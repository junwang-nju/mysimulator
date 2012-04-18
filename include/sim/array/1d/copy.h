
#ifndef _Array_1D_Copy_H_
#define _Array_1D_Copy_H_

namespace mysimulator {

  template <typename T1,typename T2>
  void Copy(T1* p, const T2* q, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]=q[i];
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BLASCopy(double* p, const double* q, unsigned int n) {
    long m=n, one=1;
    BLAS<double>::Copy(&m,const_cast<double*>(q),&one,p,&one);
  }

  void BLASCopy(float* p, const float* q, unsigned int n) {
    long m=n, one=1;
    BLAS<float>::Copy(&m,const_cast<float*>(q),&one,p,&one);
  }

}

#include <cassert>

namespace mysimulator {

  void BLASCopy(long double* p, const long double* q, unsigned int n) {
    assert(sizeof(long double)==3*sizeof(double));
    long m=n, three=3;
    double *rp=reinterpret_cast<double*>(p);
    double *rq=reinterpret_cast<double*>(const_cast<long double*>(q));
    BLAS<double>::Copy(&m,rq,&three,rp,&three);
    BLAS<double>::Copy(&m,rq+1,&three,rp+1,&three);
    BLAS<double>::Copy(&m,rq+2,&three,rp+2,&three);
  }

}

#ifndef _COPY_EqType
#define _COPY_EqType(type,Etype) \
  void BLASCopy(type* p, const type* q, unsigned int n) { \
    assert(sizeof(type)==sizeof(Etype)); \
    long m=n, one=1; \
    BLAS<Etype>::Copy(&m,reinterpret_cast<Etype*>(const_cast<type*>(q)),&one,\
                         reinterpret_cast<Etype*>(p),&one); \
  }
#else
#error "Duplication Definition for Macro _COPY_EqType"
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
  void MemCopy(T* p, const T* q, unsigned int n) {
    memcpy(p,q,n*sizeof(T));
  }

}

#endif

