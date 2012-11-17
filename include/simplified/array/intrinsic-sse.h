
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

      friend void
      __allocate_sse<T,ArrayKernelName::SSE>(Type&,size_type);
      template <typename T1,ArrayKernelName KN1,ArrayKernelName KN>
      friend void
      __refer_part_sse(Array<Intrinsic<T1>,KN1,true>&,
                       Array<Intrinsic<T1>,KN,true> const&,size_type,size_type);

      static const bool _is_SSE_valid;

    protected:

      access_ptr<monomer_type>  _pdata;
      size_type                 _ndata;
      size_type                 _n128;
      size_type                 _n128_low;
      value128_type*            _p128;

    public:

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
      ArrayKernelName KernelName() const { return ArrayKernelName::SSE; }
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
      template <typename EA,typename EB>
      Type& operator=(ArraySum<EA,EB,T,true> const& A) {
        return __copy_sum_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArraySub<EA,EB,T,true> const& A) {
        return __copy_sub_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayMul<EA,EB,T,true> const& A) {
        return __copy_mul_simple(*this,A);
      }
      template <typename EA,typename EB>
      Type& operator=(ArrayDiv<EA,EB,T,true> const& A) {
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
      template <typename Y,ArrayKernelName KY>
      void imprint(const Array<Intrinsic<Y>,KY,true>& A) {
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
  const bool Array<Intrinsic<T>,ArrayKernelName::SSE,true>::_is_SSE_valid
      = true;

  template <>
  template <typename EA,typename EB>
  Array<Double,ArrayKernelName::SSE,true>&
  Array<Double,ArrayKernelName::SSE,true>::operator=(
      ArraySum<EA,EB,double,true> const& E) {
    return __copy_sum_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Float,ArrayKernelName::SSE,true>&
  Array<Float,ArrayKernelName::SSE,true>::operator=(
      ArraySum<EA,EB,float,true> const& E) {
    return __copy_sum_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Int,ArrayKernelName::SSE,true>&
  Array<Int,ArrayKernelName::SSE,true>::operator=(
      ArraySum<EA,EB,int,true> const& E) {
    return __copy_sum_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Long,ArrayKernelName::SSE,true>&
  Array<Long,ArrayKernelName::SSE,true>::operator=(
      ArraySum<EA,EB,long,true> const& E) {
    return __copy_sum_sse(*this,E);
  }

  template <>
  template <typename EA,typename EB>
  Array<Double,ArrayKernelName::SSE,true>&
  Array<Double,ArrayKernelName::SSE,true>::operator=(
      ArraySub<EA,EB,double,true> const& E) {
    return __copy_sub_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Float,ArrayKernelName::SSE,true>&
  Array<Float,ArrayKernelName::SSE,true>::operator=(
      ArraySub<EA,EB,float,true> const& E) {
    return __copy_sub_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Int,ArrayKernelName::SSE,true>&
  Array<Int,ArrayKernelName::SSE,true>::operator=(
      ArraySub<EA,EB,int,true> const& E) {
    return __copy_sub_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Long,ArrayKernelName::SSE,true>&
  Array<Long,ArrayKernelName::SSE,true>::operator=(
      ArraySub<EA,EB,long,true> const& E) {
    return __copy_sub_sse(*this,E);
  }

  template <>
  template <typename EA,typename EB>
  Array<Double,ArrayKernelName::SSE,true>&
  Array<Double,ArrayKernelName::SSE,true>::operator=(
      ArrayMul<EA,EB,double,true> const& E) {
    return __copy_mul_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Float,ArrayKernelName::SSE,true>&
  Array<Float,ArrayKernelName::SSE,true>::operator=(
      ArrayMul<EA,EB,float,true> const& E) {
    return __copy_mul_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Int,ArrayKernelName::SSE,true>&
  Array<Int,ArrayKernelName::SSE,true>::operator=(
      ArrayMul<EA,EB,int,true> const& E) {
    return __copy_mul_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Long,ArrayKernelName::SSE,true>&
  Array<Long,ArrayKernelName::SSE,true>::operator=(
      ArrayMul<EA,EB,long,true> const& E) {
    return __copy_mul_sse(*this,E);
  }

  template <>
  template <typename EA,typename EB>
  Array<Double,ArrayKernelName::SSE,true>&
  Array<Double,ArrayKernelName::SSE,true>::operator=(
      ArrayDiv<EA,EB,double,true> const& E) {
    return __copy_div_sse(*this,E);
  }
  template <>
  template <typename EA,typename EB>
  Array<Float,ArrayKernelName::SSE,true>&
  Array<Float,ArrayKernelName::SSE,true>::operator=(
      ArrayDiv<EA,EB,float,true> const& E) {
    return __copy_div_sse(*this,E);
  }

  template <typename EA,typename EB>
  typename EA::value_type __dot_sse(EA const& A, EB const& B) {
    assert((bool)A);
    assert((bool)B);
    typedef typename EA::value_type VT;
    unsigned int n=A.size128_low()<B.size128_low()?A.size128_low():
                                                   B.size128_low();
    unsigned int m=A.size()<B.size()?A.size():B.size();
    typename __sse_value<VT>::Type tmp,s4;
    VT S=0;
    if(n>0) {
      s4=Set128<VT>(0);
      for(unsigned int i=0;i<n;++i) {
        tmp=Mul128<VT>(A.value128(i),B.value128(i));
        s4=Sum128<VT>(s4,tmp);
      }
      VT* p=(VT*)(&s4);
      S=p[0]+p[1]+p[2]+p[3];
    }
    for(unsigned int i=(n<<4)/sizeof(VT);i<m;++i) S+=A[i]*B[i];
    return S;
  }

  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             ArraySum<EA,EB,double,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             ArraySub<EA,EB,double,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             ArrayMul<EA,EB,double,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             ArrayDiv<EA,EB,double,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(ArraySum<EA,EB,double,true> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySum<EA,EB,double,true> const& A,
             ArraySum<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySum<EA,EB,double,true> const& A,
             ArraySub<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySum<EA,EB,double,true> const& A,
             ArrayMul<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySum<EA,EB,double,true> const& A,
             ArrayDiv<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(ArraySub<EA,EB,double,true> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySub<EA,EB,double,true> const& A,
             ArraySum<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySub<EA,EB,double,true> const& A,
             ArraySub<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySub<EA,EB,double,true> const& A,
             ArrayMul<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySub<EA,EB,double,true> const& A,
             ArrayDiv<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(ArrayMul<EA,EB,double,true> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayMul<EA,EB,double,true> const& A,
             ArraySum<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayMul<EA,EB,double,true> const& A,
             ArraySub<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayMul<EA,EB,double,true> const& A,
             ArrayMul<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayMul<EA,EB,double,true> const& A,
             ArrayDiv<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(ArrayDiv<EA,EB,double,true> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayDiv<EA,EB,double,true> const& A,
             ArraySum<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayDiv<EA,EB,double,true> const& A,
             ArraySub<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayDiv<EA,EB,double,true> const& A,
             ArrayMul<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayDiv<EA,EB,double,true> const& A,
             ArrayDiv<EC,ED,double,true> const& B) {
    return __dot_sse(A,B);
  }

  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            ArraySum<EA,EB,float,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            ArraySub<EA,EB,float,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            ArrayMul<EA,EB,float,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            ArrayDiv<EA,EB,float,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(ArraySum<EA,EB,float,true> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySum<EA,EB,float,true> const& A,
            ArraySum<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySum<EA,EB,float,true> const& A,
            ArraySub<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySum<EA,EB,float,true> const& A,
            ArrayMul<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySum<EA,EB,float,true> const& A,
            ArrayDiv<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(ArraySub<EA,EB,float,true> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySub<EA,EB,float,true> const& A,
            ArraySum<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySub<EA,EB,float,true> const& A,
            ArraySub<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySub<EA,EB,float,true> const& A,
            ArrayMul<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySub<EA,EB,float,true> const& A,
            ArrayDiv<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(ArrayMul<EA,EB,float,true> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayMul<EA,EB,float,true> const& A,
            ArraySum<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayMul<EA,EB,float,true> const& A,
            ArraySub<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayMul<EA,EB,float,true> const& A,
            ArrayMul<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayMul<EA,EB,float,true> const& A,
            ArrayDiv<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(ArrayDiv<EA,EB,float,true> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayDiv<EA,EB,float,true> const& A,
            ArraySum<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayDiv<EA,EB,float,true> const& A,
            ArraySub<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayDiv<EA,EB,float,true> const& A,
            ArrayMul<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayDiv<EA,EB,float,true> const& A,
            ArrayDiv<EC,ED,float,true> const& B) {
    return __dot_sse(A,B);
  }

  int Dot(Array<Int,ArrayKernelName::SSE,true> const& A,
          Array<Int,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(Array<Int,ArrayKernelName::SSE,true> const& A,
          ArraySum<EA,EB,int,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(Array<Int,ArrayKernelName::SSE,true> const& A,
          ArraySub<EA,EB,int,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(Array<Int,ArrayKernelName::SSE,true> const& A,
          ArrayMul<EA,EB,int,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(ArraySum<EA,EB,int,true> const& A,
          Array<Int,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySum<EA,EB,int,true> const& A,
          ArraySum<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySum<EA,EB,int,true> const& A,
          ArraySub<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySum<EA,EB,int,true> const& A,
          ArrayMul<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(ArraySub<EA,EB,int,true> const& A,
          Array<Int,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySub<EA,EB,int,true> const& A,
          ArraySum<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySub<EA,EB,int,true> const& A,
          ArraySub<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySub<EA,EB,int,true> const& A,
          ArrayMul<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(ArrayMul<EA,EB,int,true> const& A,
          Array<Int,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArrayMul<EA,EB,int,true> const& A,
          ArraySum<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArrayMul<EA,EB,int,true> const& A,
          ArraySub<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArrayMul<EA,EB,int,true> const& A,
          ArrayMul<EC,ED,int,true> const& B) {
    return __dot_sse(A,B);
  }

  long Dot(Array<Long,ArrayKernelName::SSE,true> const& A,
           Array<Long,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(Array<Long,ArrayKernelName::SSE,true> const& A,
           ArraySum<EA,EB,long,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(Array<Long,ArrayKernelName::SSE,true> const& A,
           ArraySub<EA,EB,long,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(Array<Long,ArrayKernelName::SSE,true> const& A,
           ArrayMul<EA,EB,long,true>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(ArraySum<EA,EB,long,true> const& A,
           Array<Long,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySum<EA,EB,long,true> const& A,
           ArraySum<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySum<EA,EB,long,true> const& A,
           ArraySub<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySum<EA,EB,long,true> const& A,
           ArrayMul<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(ArraySub<EA,EB,long,true> const& A,
           Array<Long,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySub<EA,EB,long,true> const& A,
           ArraySum<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySub<EA,EB,long,true> const& A,
           ArraySub<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySub<EA,EB,long,true> const& A,
           ArrayMul<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(ArrayMul<EA,EB,long,true> const& A,
           Array<Long,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArrayMul<EA,EB,long,true> const& A,
           ArraySum<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArrayMul<EA,EB,long,true> const& A,
           ArraySub<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArrayMul<EA,EB,long,true> const& A,
           ArrayMul<EC,ED,long,true> const& B) {
    return __dot_sse(A,B);
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

