
#ifndef _Array_1D_Fill_H_
#define _Array_1D_Fill_H_

#include "array/1d/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T1,typename T2>
  void Fill(Array1D<T1>& V, const T2& d, unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) V[i]=d;
  }

}

#include "linear-algebra/blas.h"

namespace mysimulator {

  void BlasFill(Array1D<double>& V,const double& d,unsigned int n) {
    assert(n<=V.Size());
    long m=n, one=1, zero=0;
    BLAS<double>::Copy(&m,const_cast<double*>(&d),&zero,V._data,&one);
  }

  void BlasFill(Array1D<float>& V,const float& d,unsigned int n) {
    assert(n<=V.Size());
    long m=n, one=1, zero=0;
    BLAS<float>::Copy(&m,const_cast<float*>(&d),&zero,V._data,&one);
  }

  void BlasFill(Array1D<long double>& V, const long double& d, unsigned int n) {
    assert(sizeof(long double)==3*sizeof(double));
    assert(n<=V.Size());
    long m=n, three=3, zero=0;
    double *p=reinterpret_cast<double*>(V._data);
    double *q=reinterpret_cast<double*>(const_cast<long double*>(&d));
    BLAS<double>::Copy(&m,q,  &zero,p,  &three);
    BLAS<double>::Copy(&m,q+1,&zero,p+1,&three);
    BLAS<double>::Copy(&m,q+2,&zero,p+2,&three);
  }

}

#ifndef _FILL_EqType
#define _FILL_EqType(Type,EType) \
  void BlasFill(Array1D<Type>& V,const Type& d,unsigned int n) { \
    assert(sizeof(Type)==sizeof(EType)); \
    assert(n<=V.Size()); \
    long m=n, one=1, zero=0; \
    BLAS<EType>::Copy(&m,reinterpret_cast<EType*>(const_cast<Type*>(&d)),&zero,\
                         reinterpret_cast<EType*>(V._data),&one); \
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

  void MemFill(Array1D<char>& V,const char& d,unsigned int n) {
    memset(V._data,d,n);
  }
  void MemFill(Array1D<char>& V,const unsigned char& d,unsigned int n) {
    memset(V._data,d,n);
  }
  void MemFill(Array1D<unsigned char>& V,const char& d,unsigned int n) {
    memset(V._data,d,n);
  }
  void MemFill(Array1D<unsigned char>& V,const unsigned char& d,unsigned int n){
    memset(V._data,d,n);
  }

}

#endif

