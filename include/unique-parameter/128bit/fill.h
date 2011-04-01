
#ifndef _Unique_Parameter_128bit_Fill_H_
#define _Unique_Parameter_128bit_Fill_H_

#include "unique-parameter/128bit/interface.h"

namespace mysimulator {

  void fill(UniqueParameter128Bit& P, const long double& ld) { copy(P.ld,ld); }

  void fill(UniqueParameter128Bit& P, const double& d) {
#ifdef _Have_SSE2
    P.sd=_mm_set_pd(d,d);
#else
    dcopy_(const_cast<long*>(&lTwo),const_cast<double*>(&d),
           const_cast<long*>(&lZero),P.d,const_cast<long*>(&lOne));
#endif
  }

  void fill(UniqueParameter128Bit& P, const float& f) {
#ifdef _Have_SSE2
    int i=*reinterpret_cast<int*>(const_cast<float*>(&f));
    P.si=_mm_set_epi32(i,i,i,i);
#else
    scopy_(const_cast<long*>(&lFour),const_cast<float*>(&f),
           const_cast<long*>(&lZero),P.f,const_cast<long*>(&lOne));
#endif
  }

  void fill(UniqueParameter128Bit& P, const unsigned long long& ull) {
#ifdef _Have_SSE2
    double d=*reinterpret_cast<double*>(const_cast<unsigned long long*>(&ull));
    P.sd=_mm_set_pd(d,d);
#else
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<unsigned long long*>(&ull)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(P.ull),
           const_cast<long*>(&lOne));
#endif
  }

  void fill(UniqueParameter128Bit& P, const int& i) {
#ifdef _Have_SSE2
    P.si=_mm_set_epi32(i,i,i,i);
#else
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<int*>(&i)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(P.i),
           const_cast<long*>(&lOne));
#endif
  }

  void fill(UniqueParameter128Bit& P, const unsigned int& u) {
#ifdef _Have_SSE2
    P.si=_mm_set_epi32(u,u,u,u);
#else
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&u)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(P.u),
           const_cast<long*>(&lOne));
#endif
  }

  void fill(UniqueParameter128Bit& P, const short& s) {
    short *sp=P.s;
    short *pend=sp+8;
    for(;sp!=pend;) copy(*(sp++),s);
  }

  void fill(UniqueParameter128Bit& P, const char& c) {
    char *cp=P.c;
    char *pend=cp+16;
    for(;cp!=pend;) copy(*(cp++),c);
  }

  template <typename T>
  void fill(UniqueParameter128Bit& P, const T* d) {
#ifdef _Have_SSE2
    const double *pd=reinterpret_cast<const double*>(d);
    P.sd=_mm_set_pd(*pd,*(pd+1));
#else
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<T*>(d)),
           const_cast<long*>(&lOne),P.d,const_cast<long*>(&lOne));
#endif
  }

  void fill(UniqueParameter128Bit& P, const double& d1, const double& d2) {
#ifdef _Have_SSE2
    p.sd=_mm_set_pd(d1,d2);
#else
    P.d[0]=d1;    P.d[1]=d2;
#endif
  }

  void fill(UniqueParameter128Bit& P, const  float& f1, const float& f2,
            const float& f3, const float& f4) {
#ifdef _Have_SSE2
    P.si=_mm_set_epi32(*reinterpret_cast<const int*>(&f1),
                       *reinterpret_cast<const int*>(&f2),
                       *reinterpret_cast<const int*>(&f3),
                       *reinterpret_cast<const int*>(&f4));
#else
    P.f[0]=f1;  P.f[1]=f2;  P.f[2]=f3;    P.f[3]=f4;
#endif
  }

  void fill(UniqueParameter128Bit& P, const unsigned long long& ull1,
            const unsigned long long& ull2) {
#ifdef _Have_SSE2
    P.sd=_mm_set_pd(*reinterpret_cast<const double*>(&ull1),
                    *reinterpret_cast<const double*>(&ull2));
#else
    P.ull[0]=ull1;    P.ull[1]=ull2;
#endif
  }

  void fill(UniqueParameter128Bit& P, const int& i1, const int& i2,
            const int& i3, const int& i4) {
#ifdef _Have_SSE2
    P.si=_mm_set_epi32(i1,i2,i3,i4);
#else
    P.i[0]=i1;  P.i[1]=i2;    P.i[2]=i3;    P.i[3]=i4;
#endif
  }

  void fill(UniqueParameter128Bit& P, const unsigned int& u1,
            const unsigned int& u2, const unsigned int& u3,
            const unsigned int& u4) {
#ifdef _Have_SSE2
    P.si=_mm_set_epi32(u1,u2,u3,u4);
#else
    P.u[0]=u1;  P.u[1]=u2;    P.u[2]=u3;    P.u[3]=u4;
#endif
  }

}

#include "vector/interface.h"

namespace mysimulator {

  void fill(Vector<UniqueParameter128Bit>& v, const UniqueParameter128Bit& P) {
    dcopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
           reinterpret_cast<double*>(const_cast<UniqueParameter128Bit*>(&P)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lTwo));
    dcopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
           reinterpret_cast<double*>(const_cast<UniqueParameter128Bit*>(&P))+1,
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v())+1,
           const_cast<long*>(&lTwo));
  }

}

#endif

