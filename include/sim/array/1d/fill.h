
#ifndef _Array_1D_Fill_H_
#define _Array_1D_Fill_H_

namespace mysimulator {

  template <typename T1, typename T2>
  void Fill(T1* p, const T2& d, unsigned int n) {
    for(unsigned int i=0;i<n;++i) p[i]=d;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BLASFill(double* p, const double& d, unsigned int n) {
    long m=n, one=1, zero=0;
    BLAS<double>::Copy(&m,const_cast<double*>(&d),&zero,p,&one);
  }

  void BLASFill(float* p, const float& d, unsigned int n) {
    long m=n, one=1, zero=0;
    BLAS<float>::Copy(&m,const_cast<float*>(&d),&zero,p,&one);
  }

}

#include <cassert>

namespace mysimulator {

  void BLASFill(long double* p, const long double& d, unsigned int n) {
    assert(sizeof(long double)==3*sizeof(double));
    long m=n, three=3, zero=0;
    double* lp=reinterpret_cast<double*>(p);
    double* ld=reinterpret_cast<double*>(const_cast<long double*>(&d));
    BLAS<double>::Copy(&m,ld,&zero,lp,&three);
    BLAS<double>::Copy(&m,ld+1,&zero,lp+1,&three);
    BLAS<double>::Copy(&m,ld+2,&zero,lp+2,&three);
  }

}

#ifndef _FILL_EqType
#define _FILL_EqType(type,Etype) \
  void BLASFill(type* p, const type& d, unsigned int n) { \
    assert(sizeof(type)==sizeof(Etype)); \
    long m=n, one=1, zero=0; \
    BLAS<Etype>::Copy(&m,reinterpret_cast<Etype*>(const_cast<type*>(&d)),&zero,\
                         reinterpret_cast<Etype*>(p),&one); \
  }
#else
#error "Duplicate Definition for Macro _FILL_EqType"
#endif

namespace mysimulator {

  _FILL_EqType(long long,double)
  _FILL_EqType(unsigned long long,double)
  _FILL_EqType(int,float)
  _FILL_EqType(unsigned int,float)
  _FILL_EqType(long,float)
  _FILL_EqType(unsigned long,float)

}

#ifdef _FILL_EqType
#undef _FILL_EqType
#endif

#include <cstring>

namespace mysimulator {

  void MemFill(char* p, const char& d, unsigned int n) { memset(p,d,n); }
  void MemFill(char* p, const unsigned char& d, unsigned int n) {
    memset(p,d,n);
  }
  void MemFill(unsigned char* p, const unsigned char& d, unsigned int n) {
    memset(p,d,n);
  }
  void MemFill(unsigned char* p, const char& d, unsigned int n) {
    memset(p,d,n);
  }

}

#endif

