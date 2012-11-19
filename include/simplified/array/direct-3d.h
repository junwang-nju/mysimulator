
#ifndef _Array_Direct_3D_H_
#define _Array_Direct_3D_H_

#include "array/def.h"
#include "array/monomer/type.h"
#include "array/kernel/simple.h"
#include "array/kernel/direct-3d.h"
#include "array/expression/operation.h"
#include "basic/memory/access-pointer.h"

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> {

    public:

      typedef Array<Intrinsic<T>,ArrayKernelName::Direct3D,true>  Type;
      typedef typename __array_monomer<Intrinsic<T>>::Type  monomer_type;
      typedef T value_type;
      typedef monomer_type * pointer;
      typedef monomer_type & reference;
      typedef const monomer_type * const_pointer;
      typedef const monomer_type & const_reference;
      typedef unsigned int size_type;

      access_ptr<monomer_type>  _pdata;
      size_type                 _ndata;

      Array() : _pdata(), _ndata(0U) {}
      Array(size_type size) : Array() { assert(size==3U); allocate(); }
      Array(const Type& A) : Array() { imprint(A); operator=(A); }
      Array(Type&& A) : Array() { swap(A); }
      ~Array() { reset(); }

      operator bool() const { return (bool)_pdata && _ndata==3U; }
      ArrayKernelName KernelName() const { return ArrayKernelName::Direct3D; }
      size_type size() const { return _ndata; }
      pointer head() const { return _pdata.get(); }
      const_pointer end() const { return head()+size(); }
      reference operator[](size_type i) { assert(i<_ndata); return _pdata[i]; }
      const_reference operator[](size_type i) const {
        assert(i<_ndata);
        return _pdata[i];
      }
      void reset() { _ndata=0U; _pdata.reset(); }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        _pdata[0]=A[0];
        _pdata[1]=A[1];
        _pdata[2]=A[2];
        return *this;
      }
      template <typename T1,ArrayKernelName K1>
      Type& operator=(Array<Intrinsic<T1>,K1> const& A) {
        _pdata[0]=A[0];
        _pdata[1]=A[1];
        _pdata[2]=A[2];
        return *this;
      }
      Type& operator=(const monomer_type& D) {
        assert((bool)(*this));
        _pdata[0]=D;
        _pdata[1]=D;
        _pdata[2]=D;
        return *this;
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySum<EA,EB> const& A) {
        return __copy_sum_direct3d(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySub<EA,EB> const& A) {
        return __copy_sub_direct3d(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayMul<EA,EB> const& A) {
        return __copy_mul_direct3d(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayDiv<EA,EB> const& A) {
        return __copy_div_direct3d(*this,A);
      }

      template <typename E>
      Type& operator+=(E const& A) { return operator=((*this)+A); }
      template <typename E>
      Type& operator-=(E const& A) { return operator=((*this)-A); }
      template <typename E>
      Type& operator*=(E const& A) { return operator=((*this)*A); }
      template <typename E>
      Type& operator/=(E const& A) { return operator=((*this)/A); }

      void allocate(size_type size=3U) {
        assert(size==3U);
        __allocate_simple(*this,3U);
      }
      void refer(const Type& A,size_type bg=0U,size_type num=3U) {
        assert( bg==0U && num==3U );
        reset();
        _pdata=A._pdata;
        _ndata=A._ndata;
      }
      template <typename T1,ArrayKernelName K>
      void refer(const Array<Intrinsic<T1>,K>& A,size_type bg,size_type num=3U){
        __refer_part_simple(*this,A,bg,3U);
      }
      template <typename T1>
      void imprint_structure(
          Array<Intrinsic<T1>,ArrayKernelName::Direct3D> const& A) {
        assert((bool)A);
        allocate();
      }
      void imprint(const Type& A) { imprint_structure(A); }
      void swap(Type& A) {
        std::swap(_pdata,A._pdata);
        std::swap(_ndata,A._ndata);
      }

  };

}

#endif

