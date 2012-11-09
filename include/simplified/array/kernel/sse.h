
#ifndef _Array_Kernel_SSE_H_
#define _Array_Kernel_SSE_H_

#include "array/def.h"
#include "basic/memory/aligned.h"

namespace mysimulator {

  template <typename T>
  void _allocate_sse(Array<Intrinsic<T>>& A,unsigned int size) {
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
  void _copy_sse(Array<Intrinsic<T>>& A,const Array<Intrinsic<T>>& B) {
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
  void _mono_copy_sse(Array<Intrinsic<T>>& A,const T& D) {
    assert((bool)A);
    for(unsigned int i=0;i<A.size();++i)  A[i]=D;
  }

  template <typename T>
  void _refer_sse(Array<Intrinsic<T>>& A, const Array<Intrinsic<T>>& B,
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

#endif

