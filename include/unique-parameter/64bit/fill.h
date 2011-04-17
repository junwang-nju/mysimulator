
#ifndef _Unique_Parameter_64bit_Fill_H_
#define _Unique_Parameter_64bit_Fill_H_

#include "unique-parameter/64bit/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  void fill(UniqueParameter64Bit& P, const double& d) { copy(P.d,d); }

  void fill(UniqueParameter64Bit& P, const float& f) {
    copy(P.fdata[0],f);
    copy(P.fdata[1],f);
  }

  void fill(UniqueParameter64Bit& P, const unsigned long long& ull) {
    copy(P.ull,ull);
  }
  void fill(UniqueParameter64Bit& P, const long long& ll) {
    copy(P.ll,ll);
  }
  void fill(UniqueParameter64Bit& P, const int& i) {
    copy(P.i[0],i);
    copy(P.i[1],i);
  }
  void fill(UniqueParameter64Bit& P, const unsigned int& u) {
    copy(P.u[0],u);
    copy(P.u[1],u);
  }

  void fill(UniqueParameter64Bit& P, const unsigned short& s) {
    unsigned short *sp=P.us;
    unsigned short *pend=sp+4;
    for(;sp!=pend;) copy(*(sp++),s);
  }
  void fill(UniqueParameter64Bit& P, const short& s) {
    short *sp=P.s;
    short *pend=sp+4;
    for(;sp!=pend;) copy(*(sp++),s);
  }

  void fill(UniqueParameter64Bit& P, const unsigned char& c) {
    unsigned char *cp=P.uc;
    unsigned char *pend=cp+8;
    for(;cp!=pend;) copy(*(cp++),c);
  }
  void fill(UniqueParameter64Bit& P, const char& c) {
    char *cp=P.c;
    char *pend=cp+8;
    for(;cp!=pend;) copy(*(cp++),c);
  }

  template <typename T>
  void fill(UniqueParameter64Bit& P, const T* d) {
    P.ull=*reinterpret_cast<const unsigned long long*>(d);
  }

  void fill(UniqueParameter64Bit& P, const float& f1, const float& f2) {
    P.f[0]=f1;  P.f[1]=f2;
  }

  void fill(UniqueParameter64Bit& P,
            const unsigned int& i1, const unsigned int& i2) {
    P.u[0]=i1;    P.u[1]=i2;
  }
  void fill(UniqueParameter64Bit& P, const int& i1, const int& i2) {
    P.i[0]=i1;    P.i[1]=i2;
  }

  void fill(UniqueParameter64Bit& P,
            const unsigned short& s1, const unsigned short& s2,
            const unsigned short& s3, const unsigned short& s4) {
    P.us[0]=s1;  P.us[1]=s2;  P.us[2]=s3;  P.us[3]=s4;
  }
  void fill(UniqueParameter64Bit& P, const short& s1, const short& s2,
            const short& s3, const short& s4) {
    P.s[0]=s1;  P.s[1]=s2;  P.s[2]=s3;  P.s[3]=s4;
  }

  void fill(UniqueParameter64Bit& P,
            const unsigned char c1, const unsigned char c2,
            const unsigned char c3, const unsigned char c4,
            const unsigned char c5, const unsigned char c6,
            const unsigned char c7, const unsigned char c8) {
    P.uc[0]=c1;  P.uc[1]=c2;  P.uc[2]=c3;  P.uc[3]=c4;
    P.uc[4]=c5;  P.uc[5]=c6;  P.uc[6]=c7;  P.uc[7]=c8;
  }
  void fill(UniqueParameter64Bit& P,
            const char c1, const char c2, const char c3, const char c4,
            const char c5, const char c6, const char c7, const char c8) {
    P.c[0]=c1;  P.c[1]=c2;  P.c[2]=c3;  P.c[3]=c4;
    P.c[4]=c5;  P.c[5]=c6;  P.c[6]=c7;  P.c[7]=c8;
  }


}

#include "vector/interface.h"
#include "linear-algebra/blas.h"

namespace mysimulator {

  void fill(Vector<UniqueParameter64Bit>& v, const unsigned long long& d) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<unsigned long long*>(&d)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void fill(Vector<UniqueParameter64Bit>& v, const double& d) {
    fill(v,*reinterpret_cast<const unsigned long long*>(&d));
  }

  void fill(Vector<UniqueParameter64Bit>& v, const UniqueParameter64Bit& d) {
    fill(v,d.ull);
  }

  void fill(Vector<UniqueParameter64Bit>& v, const float& f) {
    assert(IsValid(v));
    long n=v.size+v.size;
    scopy_(&n,const_cast<float*>(&f),const_cast<long*>(&lZero),
           reinterpret_cast<float*>(v()),const_cast<long*>(&lOne));
  }

  void fill(Vector<UniqueParameter64Bit>& v, const int& i) {
    assert(IsValid(v));
    long n=v.size+v.size;
    scopy_(&n,reinterpret_cast<float*>(const_cast<int*>(&i)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

  void fill(Vector<UniqueParameter64Bit>& v, const unsigned int& u) {
    assert(IsValid(v));
    long n=v.size+v.size;
    scopy_(&n,reinterpret_cast<float*>(const_cast<unsigned int*>(&u)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(v()),
           const_cast<long*>(&lOne));
  }

  void fill(Vector<UniqueParameter64Bit>& v, const unsigned char& c) {
    assert(IsValid(v));
    memset(v(),c,v.size*8);
  }

  void fill(Vector<UniqueParameter64Bit>& v, const char& c) {
    assert(IsValid(v));
    memset(v(),c,v.size*8);
  }

}

#endif
