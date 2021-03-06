
#ifndef _Unique_Parameter_128bit_H_
#define _Unique_Parameter_128bit_H_

#include "data/basic/vector.h"

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

  union UniqueParameter128b {
  
    typedef  UniqueParameter128b Type;

#ifdef HAVE_SSE2
    __m128i si;
    __m128d sd;
#endif
    long double ld;
    double d[2];
    float f[4];
    unsigned int u[4];
    int i[4];
    unsigned long long int ull[2];
    void* ptr[4];
    
    UniqueParameter128b() { ull[0]=0; ull[1]=0; }
    UniqueParameter128b(const Type& P) {
      Error("Cannot create Unique Parameter 128bit");
    }
    Type& operator=(const Type& P) {
      Error("Cannot copy Unique Parameter 128bit");
      return *this;
    }

  };

  void copy(UniqueParameter128b& P, const UniqueParameter128b& cP) {
    P.ull[0]=cP.ull[0]; P.ull[1]=cP.ull[1];
  }
  void copy(UniqueParameter128b& P, const long double& ld) { P.ld=ld; }
  void copy(UniqueParameter128b& P, const double d[2]) {
    dcopy_(const_cast<long*>(&lTwo),
           const_cast<double*>(d),const_cast<long*>(&lOne),
           P.d,const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P, const double& d) {
    dcopy_(const_cast<long*>(&lTwo),
           const_cast<double*>(&d),const_cast<long*>(&lZero),
           P.d,const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P, const float f[4]) {
    scopy_(const_cast<long*>(&lFour),const_cast<float*>(f),
           const_cast<long*>(&lOne),P.f,const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P, const float& f) {
    scopy_(const_cast<long*>(&lFour),const_cast<float*>(&f),
           const_cast<long*>(&lZero),P.f,const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P, const unsigned int u[4]) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<unsigned int*>(u)),
           const_cast<long*>(&lOne),P.d,const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P, const unsigned int& u) {
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&u)),
           const_cast<long*>(&lZero),
           reinterpret_cast<float*>(P.u),const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P,const int i[4]) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<int*>(i)),
           const_cast<long*>(&lOne),P.d,const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P, const int& i) {
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<int*>(&i)),
           const_cast<long*>(&lZero),
           reinterpret_cast<float*>(P.i),const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P,const unsigned long long int l[2]) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<unsigned long long int*>(l)),
           const_cast<long*>(&lOne),P.d,const_cast<long*>(&lOne));
  }
  void copy(UniqueParameter128b& P,const unsigned long long int& l) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<unsigned long long int*>(&l)),
           const_cast<long*>(&lZero),P.d,const_cast<long*>(&lOne));
  }

  template <typename T>
  void copy(UniqueParameter128b& P,T* const ptr[4]) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<T**>(ptr)),
           const_cast<long*>(&lOne),P.d,const_cast<long*>(&lOne));
  }
  template <typename T>
  void copy(UniqueParameter128b& P, const T*& ptr) {
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<T**>(&ptr)),
           const_cast<long*>(&lZero),
           reinterpret_cast<float*>(P.i),const_cast<long*>(&lOne));
  }

  void ccopy(UniqueParameter128b* P, const UniqueParameter128b* cP,
             const unsigned int size,
             const int off=iZero, const int coff=iZero) {
    long sz=size+size;
    dcopy_(&sz,
           reinterpret_cast<double*>(const_cast<UniqueParameter128b*>(cP))
           +coff+coff,const_cast<long*>(&lOne),
           reinterpret_cast<double*>(P)+off+off,const_cast<long*>(&lOne));
  }
  void copy(Vector<UniqueParameter128b>& P,
            const Vector<UniqueParameter128b>& cP) {
    unsigned int n=(P.size<cP.size?P.size:cP.size);
    ccopy(P.data,cP.data,n);
  }
  void dcopy(UniqueParameter128b* P, const UniqueParameter128b* cP,
             const unsigned int size,
             const int off=iZero, const int step=iOne,
             const int coff=iZero, const int cstep=iOne) {
    int doff=off+off, dcoff=coff+coff;
    long dstep=step+step, cdstep=cstep+cstep;
    dcopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&size)),
           reinterpret_cast<double*>(const_cast<UniqueParameter128b*>(cP))
           +dcoff,&cdstep,reinterpret_cast<double*>(P)+doff,&dstep);
    dcopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&size)),
           reinterpret_cast<double*>(const_cast<UniqueParameter128b*>(cP))
           +dcoff+1,&cdstep,reinterpret_cast<double*>(P)+doff+1,&dstep);
  }
  void copy(Vector<UniqueParameter128b>& P, const UniqueParameter128b& cP) {
    dcopy(P.data,&cP,P.size,iZero,iOne,iZero,iZero);
  }

}

#endif
