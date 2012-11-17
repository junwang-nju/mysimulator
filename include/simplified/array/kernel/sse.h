
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

}

#include "array/expression/sum.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN,typename EA,typename EB>
  Array<Intrinsic<T>,KN,true>&
  __copy_sum_sse(Array<Intrinsic<T>,KN,true>& A,
                 ArraySum<EA,EB,T,true> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=E.value128(i);
    return A;
  }

}

#include "array/expression/substract.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN,typename EA,typename EB>
  Array<Intrinsic<T>,KN,true>&
  __copy_sub_sse(Array<Intrinsic<T>,KN,true>& A,
                 ArraySub<EA,EB,T,true> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=E.value128(i);
    return A;
  }

}

#include "array/expression/multiple.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN,typename EA,typename EB>
  Array<Intrinsic<T>,KN,true>&
  __copy_mul_sse(Array<Intrinsic<T>,KN,true>& A,
                 ArrayMul<EA,EB,T,true> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=E.value128(i);
    return A;
  }

}

#include "array/expression/divide.h"

namespace mysimulator {

  template <typename T,ArrayKernelName KN,typename EA,typename EB>
  Array<Intrinsic<T>,KN,true>&
  __copy_div_sse(Array<Intrinsic<T>,KN,true>& A,
                 ArrayDiv<EA,EB,T,true> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i) A.value128(i)=E.value128(i);
    return A;
  }

}

#endif

