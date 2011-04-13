
#ifndef _Unique_Parameter_128bit_Fill_H_
#define _Unique_Parameter_128bit_Fill_H_

#include "unique-parameter/128bit/interface.h"
#include "unique-parameter/128bit/copy.h"
#include <cstring>

namespace mysimulator {

#ifdef _Have_SSE2

  void fill(UniqueParameter128Bit& P, const __m128i& i) { copy(P,i); }
  void fill(UniqueParameter128Bit& P, const __m128d& d) { copy(P,d); }
  void fill(UniqueParameter128Bit& P, const double& d) { P.sd=_mm_set_pd(d,d); }
  void fill(UniqueParameter128Bit& P, const float& f) {
    P.si=_mm_set_ps(f,f,f,f);
  }
  void fill(UniqueParameter128Bit& P, const unsigned long long& ull) {
    double *d=reinterpret_cast<double*>(const_cast<unsigned long long*>(&ull));
    P.sd=_mm_set_pd(*d,*d);
  }
  void fill(UniqueParameter128Bit& P, const long long& ll) {
    double *d=reinterpret_cast<double*>(const_cast<long long*>(&ll));
    P.sd=_mm_set_pd(*d,*d);
  }
  void fill(UniqueParameter128Bit& P, const int& i) {
    P.si=_mm_set_epi32(i,i,i,i);
  }
  void fill(UniqueParameter128Bit& P, const unsigned int& u) {
    P.si=_mm_set_epi32(u,u,u,u);
  }
  void fill(UniqueParameter128Bit& P, const short& s) {
    P.si=_mm_set_epi16(s,s,s,s,s,s,s,s);
  }
  void fill(UniqueParameter128Bit& P, const unsigned short& s) {
    P.si=_mm_set_epi16(s,s,s,s,s,s,s,s);
  }
  void fill(UniqueParameter128Bit& P, const char& c) {
    P.si=_mm_set_epi8(c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c);
  }
  void fill(UniqueParameter128Bit& P, const unsigned char& c) {
    P.si=_mm_set_epi8(c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c);
  }

  void fill(UniqueParameter128Bit& P, const double& d1, const double& d2) {
    p.sd=_mm_set_pd(d2,d1);
  }
  void fill(UniqueParameter128Bit& P, const  float& f1, const float& f2,
            const float& f3, const float& f4) {
    P.sd=_mm_set_ps(f4,f3,f2,f1);
  }
  void fill(UniqueParameter128Bit& P, const unsigned long long& ull1,
            const unsigned long long& ull2) {
    P.sd=_mm_set_pd(*reinterpret_cast<const double*>(&ull2),
                    *reinterpret_cast<const double*>(&ull1));
  }
  void fill(UniqueParameter128Bit& P, const long long& ll1,
            const long long& ll2) {
    P.sd=_mm_set_pd(*reinterpret_cast<const double*>(&ll2),
                    *reinterpret_cast<const double*>(&ll1));
  }
  void fill(UniqueParameter128Bit& P, const int& i1, const int& i2,
            const int& i3, const int& i4) {
    P.si=_mm_set_epi32(i4,i3,i2,i1);
  }
  void fill(UniqueParameter128Bit& P, const unsigned int& u1,
            const unsigned int& u2, const unsigned int& u3,
            const unsigned int& u4) {
    P.si=_mm_set_epi32(u4,u3,u2,u1);
  }
  void fill(UniqueParameter128Bit& P, const short& s1, const short& s2,
            const short& s3, const short& s4, const short& s5,
            const short& s6, const short& s7, const short& s8) {
    P.si=_mm_set_epi16(s8,s7,s6,s5,s4,s3,s2,s1);
  }

  template <typename T>
  void fill(UniqueParameter128Bit& P, const T* d) {
    P.sd=_mm_loadu_pd(reinterpret_cast<const double*>(d));
  }

#else

  void fill(UniqueParameter128Bit& P, const double& d) {
    dcopy_(const_cast<long*>(&lTwo),const_cast<double*>(&d),
           const_cast<long*>(&lZero),P.d,const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const float& f) {
    scopy_(const_cast<long*>(&lFour),const_cast<float*>(&f),
           const_cast<long*>(&lZero),P.f,const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const unsigned long long& ull) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<unsigned long long*>(&ull)),
           const_cast<long*>(&lZero),P.d,const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const long long& ll) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<long long*>(&ll)),
           const_cast<long*>(&lZero),P.d,const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const int& i) {
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<int*>(&i)),
           const_cast<long*>(&lZero),P.f,const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const unsigned int& u) {
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&u)),
           const_cast<long*>(&lZero),P.f,const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const short& s) {
    short *sp=P.s;
    short *pend=sp+8;
    for(;sp!=pend;) copy(*(sp++),s);
  }
  void fill(UniqueParameter128Bit& P, const unsigned short& s) {
    unsigned short *sp=P.us;
    unsigned short *pend=sp+8;
    for(;sp!=pend;) copy(*(sp++),s);
  }
  void fill(UniqueParameter128Bit& P, const char& c) {
    memset(P.c,c,16);
  }
  void fill(UniqueParameter128Bit& P, const unsigned char& c) {
    memset(P.c,c,16);
  }

  void fill(UniqueParameter128Bit& P, const double& d1, const double& d2) {
    P.d[0]=d1;    P.d[1]=d2;
  }
  void fill(UniqueParameter128Bit& P, const  float& f1, const float& f2,
            const float& f3, const float& f4) {
    P.f[0]=f1;  P.f[1]=f2;  P.f[2]=f3;    P.f[3]=f4;
  }
  void fill(UniqueParameter128Bit& P, const unsigned long long& ull1,
            const unsigned long long& ull2) {
    P.ull[0]=ull1;    P.ull[1]=ull2;
  }
  void fill(UniqueParameter128Bit& P, const long long& ll1,
            const long long& ll2) {
    P.ll[0]=ll1;    P.ll[1]=ll2;
  }
  void fill(UniqueParameter128Bit& P, const int& i1, const int& i2,
            const int& i3, const int& i4) {
    P.i[0]=i1;  P.i[1]=i2;    P.i[2]=i3;    P.i[3]=i4;
  }
  void fill(UniqueParameter128Bit& P, const unsigned int& u1,
            const unsigned int& u2, const unsigned int& u3,
            const unsigned int& u4) {
    P.u[0]=u1;  P.u[1]=u2;    P.u[2]=u3;    P.u[3]=u4;
  }

  template <typename T>
  void fill(UniqueParameter128Bit& P, const T* d) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<T*>(d)),
           const_cast<long*>(&lOne),P.d,const_cast<long*>(&lOne));
  }

#endif

  void fill(UniqueParameter128Bit& P, const long double& ld) { copy(P.ld,ld); }





}

#include "vector/interface.h"

namespace mysimulator {

  void fill(Vector<UniqueParameter128Bit>& v, const UniqueParameter128Bit& P) {
    assert(IsValid(v));
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

