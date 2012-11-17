
#ifndef _Array_General_Value_H_
#define _Array_General_Value_H_

#include "array/def.h"
#include "array/monomer/type.h"
#include "array/kernel/simple.h"
#include "basic/memory/access-pointer.h"
#include "basic/util/imprint.h"
#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class Array<T,ArrayKernelName::Simple,true> {

    public:

      typedef Array<T,ArrayKernelName::Simple,true>   Type;
      typedef typename __array_monomer<T>::Type       monomer_type;
      typedef typename T::value_type    value_type;
      typedef monomer_type * pointer;
      typedef monomer_type & reference;
      typedef const monomer_type * const_pointer;
      typedef const monomer_type & const_reference;
      typedef unsigned int size_type;

      friend void __allocate_simple<T>(Type&,size_type);
      template <typename T1,ArrayKernelName KN,bool vF, ArrayKernelName KN1>
      friend void __refer_part_simple(Array<T1,KN,vF>&,Array<T1,KN1,vF> const&,
                                      size_type,size_type);

    protected:

      access_ptr<monomer_type>  _pdata;
      size_type                 _ndata;

    public:

      Array() : _pdata(), _ndata(0U) {}
      Array(size_type size) : Array() { allocate(size); }
      Array(const Type& A) : Array() { imprint(A); operator=(A); }
      Array(Type&& A) : Array() { swap(A); }
      ~Array() { reset(); }

      operator bool() const { return (bool)_pdata && _ndata>0U; }
      ArrayKernelName KernelName() const { return ArrayKernelName::Simple; }
      size_type size() const { return _ndata; }
      pointer head() const { return _pdata.get(); }
      const_pointer end() const { return head()+size(); }
      reference operator[](size_type i) { assert(i<_ndata); return _pdata[i]; }
      const_reference operator[](size_type i) const {
        assert(i<_ndata);
        return _pdata[i];
      }
      void reset() { _ndata=0U; _pdata.reset(); }

      Type& operator=(const Type& A) { return __copy_simple<T>(*this,A); }
      Type& operator=(const monomer_type& D) {
        return __mono_copy_simple<T>(*this,D);
      }
      Type& operator=(const value_type& D) { return __value_copy_simple<T>(D); }
      template <typename T1>
      Type& operator=(const Intrinsic<T1>& D) {
        return operator=((value_type)((T1)D));
      }

      value_type Sum() const {
        value_type S=0;
        for(unsigned int i=0;i<size();++i)  S+=(*this)[i].Sum();
        return S;
      }

      void allocate(size_type size) { __allocate_simple<T>(*this,size); }
      void refer(const Type& A) {
        reset();
        _pdata=A._pdata;
        _ndata=A._ndata;
      }
      void refer(const Type& A, size_type bg, size_type num) {
        __refer_part_simple<T>(*this,A,bg,num);
      }
      template <typename Y,ArrayKernelName KY,bool vY>
      void imprint_structure(Array<Y,KY,vY> const& A) {
        assert((bool)A);
        allocate(A.size());
      }
      void imprint(const Type& A) {
        imprint_structure(A);
        for(unsigned int i=0;i<size();++i)  __imprint((*this)[i],A[i]);
      }
      void swap(Type& A) {
        std::swap(_pdata,A._pdata);
        std::swap(_ndata,A._ndata);
      }

  };

}

#endif

