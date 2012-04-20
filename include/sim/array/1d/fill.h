
#ifndef _Array_1D_Fill_H_
#define _Array_1D_Fill_H_

#include "array/1d/size.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void Fill(T1* p, const T2& d) {
    unsigned int n=size(p);
    for(unsigned int i=0;i<n;++i) p[i]=d;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void Fill(double* p, const double& d) {
    long n=size(p), one=1, zero=0;
    BLAS<double>::Copy(&n,const_cast<double*>(&d),&zero,p,&one);
  }

  void Fill(float* p, const float& d) {
    long n=size(p), one=1, zero=0;
    BLAS<float>::Copy(&n,const_cast<float*>(&d),&zero,p,&one);
  }

  void Fill(long double* p, const long double& d) {
    long n=size(p), three=3, zero=0;
    double* lp=reinterpret_cast<double*>(p);
    double* ld=reinterpret_cast<double*>(const_cast<long double*>(&d));
    BLAS<double>::Copy(&n,ld,&zero,lp,&three);
    BLAS<double>::Copy(&n,ld+1,&zero,lp+1,&three);
    BLAS<double>::Copy(&n,ld+2,&zero,lp+2,&three);
  }

}

#ifndef _FILL_EqType
#define _FILL_EqType(type,Etype) \
  void Fill(type* p, const type& d) { \
    assert(sizeof(type)==sizeof(Etype)); \
    long n=size(p), one=1, zero=0; \
    BLAS<Etype>::Copy(&n,reinterpret_cast<Etype*>(const_cast<type*>(&d)),&zero,\
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

#ifndef _FILL_ShortType
#define _FILL_ShortType(type) \
  void Fill(type* p, const type& d) { \
    assert(sizeof(double)==sizeof(unsigned long long)); \
    static const unsigned int M=sizeof(unsigned long long)/sizeof(type); \
    union U { double d; unsigned long long ll; type s[M]; } u; \
    for(unsigned int i=0;i<M;++i) u.s[i]=d; \
    unsigned int n=size(p); \
    long nmodM=n%M, nu=n/M, nres=n-nmodM, one=1, zero=0; \
    BLAS<double>::Copy(&nu,&(u.d),&zero,reinterpret_cast<double*>(p),&one); \
    memcpy(p+nres,u.s,nmodM*sizeof(type)); \
  }
#else
#error "Duplicate Definition for Macro _FILL_ShortType"
#endif

namespace mysimulator {

  _FILL_ShortType(short)
  _FILL_ShortType(unsigned short)
  _FILL_ShortType(char)
  _FILL_ShortType(unsigned char)

}

#ifdef _FILL_ShortType
#undef _FILL_ShortType
#endif

#ifndef _FILL_VarConstType
#define _FILL_VarConstType(type) \
  template <typename T> \
  void Fill(type* p, const T& d) { type td=d; Fill(p,td); }
#else
#error "Duplicate Definition for Macro _FILL_VarConstType"
#endif

namespace mysimulator {

  _FILL_VarConstType(long double)
  _FILL_VarConstType(double)
  _FILL_VarConstType(float)
  _FILL_VarConstType(long long)
  _FILL_VarConstType(unsigned long long)
  _FILL_VarConstType(int)
  _FILL_VarConstType(unsigned int)
  _FILL_VarConstType(long)
  _FILL_VarConstType(unsigned long)
  _FILL_VarConstType(short)
  _FILL_VarConstType(unsigned short)
  _FILL_VarConstType(char)
  _FILL_VarConstType(unsigned char)

}

#ifdef _FILL_VarConstType
#undef _FILL_VarConstType
#endif

#endif

