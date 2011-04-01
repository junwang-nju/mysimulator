
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
  void fill(UniqueParameter64Bit& P, const int& i) {
    copy(P.idata[0],i);
    copy(P.idata[1],i);
  }
  void fill(UniqueParameter64Bit& P, const unsigned int& u) {
    copy(P.udata[0],u);
    copy(P.udata[1],u);
  }

  void fill(UniqueParameter64Bit& P, const short& s) {
    short *sp=P.sdata;
    short *pend=sp+4;
    for(;sp!=pend;) copy(*(sp++),s);
  }

  void fill(UniqueParameter64Bit& P, const char& c) {
    char *cp=P.cdata;
    char *pend=cp+8;
    for(;cp!=pend;) copy(*(cp++),c);
  }

  template <typename T>
  void fill(UniqueParameter64Bit& P, const T* d) {
    P.ull=*reinterpret_cast<const unsigned long long*>(d);
  }

  void fill(UniqueParameter64Bit& P, const float& f1, const float& f2) {
    P.fdata[0]=f1;  P.fdata[1]=f2;
  }

  void fill(UniqueParameter64Bit& P, const int& i1, const int& i2) {
    P.idata[0]=i1;    P.idata[1]=i2;
  }

  void fill(UniqueParameter64Bit& P,
            const unsigned int& u1, const unsigned int& u2) {
    P.udata[0]=u1;    P.udata[1]=u2;
  }

  void fill(UniqueParameter64Bit& P, const short& s1, const short& s2,
            const short& s3, const short& s4) {
    P.sdata[0]=s1;  P.sdata[1]=s2;  P.sdata[2]=s3;  P.sdata[3]=s4;
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

}

#endif
