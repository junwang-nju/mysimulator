
#ifndef _Array_Kernel_SSE_H_
#define _Array_Kernel_SSE_H_

#include "array/def.h"
#include "basic/memory/aligned.h"

namespace mysimulator {

  template <typename T>
  void __allocate_sse(Array<Intrinsic<T>>& A,unsigned int size) {
    assert(size>0);
    unsigned int alloc_size=__span16_byte<T>(size);
    A._n128=(alloc_size>>4);
    A._pdata.reset(
        reinterpret_cast<T*>(__aligned_malloc(alloc_size)),
        __aligned_free);
    A._ndata=size;
  }

}

#include "array/kernel/name.h"
#include "basic/memory/access-pointer.h"
#include <emmintrin.h>
#include <smmintrin.h>

namespace mysimulator {

  template <typename T>
  void __copy_sse(Array<Intrinsic<T>>& A,const Array<Intrinsic<T>>& B) {
    assert((bool)A);
    assert((bool)B);
    assert(A.size()<=B.size());
    assert(B.KernelName() == ArrayKernelName::SSE);
    __m128i* p=(__m128i*)(A.head());
    __m128i* q=(__m128i*)(B.head());
    const __m128i* e=p+A.size128();
    for(;p!=e;) _mm_store_si128(p++,*(q++));
  }

  template <typename T>
  void __mono_copy_sse(Array<Intrinsic<T>>& A,const T& D) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size();++i)  A[i]=D;
  }

  template <typename T>
  void __refer_sse(Array<Intrinsic<T>>& A, const Array<Intrinsic<T>>& B,
                   unsigned int bg,unsigned int num) {
    assert((bool)B);
    assert(B.KernelName() == ArrayKernelName::SSE);
    assert(B._pdata.__aligned16());
    assert(((bg*sizeof(T))&0xFU)==0);
    assert(bg+num<=B.size());
    A._pdata.reset(B._pdata,bg);
    A._ndata=num;
    A._n128=__span16<T>(num);
  }

}

#include "array/expression/sum.h"

namespace mysimulator {

  template <typename T,typename EA,typename EB>
  void __assign_sum_sse(Array<T>& A, ArraySum<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size128();++i)
      value128(A,i)=value128(E,i);
  }

}

#include "array/expression/substract.h"

namespace mysimulator {

  template <typename T,typename EA,typename EB>
  void __assign_sub_sse(Array<T>& A,ArraySub<EA,EB> const& E) {
    assert((bool)A);
    assert((bool)E);
    assert(A.size128()<=E.size128());
    for(unsigned int i=0;i<A.size();++i)
      value128(A,i)=value128(E,i);
  }

}

#endif

