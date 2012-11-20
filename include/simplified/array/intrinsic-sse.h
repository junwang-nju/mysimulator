
#ifndef _Array_Intrinsic_SSE_H_
#define _Array_Intrinsic_SSE_H_

#include "array/def.h"
#include "array/monomer/type.h"
#include "array/kernel/sse.h"
#include "array/kernel/simple.h"
#include "array/expression/operation.h"
#include "basic/memory/access-pointer.h"
#include "basic/type/intrinsic.h"

namespace mysimulator {

  template <typename T>
  class Array<Intrinsic<T>,ArrayKernelName::SSE,true> {

    public:

      typedef Array<Intrinsic<T>,ArrayKernelName::SSE,true>   Type;
      typedef typename __array_monomer<Intrinsic<T>>::Type  monomer_type;
      typedef T value_type;
      typedef monomer_type * pointer;
      typedef monomer_type & reference;
      typedef const monomer_type * const_pointer;
      typedef const monomer_type & const_reference;
      typedef unsigned int size_type;
      typedef typename __sse_value<value_type>::Type  value128_type;

      static const ArrayKernelName Kernel;

      access_ptr<monomer_type>  _pdata;
      size_type                 _ndata;
      size_type                 _n128;
      size_type                 _n128_low;
      value128_type*            _p128;

      Array() : _pdata(), _ndata(0U), _n128(0U), _n128_low(0U),
                _p128(nullptr) {}
      Array(size_type size) : Array() { allocate(size); }
      Array(const Type& A) : Array() { imprint(A), operator=(A); }
      template <typename Y,ArrayKernelName KY>
      Array(const Array<Intrinsic<Y>,KY,true>& A) : Array() {
        imprint(A); operator=(A);
      }
      Array(Type&& A) : Array() { swap(A); }
      ~Array() { reset(); }

      operator bool() const { return (bool)_pdata && _ndata>0U; }
      size_type size() const { return _ndata; }
      size_type size128() const { return _n128; }
      size_type size128_low() const { return _n128_low; }
      pointer head() const { return _pdata.get(); }
      const_pointer end() const { return head()+size(); }
      reference operator[](size_type i) { assert(i<_ndata); return _pdata[i]; }
      const_reference operator[](size_type i) const {
        assert(i<_ndata);
        return _pdata[i];
      }
      value128_type value128(size_type i) const {
        assert(i<size128());
        return _p128[i];
      }
      value128_type& value128(size_type i) {
        assert(i<size128());
        return _p128[i];
      }
      void reset() {
        _p128=nullptr;
        _n128_low=0U;
        _n128=0U;
        _ndata=0U;
        _pdata.reset();
      }

      Type& operator=(const Type& A) { return __copy_sse(*this,A); }
      template <typename T1,ArrayKernelName KN1>
      Type& operator=(const Array<Intrinsic<T1>,KN1,true>& A) {
        return __copy_simple(*this,A);
      }
      Type& operator=(const monomer_type& D) {
        return __mono_copy_sse(*this,D);
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
      template <typename EA,typename EB>
      Type& operator=(ArraySum<EA,EB,T,ArrayKernelName::SSE> const& A) {
        return __copy_sum_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySub<EA,EB,T,ArrayKernelName::SSE> const& A) {
        return __copy_sub_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayMul<EA,EB,T,ArrayKernelName::SSE> const& A) {
        return __copy_mul_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayDiv<EA,EB,T,ArrayKernelName::SSE> const& A) {
        return __copy_div_simple(*this,A);
      }
      // mixng of int and long may not produce sse operation

      template <typename E>
      Type& operator+=(E const& A) { return operator=((*this)+A); }
      template <typename E>
      Type& operator-=(E const& A) { return operator=((*this)-A); }
      template <typename E>
      Type& operator*=(E const& A) { return operator=((*this)*A); }
      template <typename E>
      Type& operator/=(E const& A) { return operator=((*this)/A); }

      T Sum() const { return __sum_simple(*this); }

      void allocate(size_type size) { __allocate_sse(*this,size); }
      void refer(const Type& A) {
        reset();
        _pdata=A._pdata;
        _ndata=A._ndata;
        _n128=A._n128;
        _n128_low=A._n128_low;
        _p128=reinterpret_cast<value128_type*>(A.head());
      }
      template <ArrayKernelName KN>
      void refer(const Array<Intrinsic<T>,KN,true>& A,
                 size_type bg,size_type num) {
        __refer_part_sse(*this,A,bg,num);
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
        std::swap(_n128,A._n128);
        std::swap(_n128_low,A._n128_low);
        std::swap(_p128,A._p128);
      }

  };

  template <typename T>
  const ArrayKernelName Array<Intrinsic<T>,ArrayKernelName::SSE,true>::Kernel=
      ArrayKernelName::SSE;

  template <>
  template <typename EA,typename EB>
  Array<Double,ArrayKernelName::SSE,true>&
  Array<Double,ArrayKernelName::SSE,true>::operator=(
      ArraySum<EA,EB,double,ArrayKernelName::SSE> const& E) {
    return __copy_sum_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Float,ArrayKernelName::SSE,true>&
  Array<Float,ArrayKernelName::SSE,true>::operator=(
      ArraySum<EA,EB,float,ArrayKernelName::SSE> const& E) {
    return __copy_sum_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Int,ArrayKernelName::SSE,true>&
  Array<Int,ArrayKernelName::SSE,true>::operator=(
      ArraySum<EA,EB,int,ArrayKernelName::SSE> const& E) {
    return __copy_sum_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Long,ArrayKernelName::SSE,true>&
  Array<Long,ArrayKernelName::SSE,true>::operator=(
      ArraySum<EA,EB,long,ArrayKernelName::SSE> const& E) {
    return __copy_sum_sse(*this,E);
  }

  template <>
  template <typename EA,typename EB>
  Array<Double,ArrayKernelName::SSE,true>&
  Array<Double,ArrayKernelName::SSE,true>::operator=(
      ArraySub<EA,EB,double,ArrayKernelName::SSE> const& E) {
    return __copy_sub_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Float,ArrayKernelName::SSE,true>&
  Array<Float,ArrayKernelName::SSE,true>::operator=(
      ArraySub<EA,EB,float,ArrayKernelName::SSE> const& E) {
    return __copy_sub_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Int,ArrayKernelName::SSE,true>&
  Array<Int,ArrayKernelName::SSE,true>::operator=(
      ArraySub<EA,EB,int,ArrayKernelName::SSE> const& E) {
    return __copy_sub_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Long,ArrayKernelName::SSE,true>&
  Array<Long,ArrayKernelName::SSE,true>::operator=(
      ArraySub<EA,EB,long,ArrayKernelName::SSE> const& E) {
    return __copy_sub_sse(*this,E);
  }

  template <>
  template <typename EA,typename EB>
  Array<Double,ArrayKernelName::SSE,true>&
  Array<Double,ArrayKernelName::SSE,true>::operator=(
      ArrayMul<EA,EB,double,ArrayKernelName::SSE> const& E) {
    return __copy_mul_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Float,ArrayKernelName::SSE,true>&
  Array<Float,ArrayKernelName::SSE,true>::operator=(
      ArrayMul<EA,EB,float,ArrayKernelName::SSE> const& E) {
    return __copy_mul_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Int,ArrayKernelName::SSE,true>&
  Array<Int,ArrayKernelName::SSE,true>::operator=(
      ArrayMul<EA,EB,int,ArrayKernelName::SSE> const& E) {
    return __copy_mul_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Long,ArrayKernelName::SSE,true>&
  Array<Long,ArrayKernelName::SSE,true>::operator=(
      ArrayMul<EA,EB,long,ArrayKernelName::SSE> const& E) {
    return __copy_mul_sse(*this,E);
  }

  template <>
  template <typename EA,typename EB>
  Array<Double,ArrayKernelName::SSE,true>&
  Array<Double,ArrayKernelName::SSE,true>::operator=(
      ArrayDiv<EA,EB,double,ArrayKernelName::SSE> const& E) {
    return __copy_div_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Float,ArrayKernelName::SSE,true>&
  Array<Float,ArrayKernelName::SSE,true>::operator=(
      ArrayDiv<EA,EB,float,ArrayKernelName::SSE> const& E) {
    return __copy_div_sse(*this,E);
  }

  Array<Float,ArrayKernelName::SSE,true>&
  __square_root(Array<Float,ArrayKernelName::SSE,true>& A) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size128();++i) _mm_sqrt_ps(A.value128(i));
    return A;
  }
  Array<Double,ArrayKernelName::SSE,true>&
  __square_root(Array<Double,ArrayKernelName::SSE,true>& A) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size128();++i) _mm_sqrt_pd(A.value128(i));
    return A;
  }

  Array<Float,ArrayKernelName::SSE,true>&
  __inv_square_root(Array<Float,ArrayKernelName::SSE,true>& A) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size128();++i) _mm_rsqrt_ps(A.value128(i));
    return A;
  }
  Array<Double,ArrayKernelName::SSE,true>&
  __inv_square_root(Array<Double,ArrayKernelName::SSE,true>& A) {
    return __inv_square_root_simple(A);
  }

  template <>
  double Array<Double,ArrayKernelName::SSE,true>::Sum() const {
    return __sum_sse(*this);
  }
  template <>
  float Array<Float,ArrayKernelName::SSE,true>::Sum() const {
    return __sum_sse(*this);
  }
  template <>
  int Array<Int,ArrayKernelName::SSE,true>::Sum() const {
    return __sum_sse(*this);
  }
  template <>
  long Array<Long,ArrayKernelName::SSE,true>::Sum() const {
    return __sum_sse(*this);
  }

}

#endif

