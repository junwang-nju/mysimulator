
#ifndef _Array_1D_Copy_H_
#define _Array_1D_Copy_H_

#include "array/1d/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void Copy(Array1D<T1>& V1, const Array1D<T2>& V2,unsigned int n) {
    assert((n<=V1.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i) Copy(V1[i],V2[i]);
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BlasCopy(Array1D<double>& V1,const Array1D<double>& V2,unsigned int n) {
    assert((n<=V1.Size())&&(n<=V2.Size()));
    long m=n, one=1;
    BLAS<double>::Copy(&m,const_cast<double*>(V2._data),&one,V1._data,&one);
  }

  void BlasCopy(Array1D<float>& V1,const Array1D<float>& V2,unsigned int n) {
    assert((n<=V1.Size())&&(n<=V2.Size()));
    long m=n, one=1;
    BLAS<float>::Copy(&m,const_cast<float*>(V2._data),&one,V1._data,&one);
  }

  void BlasCopy(Array1D<long double>& V1,const Array1D<long double>& V2,
                unsigned int n) {
    assert(sizeof(long double)==3*sizeof(double));
    assert((n<=V1.Size())&&(n<=V2.Size()));
    long m=n, three=3;
    double *p=reinterpret_cast<double*>(V1._data);
    double *q=reinterpret_cast<double*>(const_cast<long double*>(V2._data));
    BLAS<double>::Copy(&m,q,  &three,p,  &three);
    BLAS<double>::Copy(&m,q+1,&three,p+1,&three);
    BLAS<double>::Copy(&m,q+2,&three,p+2,&three);
  }

}

#ifndef _COPY_EqType
#define _COPY_EqType(Type,EType) \
  void BlasCopy(Array1D<Type>& V1,const Array1D<Type>& V2,unsigned int n) { \
    assert(sizeof(Type)==sizeof(EType)); \
    long m=n, one=1; \
    BLAS<EType>::Copy(&m,reinterpret_cast<EType*>(const_cast<Type*>(V2._data)),\
                      &one,reinterpret_cast<EType*>(V1._data),&one); \
  }
#else
#error "Duplicate Definition for Macro _COPY_EqType"
#endif

namespace mysimulator {

  _COPY_EqType(long long,double)
  _COPY_EqType(unsigned long long,double)
  _COPY_EqType(int,float)
  _COPY_EqType(unsigned int,float)
  _COPY_EqType(long,float)
  _COPY_EqType(unsigned long,float)

}

#ifdef _COPY_EqType
#undef _COPY_EqType
#endif

#include <cstring>

namespace mysimulator {

  template <typename T>
  void MemCopy(Array1D<T>& V1,const Array1D<T>& V2,unsigned int n) {
    memcpy(V1._data,V2._data,n*sizeof(T));
  }
}

#endif

