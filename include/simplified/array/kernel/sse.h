
#ifndef _Array_Kernel_SSE_H_
#define _Array_Kernel_SSE_H_

#include "array/def.h"
#include "basic/memory/access-pointer.h"
#include "basic/memory/aligned.h"
#include <cassert>

namespace mysimulator {

  template <typename T,ArrayKernelName KN>
  void __allocate_sse(Array<Intrinsic<T>,KN,true>& A,unsigned int size) {
    assert(size>0);
    unsigned int alloc_size=__span16_byte<T>(size);
    A._n128=(alloc_size>>4);
    A._pdata.reset(
        reinterpret_cast<T*>(__aligned_malloc(alloc_size)),
        __aligned_free);
    A._ndata=size;
    A._n128=(__span16_byte<T>(A._ndata)>>4);
    A._n128_low=(A.size()*sizeof(T))&0xFU?A._n128-1:A._n128;
    A._p128=reinterpret_cast<typename __sse_value<T>::Type*>(A.head());
  }

}

#include "basic/sse/operation.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN>
  Array<Intrinsic<T>,KN,true>&
  __copy_sse(Array<Intrinsic<T>,KN,true>& A,
             const Array<Intrinsic<T>,KN,true>& B) {
    assert((bool)A);
    assert((bool)B);
    assert(A.size128()<=B.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=B.value128(i);
    return A;
  }

  template <typename T,ArrayKernelName KN,typename vT>
  Array<Intrinsic<T>,KN,true>&
  __mono_copy_sse(Array<Intrinsic<T>,KN,true>& A, vT const& D) {
    assert((bool)A);
    typedef typename __sse_value<vT>::Type  T128;
    T128 *p=(T128*)(A.head());
    const T128 *e=p+A.size128();
    for(;p!=e;) *(p++)=Set128<vT>(D);
    return A;
  }

  template <typename T,ArrayKernelName KN,ArrayKernelName KN1>
  void __refer_part_sse(Array<Intrinsic<T>,KN,true>& A,
                        Array<Intrinsic<T>,KN1,true> const& B,
                        unsigned int bg, unsigned int num) {
    assert((((unsigned int)(B.head()+bg))&0xFU)==0);
    assert(bg+num<=B.size());
    A.reset();
    A._pdata.reset(B._pdata,bg);
    A._ndata=num;
    A._n128=(__span16_byte<T>(A._ndata)>>4);
    A._n128_low=(A.size()*sizeof(T))&0xFU?A._n128-1:A._n128;
    A._p128=reinterpret_cast<typename __sse_value<T>::Type*>(A.head());
  }

  template <typename E>
  typename E::value_type __sum_sse(E const& A) {
    typedef typename E::value_type T;
    T S=0;
    if(A.size128_low()>0) {
      typename E::value128_type s4;
      s4=Set128<T>(0);
      for(unsigned int i=0;i<A.size128_low();++i)
        s4=Sum128<T>(s4,A.value128(i));
      T* p=(T*)(&s4);
      S=p[0]+p[1]+p[2]+p[3];
    }
    for(unsigned int i=(A.size128_low()<<4)/sizeof(T);i<A.size();++i)
      S+=A[i];
    return S;
  }

}

#include "array/expression/sum.h"

namespace mysimulator {

  template <typename T,typename EA,typename EB>
  Array<Intrinsic<T>,ArrayKernelName::SSE,true>&
  __copy_sum_sse(Array<Intrinsic<T>,ArrayKernelName::SSE,true>& A,
                 ArraySum<EA,EB,T,ArrayKernelName::SSE> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=E.value128(i);
    return A;
  }

}

#include "array/expression/substract.h"

namespace mysimulator {

  template <typename T,typename EA,typename EB>
  Array<Intrinsic<T>,ArrayKernelName::SSE,true>&
  __copy_sub_sse(Array<Intrinsic<T>,ArrayKernelName::SSE,true>& A,
                 ArraySub<EA,EB,T,ArrayKernelName::SSE> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=E.value128(i);
    return A;
  }

}

#include "array/expression/multiple.h"

namespace mysimulator {

  template <typename T,typename EA,typename EB>
  Array<Intrinsic<T>,ArrayKernelName::SSE,true>&
  __copy_mul_sse(Array<Intrinsic<T>,ArrayKernelName::SSE,true>& A,
                 ArrayMul<EA,EB,T,ArrayKernelName::SSE> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=E.value128(i);
    return A;
  }

}

#include "array/expression/divide.h"

namespace mysimulator {

  template <typename T,typename EA,typename EB>
  Array<Intrinsic<T>,ArrayKernelName::SSE,true>&
  __copy_div_sse(Array<Intrinsic<T>,ArrayKernelName::SSE,true>& A,
                 ArrayDiv<EA,EB,T,ArrayKernelName::SSE> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=E.value128(i);
    return A;
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
      S=SumElement128<VT>(s4);
    }
    for(unsigned int i=(n<<4)/sizeof(VT);i<m;++i) S+=A[i]*B[i];
    return S;
  }

}

#endif

