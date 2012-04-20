
#ifndef _Array_1D_Copy_H_
#define _Array_1D_Copy_H_

#include "array/1d/size.h"
#include <cassert>

namespace mysimulator {

  template <typename T1,typename T2>
  void Copy(T1* p, const T2* q) {
    unsigned int n=size(p);
    assert(n==size(q));
    for(unsigned int i=0;i<n;++i) p[i]=q[i];
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void Copy(double* p, const double* q) {
    long n=size(p), one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    BLAS<double>::Copy(&n,const_cast<double*>(q),&one,p,&one);
  }

  void Copy(float* p, const float* q) {
    long n=size(p), one=1;
    assert(static_cast<unsigned int>(n)==size(q));
    BLAS<float>::Copy(&n,const_cast<float*>(q),&one,p,&one);
  }

  void Copy(long double* p, const long double* q) {
    assert(sizeof(long double)==3*sizeof(double));
    long n=size(p), three=3;
    assert(static_cast<unsigned int>(n)==size(q));
    double *rp=reinterpret_cast<double*>(p);
    double *rq=reinterpret_cast<double*>(const_cast<long double*>(q));
    BLAS<double>::Copy(&n,rq,&three,rp,&three);
    BLAS<double>::Copy(&n,rq+1,&three,rp+1,&three);
    BLAS<double>::Copy(&n,rq+2,&three,rp+2,&three);
  }

}

#ifndef _COPY_EqType
#define _COPY_EqType(type,Etype) \
  void Copy(type* p, const type* q) { \
    assert(sizeof(type)==sizeof(Etype)); \
    long n=size(p), one=1; \
    assert(static_cast<unsigned int>(n)==size(q)); \
    BLAS<Etype>::Copy(&n,reinterpret_cast<Etype*>(const_cast<type*>(q)),&one,\
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

#ifndef _COPY_ShortType
#define _COPY_ShortType(type) \
  void Copy(type* p, const type* q) { \
    unsigned int n=size(p); \
    assert(n==size(q)); \
    memcpy(p,q,n*sizeof(type)); \
  }
#else
#error "Duplication Definition for Macro _COPY_ShortType"
#endif

namespace mysimulator {

  _COPY_ShortType(short)
  _COPY_ShortType(unsigned short)
  _COPY_ShortType(char)
  _COPY_ShortType(unsigned char)

}

#ifdef _COPY_ShortType
#undef _COPY_ShortType
#endif

#endif

