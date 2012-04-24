
#ifndef _Unique_128Bit_Fill_H_
#define _Unique_128Bit_Fill_H_

#include "unique/128bit/interface.h"

namespace mysimulator {

  void Fill(Unique128Bit& U,const long double& ld) { U.ld=ld; }

}

#include "unique/128bit/copy.h"

#ifdef _HAVE_SSE2

namespace mysimulator {

  void Fill(Unique128Bit& U,const __m128i& si) { Copy(U,si); }
  void Fill(Unique128Bit& U,const __m128d& sd) { Copy(U,sd); }
  void Fill(Unique128Bit& U,const double& d1,const double& d2) {
    U.sd=_mm_set_pd(d2,d1);
  }
  void Fill(Unique128Bit& U,const double& d) { U.sd=_mm_set1_pd(d); }
  void Fill(Unique128Bit& U,
      const unsigned long long& ull1,const unsigned long long& ull2) {
    double *p1=reinterpret_cast<const double*>(&ull1);
    double *p2=reinterpret_cast<const double*>(&ull2);
    Fill(U,*p1,*p2);
  }
  void Fill(Unique128Bit& U,const unsigned long long& ull) {
    double *p=reinterpret_cast<const double*>(&ull);
    Fill(U,*p);
  }
  void Fill(Unique128Bit& U,const long long& ll1,const long long& ll2) {
    double *p1=reinterpret_cast<const double*>(&ll1);
    double *p2=reinterpret_cast<const double*>(&ll2);
    Fill(U,*p1,*p2);
  }
  void Fill(Unique128Bit& U,const long long& ll) {
    double *p=reinterpret_cast<const double*>(&ll);
    Fill(U,*p);
  }
  void Fill(Unique128Bit& U,
            const float& f1,const float& f2,const float& f3,const float& f4) {
    U.sm=_mm_set_ps(f4,f3,f2,f1);
  }
  void Fill(Unique128Bit& U,const float& f) { U.sm=_mm_set1_ps(f); }
  void Fill(Unique128Bit& U,int i1,int i2,int i3,int i4) {
    U.si=_mm_set_epi32(i4,i3,i2,i1);
  }
  void Fill(Unique128Bit& U,int i) { U.si=_mm_set1_epi32(i); }
  void Fill(Unique128Bit& U,
            unsigned int u1,unsigned int u2,unsigned int u3,unsigned int u4) {
    U.si=_mm_set_epi32(u4,u3,u2,u1);
  }
  void Fill(Unique128Bit& U,unsigned int u) { U.si=_mm_set1_epi32(u); }
  void Fill(Unique128Bit& U,long l1,long l2,long l3,long l4) {
    U.si=_mm_set_epi32(l4,l3,l2,l1);
  }
  void Fill(Unique128Bit& U,long l) { U.si=_mm_set1_epi32(l); }
  void Fill(Unique128Bit& U,unsigned long ul1,unsigned long ul2,
            unsigned long ul3,unsigned long ul4) {
    U.si=_mm_set_epi32(ul4,ul3,ul2,ul1);
  }
  void Fill(Unique128Bit& U,unsigned long ul) { U.si=_mm_set1_epi32(l); }
  void Fill(Unique128Bit& U,short s1,short s2,short s3,short s4,
            short s5,short s6,short s7,short s8) {
    U.si=_mm_set_epi16(s8,s7,s6,s5,s4,s3,s2,s1);
  }
  void Fill(Unique128Bit& U,short s) { U.si=_mm_set1_epi16(s); }
  void Fill(Unique128Bit& U,unsigned short us1,unsigned short us2,
            unsigned short us3,unsigned short us4,unsigned short us5,
            unsigned short us6,unsigned short us7,unsigned short us8) {
    U.si=_mm_set_epi16(us8,us7,us6,us5,us4,us3,us2,us1);
  }
  void Fill(Unique128Bit& U,unsigned short us) { U.si=_mm_set1_epi16(us); }
  void Fill(Unique128Bit& U,char c1,char c2,char c3,char c4,char c5,char c6,
            char c7,char c8,char c9,char ca,char cb,char cc,char cd,char ce,
            char cf,char cg) {
    U.si=_mm_set_epi8(cg,cf,ce,cd,cc,cb,ca,c9,c8,c7,c6,c5,c4,c3,c2,c1);
  }
  void Fill(Unique128Bit& U,char c) { U.si=_mm_set1_epi8(c); }
  void Fill(Unique128Bit& U,unsigned char c1,unsigned char c2,unsigned char c3,
            unsigned char c4,unsigned char c5,unsigned char c6,unsigned char c7,
            unsigned char c8,unsigned char c9,unsigned char ca,unsigned char cb,
            unsigned char cc,unsigned char cd,unsigned char ce,unsigned char cf,
            unsigned char cg) {
    U.si=_mm_set_epi8(cg,cf,ce,cd,cc,cb,ca,c9,c8,c7,c6,c5,c4,c3,c2,c1);
  }
  void Fill(Unique128Bit& U,unsigned char c) { U.si=_mm_set1_epi8(c); }

}

#else

namespace mysimulator {

  void Fill(Unique128Bit& U,const double& d1,const double& d2) {
    U.dv[0]=d1; U.dv[1]=d2;
  }
  void Fill(Unique128Bit& U,const double& d) { Fill(U,d,d); }
  void Fill(Unique128Bit& U,const long long& ll1,const long long& ll2) {
    U.llv[0]=ll1; U.llv[1]=ll2;
  }
  void Fill(Unique128Bit& U,const long long& ll) { Fill(U,ll,ll); }
  void Fill(Unique128Bit& U,
            const unsigned long long& ull1,const unsigned long long& ull2) {
    U.ullv[0]=ull1; U.ullv[1]=ull2;
  }
  void Fill(Unique128Bit& U,const unsigned long long& ull) { Fill(U,ull,ull); }
  void Fill(Unique128Bit& U,
            const float& f1,const float& f2,const float& f3,const float& f4) {
    U.fv[0]=f1; U.fv[1]=f2; U.fv[2]=f3; U.fv[3]=f4;
  }
  void Fill(Unique128Bit& U,const float& f) { Fill(U,f,f,f,f); }
  void Fill(Unique128Bit& U,int i1,int i2,int i3,int i4) {
    U.iv[0]=i1; U.iv[1]=i2; U.iv[2]=i3; U.iv[3]=i4;
  }
  void Fill(Unique128Bit& U,int i) { Fill(U,i,i,i,i); }
  void Fill(Unique128Bit& U,
            unsigned int u1,unsigned int u2,unsigned int u3,unsigned int u4) {
    U.uv[0]=u1; U.uv[1]=u2; U.uv[2]=u3; U.uv[3]=u4;
  }
  void Fill(Unique128Bit& U,unsigned int u) { Fill(U,u,u,u,u); }
  void Fill(Unique128Bit& U,long l1,long l2,long l3,long l4) {
    U.lv[0]=l1; U.lv[1]=l2; U.lv[2]=l3; U.lv[3]=l4;
  }
  void Fill(Unique128Bit& U,long l) { Fill(U,l,l,l,l); }
  void Fill(Unique128Bit& U,unsigned long ul1,unsigned long ul2,
                            unsigned long ul3,unsigned long ul4) {
    U.ulv[0]=ul1; U.ulv[1]=ul2; U.ulv[2]=ul3; U.ulv[3]=ul4;
  }
  void Fill(Unique128Bit& U,unsigned long ul) { Fill(U,ul,ul,ul,ul); }
  void Fill(Unique128Bit& U,short s1,short s2,short s3,short s4,
                            short s5,short s6,short s7,short s8) {
    U.sv[0]=s1; U.sv[1]=s2; U.sv[2]=s3; U.sv[3]=s4; U.sv[4]=s5;
    U.sv[5]=s6; U.sv[6]=s7; U.sv[7]=s8;
  }
  void Fill(Unique128Bit& U,short s) { Fill(U,s,s,s,s,s,s,s,s); }
  void Fill(Unique128Bit& U,unsigned short us1,unsigned short us2,
            unsigned short us3,unsigned short us4,unsigned short us5,
            unsigned short us6,unsigned short us7,unsigned short us8) {
    U.usv[0]=us1; U.usv[1]=us2; U.usv[2]=us3; U.usv[3]=us4; U.usv[4]=us5;
    U.usv[5]=us6; U.usv[6]=us7; U.usv[7]=us8;
  }
  void Fill(Unique128Bit& U,unsigned short us) {
    Fill(U,us,us,us,us,us,us,us,us);
  }
  void Fill(Unique128Bit& U,char c1,char c2,char c3,char c4,char c5,char c6,
            char c7,char c8,char c9,char ca,char cb,char cc,char cd,char ce,
            char cf,char cg) {
    U.cv[0]=c1; U.cv[1]=c2; U.cv[2]=c3; U.cv[3]=c4; U.cv[4]=c5; U.cv[5]=c6;
    U.cv[6]=c7; U.cv[7]=c8; U.cv[8]=c9; U.cv[9]=ca; U.cv[10]=cb;U.cv[11]=cc;
    U.cv[12]=cd;U.cv[13]=ce;U.cv[14]=cf;U.cv[15]=cg;
  }
  void Fill(Unique128Bit& U,char c) { Fill(U,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c); }
  void Fill(Unique128Bit& U,unsigned char c1,unsigned char c2,unsigned char c3,
            unsigned char c4,unsigned char c5,unsigned char c6,unsigned char c7,
            unsigned char c8,unsigned char c9,unsigned char ca,unsigned char cb,
            unsigned char cc,unsigned char cd,unsigned char ce,unsigned char cf,
            unsigned char cg) {
    U.ucv[0]=c1;  U.ucv[1]=c2;  U.ucv[2]=c3;  U.ucv[3]=c4;  U.ucv[4]=c5;
    U.ucv[5]=c6;  U.ucv[6]=c7;  U.ucv[7]=c8;  U.ucv[8]=c9;  U.ucv[9]=ca;
    U.ucv[10]=cb; U.ucv[11]=cc; U.ucv[12]=cd; U.ucv[13]=ce; U.ucv[14]=cf;
    U.ucv[15]=cg;
  }
  void Fill(Unique128Bit& U,unsigned char uc) {
    Fill(U,uc,uc,uc,uc,uc,uc,uc,uc,uc,uc,uc,uc,uc,uc,uc,uc);
  }

}

#endif

#include "unique/64bit/interface.h"

namespace mysimulator {

  void Fill(Unique128Bit& U,const Unique64Bit& U64) { Fill(U,U64.d); }

}

#include "array/1d/fill.h"

namespace mysimulator {

  void Fill(Array1D<Unique128Bit>& V,const Unique128Bit& U,unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) Copy(V[i],U);
  }

  template <typename T>
  void Fill(Array1D<Unique128Bit>& V,const T& d,unsigned int n) {
    assert(n<=V.Size());
    for(unsigned int i=0;i<n;++i) Fill(V[i],d);
  }

  void BlasFill(Array1D<Unique128Bit>& V,const Unique128Bit& U,unsigned int n) {
    assert(n<=V.Size());
    long m=n,two=2,zero=0;
    double* p=reinterpret_cast<double*>(V._data);
    double* q=reinterpret_cast<double*>(const_cast<Unique128Bit*>(&U));
    BLAS<double>::Copy(&m,q,  &zero,p,  &two);
    BLAS<double>::Copy(&m,q+1,&zero,p+1,&two);
  }

  void BlasFill(Array1D<Unique128Bit>& V,const long double& ld,unsigned int n) {
    assert(sizeof(long double)==3*sizeof(float));
    assert(sizeof(double)==2*sizeof(float));
    assert(n<=V.Size());
    long m=n, two=2, four=4, zero=0;
    double* p=reinterpret_cast<double*>(V._data);
    double* q=reinterpret_cast<double*>(const_cast<long double*>(&ld));
    BLAS<double>::Copy(&m,q,&zero,p,&two);
    float* pf=reinterpret_cast<float*>(p+1);
    float* qf=reinterpret_cast<float*>(q+1);
    BLAS<float>::Copy(&m,qf,&zero,pf,&four);
  }

}

#ifndef _FILL
#define _FILL(T,ET) \
  void BlasFill(Array1D<Unique128Bit>& V,const T& d,unsigned int n) { \
    assert(sizeof(T)==sizeof(ET)); \
    assert(n<=V.Size()); \
    long m=n*sizeof(Unique128Bit)/sizeof(T), one=1, zero=0; \
    BLAS<ET>::Copy(&m,reinterpret_cast<ET*>(const_cast<T*>(&d)),&zero,\
                      reinterpret_cast<ET*>(V._data),&one); \
  }
#else
#error "Duplicate Definition for Macro _FILL"
#endif

namespace mysimulator {

  _FILL(double,double)
  _FILL(unsigned long long,double)
  _FILL(long long,double)
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

  void Fill(Array1D<Unique128Bit>& V,const char& d,unsigned int n) {
    assert(sizeof(Unique128Bit)==16*sizeof(char));
    assert(n<=V.Size());
    memset(V._data,d,8*n);
  }

  void Fill(Array1D<Unique128Bit>& V,const unsigned char& d,unsigned int n) {
    assert(sizeof(Unique128Bit)==16*sizeof(char));
    assert(n<=V.Size());
    memset(V._data,d,8*n);
  }

}

#endif

