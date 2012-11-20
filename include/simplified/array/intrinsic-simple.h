
#ifndef _Array_Intrinsic_Simple_H_
#define _Array_Intrinsic_Simple_H_

#include "array/def.h"
#include "array/monomer/type.h"
#include "array/kernel/simple.h"
#include "array/kernel/direct-3d.h"
#include "array/expression/operation.h"
#include "basic/memory/access-pointer.h"
#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>,ArrayKernelName::Simple,true> {

    public:

      typedef Array<Intrinsic<T>,ArrayKernelName::Simple,true>  Type;
      typedef typename __array_monomer<Intrinsic<T>>::Type monomer_type;
      typedef T value_type;
      typedef monomer_type * pointer;
      typedef monomer_type & reference;
      typedef const monomer_type * const_pointer;
      typedef const monomer_type & const_reference;
      typedef unsigned int size_type;

      static const ArrayKernelName Kernel;

      access_ptr<monomer_type>  _pdata;
      size_type                 _ndata;

      Array() : _pdata(), _ndata(0U) {}
      Array(size_type size) : Array() { allocate(size); }
      Array(const Type& A) : Array() { imprint(A); operator=(A); }
      template <typename Y,ArrayKernelName KY>
      Array(const Array<Intrinsic<Y>,KY,true>& A) : Array() {
        imprint(A); operator=(A);
      }
      Array(Type&& A) : Array() { swap(A); }
      ~Array() { reset(); }

      operator bool() const { return (bool)_pdata && _ndata>0U; }
      size_type size() const { return _ndata; }
      pointer head() const { return _pdata.get(); }
      const_pointer end() const { return head()+size(); }
      reference operator[](size_type i) { assert(i<_ndata); return _pdata[i]; }
      const_reference operator[](size_type i) const {
        assert(i<_ndata);
        return _pdata[i];
      }
      void reset() {
        _ndata=0U;
        _pdata.reset();
      }

      Type& operator=(const Type& A) { return __copy_simple(*this,A); }
      template <typename T1,ArrayKernelName KN1>
      Type& operator=(Array<Intrinsic<T1>,KN1,true> const& A) {
        return __copy_simple(*this,A);
      }
      Type& operator=(const monomer_type& D) {
        return __mono_copy_simple(*this,D);
      }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((monomer_type)((T1)D));
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySum<EA,EB> const& A) {
        return __copy_sum_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySub<EA,EB> const& A) {
        return __copy_sub_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayMul<EA,EB> const& A) {
        return __copy_mul_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayDiv<EA,EB> const& A) {
        return __copy_div_simple(*this,A);
      }
      template <typename EA,typename EB,typename vT>
      Type& operator=(ArraySum<EA,EB,vT,ArrayKernelName::Direct3D> const& E) {
        return __copy_sum_direct3d(*this,E);
      }
      template <typename EA,typename EB,typename vT>
      Type& operator=(ArraySub<EA,EB,vT,ArrayKernelName::Direct3D> const& E) {
        return __copy_sub_direct3d(*this,E);
      }
      template <typename EA,typename EB,typename vT>
      Type& operator=(ArrayMul<EA,EB,vT,ArrayKernelName::Direct3D> const& E) {
        return __copy_mul_direct3d(*this,E);
      }
      template <typename EA,typename EB,typename vT>
      Type& operator=(ArrayDiv<EA,EB,vT,ArrayKernelName::Direct3D> const& E) {
        return __copy_div_direct3d(*this,E);
      }

      template <typename E>
      Type& operator+=(E const& A) { return operator=((*this)+A); }
      template <typename E>
      Type& operator-=(E const& A) { return operator=((*this)-A); }
      template <typename E>
      Type& operator*=(E const& A) { return operator=((*this)*A); }
      template <typename E>
      Type& operator/=(E const& A) { return operator=((*this)/A); }

      void allocate(size_type size) { __allocate_simple(*this,size); }
      void refer(const Type& A) {
        reset();
        _pdata=A._pdata;
        _ndata=A._ndata;
      }
      template <ArrayKernelName KN>
      void refer(const Array<Intrinsic<T>,KN,true>& A,
                 size_type bg, size_type num) {
        __refer_part_simple(*this,A,bg,num);
      }
      template <typename Y,ArrayKernelName KY,bool vY>
      void imprint_structure(Array<Y,KY,vY> const& A) {
        assert((bool)A);
        allocate(A.size());
      }
      template <ArrayKernelName KY>
      void imprint(const Array<Intrinsic<T>,KY,true>& A) {
        imprint_structure(A);
      }
      void swap(Type& A) {
        std::swap(_pdata,A._pdata);
        std::swap(_ndata,A._ndata);
      }

  };

  template <typename T>
  const ArrayKernelName Array<Intrinsic<T>,ArrayKernelName::Simple,true>::Kernel
      = ArrayKernelName::Simple;

  Array<Double,ArrayKernelName::Simple,true>&
  __square_root(Array<Double,ArrayKernelName::Simple,true>& A) {
    return __square_root_simple(A);
  }
  Array<Float,ArrayKernelName::Simple,true>&
  __square_root(Array<Float,ArrayKernelName::Simple,true>& A) {
    return __square_root_simple(A);
  }

  Array<Double,ArrayKernelName::Simple,true>&
  __inv_square_root(Array<Double,ArrayKernelName::Simple,true>& A) {
    return __inv_square_root_simple(A);
  }
  Array<Float,ArrayKernelName::Simple,true>&
  __inv_square_root(Array<Float,ArrayKernelName::Simple,true>& A) {
    return __inv_square_root_simple(A);
  }

}

#endif

