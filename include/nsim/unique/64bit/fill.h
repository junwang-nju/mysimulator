
#ifndef _Unique_64Bit_Fill_H_
#define _Unique_64Bit_Fill_H_

#include "unique/64bit/interface.h"

namespace mysimulator {

  void Fill(Unique64Bit& U,const double& d) { U.d=d; }
  void Fill(Unique64Bit& U,const float& f1,const float& f2) {
    U.fv[0]=f1; U.fv[1]=f2;
  }
  void Fill(Unique64Bit& U,const float& f) { Fill(U,f,f); }
  void Fill(Unique64Bit& U,const long long& ll) { U.ll=ll; }
  void Fill(Unique64Bit& U,const unsigned long long& ull) { U.ull=ull; }
  void Fill(Unique64Bit& U,const int i1,const int i2) {
    U.iv[0]=i1; U.iv[1]=i2;
  }
  void Fill(Unique64Bit& U,const int i) { Fill(U,i,i); }
  void Fill(Unique64Bit& U,const unsigned int u1,const unsigned int u2) {
    U.uv[0]=u1; U.uv[1]=u2;
  }
  void Fill(Unique64Bit& U,const unsigned int u) { Fill(U,u,u); }
  void Fill(Unique64Bit& U,const long l1,const long l2) {
    U.lv[0]=l1; U.lv[1]=l2;
  }
  void Fill(Unique64Bit& U,const long l) { Fill(U,l,l); }
  void Fill(Unique64Bit& U,const unsigned long ul1,const unsigned long ul2) {
    U.ulv[0]=ul1; U.ulv[1]=ul2;
  }
  void Fill(Unique64Bit& U,const unsigned long ul) { Fill(U,ul,ul); }
  void Fill(Unique64Bit& U,
            const short s1,const short s2,const short s3,const short s4) {
    U.sv[0]=s1; U.sv[1]=s2; U.sv[2]=s3; U.sv[3]=s4;
  }
  void Fill(Unique64Bit& U,const short s) { Fill(U,s,s,s,s); }
  void Fill(Unique64Bit& U,const unsigned short us1,const unsigned int us2,
                           const unsigned short us3,const unsigned int us4) {
    U.usv[0]=us1; U.usv[1]=us2; U.usv[2]=us3; U.usv[3]=us4;
  }
  void Fill(Unique64Bit& U,const unsigned short us) { Fill(U,us,us,us,us); }
  void Fill(Unique64Bit& U,
            const char c1,const char c2,const char c3,const char c4,
            const char c5,const char c6,const char c7,const char c8) {
    U.cv[0]=c1; U.cv[1]=c2; U.cv[2]=c3; U.cv[3]=c4;
    U.cv[4]=c5; U.cv[5]=c6; U.cv[6]=c7; U.cv[7]=c8;
  }
  void Fill(Unique64Bit& U,const char c) { Fill(U,c,c,c,c,c,c,c,c); }
  void Fill(Unique64Bit& U,const unsigned char uc1,const unsigned char uc2,
                           const unsigned char uc3,const unsigned char uc4,
                           const unsigned char uc5,const unsigned char uc6,
                           const unsigned char uc7,const unsigned char uc8) {
    U.ucv[0]=uc1; U.ucv[1]=uc2; U.ucv[2]=uc3; U.ucv[3]=uc4;
    U.ucv[4]=uc5; U.ucv[5]=uc6; U.ucv[6]=uc7; U.ucv[7]=uc8;
  }
  void Fill(Unique64Bit& U,const unsigned char uc) {
    Fill(U,uc,uc,uc,uc,uc,uc,uc,uc);
  }

}

#include "array/1d/fill.h"
#include "unique/64bit/copy.h"

namespace mysimulator {

  void Fill(Array1D<Unique64Bit>& V,const Unique64Bit& U,unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) Copy(V[i],U);
  }

  template <typename T>
  void Fill(Array1D<Unique64Bit>& V,const T& d,unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) Fill(V[i],d);
  }

  void BlasFill(Array1D<Unique64Bit>& V,const Unique64Bit& U,unsigned int n) {
    assert(n<=V.Size());
    long m=n, one=1, zero=0;
    BLAS<double>::Copy(
        &m,reinterpret_cast<double*>(const_cast<Unique64Bit*>(&U)),&zero,
           reinterpret_cast<double*>(V._data),&one);
  }

}

#ifndef _FILL
#define _FILL(T,ET) \
  void BlasFill(Array1D<Unique64Bit>& V,const T& d,unsigned int n) { \
    assert(sizeof(T)==sizeof(ET)); \
    assert(n<=V.Size()); \
    long m=n*sizeof(Unique64Bit)/sizeof(T), one=1, zero=0; \
    BLAS<ET>::Copy(&m,reinterpret_cast<ET*>(const_cast<T*>(&d)),&zero,\
                      reinterpret_cast<ET*>(V._data),&one); \
  }
#else
#error "Duplicate Definition for Macro _FILL"
#endif

namespace mysimulator {

  _FILL(double,double)
  _FILL(long long,double)
  _FILL(unsigned long long,double)
  _FILL(float,float)
  _FILL(int,float)
  _FILL(unsigned int,float)
  _FILL(long,float)
  _FILL(unsigned long,float)

}

#ifdef _FILL
#undef _FILL
#endif

namespace mysimulator {

  void MemFill(Array1D<Unique64Bit>& V,const char& d,unsigned int n) {
    assert(sizeof(Unique64Bit)==8*sizeof(char));
    assert(n<=V.Size());
    memset(V._data,d,8*n);
  }

  void MemFill(Array1D<Unique64Bit>& V,const unsigned char& d,unsigned int n) {
    assert(sizeof(Unique64Bit)==8*sizeof(char));
    assert(n<=V.Size());
    memset(V._data,d,8*n);
  }

}

#endif

