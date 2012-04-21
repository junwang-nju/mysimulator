
#ifndef _Array_1D_Swap_H_
#define _Array_1D_Swap_H_

#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void Exchange(Array1D<T>& V1,Array1D<T>& V2) {
    T* tptr;
    unsigned int uptr;
    unsigned int u;
    bool b;
    tptr=V1._data;      V1._data=V2._data;          V2._data=tptr;
    u=V1._size;         V1._size=V2._size;          V2_size=u;
    uptr=V1._refCount;  V1._refCount=V2._refCount;  V2._refCount=uptr;
    uptr=V1._partUsed;  V1._partUsed=V2._partUsed;  V2._partUsed=uptr;
    b=V1._partFlag;     V1._partFlag=V2._partFlag;  V2._partFlag=b;
  }

}

#include "intrinsic-type/copy.h"

  template <typename T>
  void Swap(Array1D<T>& V1,Array1D<T>& V2, unsigned int n) {
    assert((n<=V1.Size())&&(n<=V2.Size()));
    T tm;
    for(unsigned int i=0;i<n;++i) {
      Copy(tm,V1[i]); Copy(V1[i],V2[i]); Copy(V2[i],tm);
    }
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BlasSwap(Array1D<double>& V1,Array1D<double>& V2,unsigned int n) {
    long m=n, one=1;
    BLAS<double>::Swap(&m,V1._data,&one,V2._data,&one);
  }
  void BlasSwap(Array1D<float>& V1,Array1D<float>& V2,unsigned int n) {
    long m=n, one=1;
    BLAS<float>::Swap(&m,V1._data,&one,V2._data,&one);
  }

}

#ifndef _SWAP_EqType
#define _SWAP_EqType(Type,EType) \
  void Swap(Array1D<Type>& V1,Array1D<Type>& V2,unsigned int n) { \
    assert(sizeof(Type)==sizeof(EType)); \
    assert((n<=V1.Size())&&(n<=V2.Size())); \
    long m=n, one=1; \
    BLAS<EType>::Swap(&m,reinterpret_cast<EType*>(V1._data),&one,\
                         reinterpret_cast<EType*>(V2._data),&one); \
  }
#else
#error "Duplicate Definition for Macro _SWAP_EqType"
#endif

namespace mysimulator {

  _SWAP_EqType(long long,double)
  _SWAP_EqType(unsigned long long,double)
  _SWAP_EqType(int,float)
  _SWAP_EqType(unsigned int,float)
  _SWAP_EqType(long,float)
  _SWAP_EqType(unsigned long,float)

}

#ifdef _SWAP_EqType
#undef _SWAP_EqType
#endif

#endif

