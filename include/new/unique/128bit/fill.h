
#ifndef _Unique_128Bit_Fill_H_
#define _Unique_128Bit_Fill_H_

#include "unique/128bit/interface.h"

namespace mysimulator {

  void fill(Unique128Bit& U, const long double& ld) { U.ld=ld; }

}

#include "unique/128bit/copy.h"

#define _TYPE(type,a) reinterpret_cast<type*>(a)

#ifdef _Have_SSE2

namespace mysimulator {

  void fill(Unique128Bit& U, const __m128i& i) { copy(U,i); }
  void fill(Unique128Bit& U, const __m128d& d) { copy(U,d); }
  void fill(Unique128Bit& U, const double& d) { U.sd=_mm_set_pd(d,d); }
  void fill(Unique128Bit& U, const float& f) { U.sm=_mm_set_ps(f,f,f,f); }
  void fill(Unique128Bit& U, const unsigned long long& ull) {
    const double* pd=_TYPE(const double,&ull);
    U.sd=_mm_set_pd(*pd,*pd);
  }
  void fill(Unique128Bit& U, const long long& ll) {
    const double* pd=_TYPE(const double,ll);
    U.sd=_mm_set_pd(*pd,*pd);
  }
  void fill(Unique128Bit& U, const int& i) { U.si=_mm_set_epi32(i,i,i,i); }
  void fill(Unique128Bit& U, const unsigned int& u) {
    U.si=_mm_set_epi32(u,u,u,u);
  }
  void fill(Unique128Bit& U, const long& l) { U.si=_mm_set_epi32(l,l,l,l); }
  void fill(Unique128Bit& U, const unsigned long& l) {
    U.si=_mm_set_epi32(l,l,l,l);
  }
  void fill(Unique128Bit& U, const short& s) {
    U.si=_mm_set_epi16(s,s,s,s,s,s,s,s);
  }
  void fill(Unique128Bit& U, const unsigned short& s) {
    U.si=_mm_set_epi16(s,s,s,s,s,s,s,s);
  }
  void fill(Unique128Bit& U, const char& c) {
    U.si=_mm_set_epi8(c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c);
  }
  void fill(Unique128Bit& U, const unsigned char& c) {
    U.si=_mm_set_epi8(c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c);
  }

  void fill(Unique128Bit& U, const double& d1, const double& d2) {
    U.sd=_mm_set_pd(d2,d1);
  }
  void fill(Unique128Bit& U, const float& f1, const float& f2, const float& f3,
            const float& f4) { U.sm=_mm_set_ps(f4,f3,f2,f1); }
  void fill(Unique128Bit& U, const unsigned long long& l1,
            const unsigned long long& l2) {
    U.sd=_mm_set_pd(*_TYPE(const double,&l2),*_TYPE(const double,&l1));
  }
  void fill(Unique128Bit& U, const long long& l1, const long long& l2) {
    U.sd=_mm_set_pd(*_TYPE(const double,&l2),*_TYPE(const double,&l1));
  }
  void fill(Unique128Bit& U, const int& i1, const int& i2, const int& i3,
            const int& i4) { U.si=_mm_set_epi32(i4,i3,i2,i1); }
  void fill(Unique128Bit& U, const unsigned int& u1, const unsigned int& u2,
            const unsigned int& u3, const unsigned int& u4) {
    U.si=_mm_set_epi32(u4,u3,u2,u1);
  }
  void fill(Unique128Bit& U, const long& l1, const long& l2, const long& l3,
            const long& l4) { U.si=_mm_set_epi32(l4,l3,l2,l1); }
  void fill(Unique128Bit& U, const unsigned long& l1, const unsigned long& l2,
            const unsigned long& l3, const unsigned long& l4) {
    U.si=_mm_set_epi32(l4,l3,l2,l1);
  }
  void fill(Unique128Bit& U, const short& s1, const short& s2, const short& s3,
            const short& s4, const short& s5, const short& s6, const short& s7,
            const short& s8) {
    U.si=_mm_set_epi16(s8,s7,s6,s5,s4,s3,s2,s1);
  }
  void fill(Unique128Bit& U, const unsigned short& s1, const unsigned short& s2,
            const unsigned short& s3, const unsigned short& s4,
            const unsigned short& s5, const unsigned short& s6,
            const unsigned short& s7, const unsigned short& s8) {
    U.si=_mm_set_epi16(s8,s7,s6,s5,s4,s3,s2,s1);
  }
  void fill(Unique128Bit& U, const char& c1, const char& c2, const char& c3,
            const char& c4, const char& c5, const char& c6, const char& c7,
            const char& c8, const char& c9, const char& ca, const char& cb,
            const char& cc, const char& cd, const char& ce, const char& cf,
            const char& cg) {
    U.si=_mm_set_epi8(cg,cf,ce,cd,cc,cb,ca,c9,c8,c7,c6,c5,c4,c3,c2,c1);
  }
  void fill(Unique128Bit& U, const unsigned char& c1, const unsigned char& c2,
            const unsigned char& c3, const unsigned char& c4,
            const unsigned char& c5, const unsigned char& c6,
            const unsigned char& c7, const unsigned char& c8,
            const unsigned char& c9, const unsigned char& ca,
            const unsigned char& cb, const unsigned char& cc,
            const unsigned char& cd, const unsigned char& ce,
            const unsigned char& cf, const unsigned char& cg) {
    U.si=_mm_set_epi8(cg,cf,ce,cd,cc,cb,ca,c9,c8,c7,c6,c5,c4,c3,c2,c1);
  }

  template <typename T>
  void fill(Unique128Bit& U, const T* p) {
    U.sd=_mm_loadu_pd(_TYPE(const double,p));
  }

}

#else

#include "array/1d/content/fill.h"

#define _FILLU(type,n) \
  void fill(Unique128Bit& U,const type& d) {\
    _fill(_TYPE(type,&U),d,sizeof(double)*2/sizeof(type));\
  }

namespace mysimulator {

  _FILLU(double,n)
  _FILLU(float,n)
  _FILLU(long long,n)
  _FILLU(unsigned long long,n)
  _FILLU(int,n)
  _FILLU(unsigned int,n)
  _FILLU(long,n)
  _FILLU(unsigned long,n)
  _FILLU(short,n)
  _FILLU(unsigned short,n)
  _FILLU(char,n)
  _FILLU(unsigned char,n)

}

#undef _FILLU

namespace mysimulator {

  void fill(Unique128Bit& U, const double& d1, const double& d2) {
    U.d[0]=d1;  U.d[1]=d2;
  }
  void fill(Unique128Bit& U, const float& f1, const float& f2, const float& f3,
            const float& f4) {
    U.f[0]=f1;  U.f[1]=f2;  U.f[2]=f3;    U.f[3]=f4;
  }
  void fill(Unique128Bit& U, const long long& l1, const long long& l2) {
    U.ll[0]=l1; U.ll[1]=l2;
  }
  void fill(Unique128Bit& U, const unsigned long long& l1,
            const unsigned long long& l2) {
    U.ull[0]=l1; U.ull[1]=l2;
  }
  void fill(Unique128Bit& U, const int& i1, const int& i2, const int& i3,
            const int& i4) {
    U.i[0]=i1;  U.i[1]=i2;  U.i[2]=i3;  U.i[3]=i4;
  }
  void fill(Unique128Bit& U, const unsigned int& u1, const unsigned int& u2,
            const unsigned int& u3, const unsigned int& u4) {
    U.u[0]=u1;  U.u[1]=u2;  U.u[2]=u3;  U.u[3]=u4;
  }
  void fill(Unique128Bit& U, const long& l1, const long& l2, const long& l3,
            const long& l4) {
    U.l[0]=l1;  U.l[1]=l2;  U.l[2]=l3;  U.l[3]=l4;
  }
  void fill(Unique128Bit& U, const unsigned long& l1, const unsigned long& l2,
            const unsigned long& l3, const unsigned long& l4) {
    U.ul[0]=l1; U.ul[1]=l2; U.ul[2]=l3; U.ul[3]=l4;
  }
  void fill(Unique128Bit& U, const short& s1, const short& s2, const short& s3,
            const short& s4, const short& s5, const short& s6, const short& s7,
            const short& s8) {
    U.s[0]=s1;  U.s[1]=s2;  U.s[2]=s3;  U.s[3]=s4;
    U.s[4]=s5;  U.s[5]=s6;  U.s[6]=s7;  U.s[7]=s8;
  }
  void fill(Unique128Bit& U, const unsigned short& s1, const unsigned short& s2,
            const unsigned short& s3, const unsigned short& s4,
            const unsigned short& s5, const unsigned short& s6,
            const unsigned short& s7, const unsigned short& s8) {
    U.us[0]=s1;  U.us[1]=s2;  U.us[2]=s3;  U.us[3]=s4;
    U.us[4]=s5;  U.us[5]=s6;  U.us[6]=s7;  U.us[7]=s8;
  }
  void fill(Unique128Bit& U, const char& c1, const char& c2, const char& c3,
            const char& c4, const char& c5, const char& c6, const char& c7,
            const char& c8, const char& c9, const char& ca, const char& cb,
            const char& cc, const char& cd, const char& ce, const char& cf,
            const char& cg) {
    U.c[0]=c1;  U.c[1]=c2;  U.c[2]=c3;  U.c[3]=c4;  U.c[4]=c5;  U.c[5]=c6;
    U.c[6]=c7;  U.c[7]=c8;  U.c[8]=c9;  U.c[9]=ca;  U.c[10]=cb; U.c[11]=cc;
    U.c[12]=cd; U.c[13]=ce; U.c[14]=cf; U.c[15]=cg;
  }
  void fill(Unique128Bit& U, const unsigned char& c1, const unsigned char& c2,
            const unsigned char& c3, const unsigned char& c4,
            const unsigned char& c5, const unsigned char& c6,
            const unsigned char& c7, const unsigned char& c8,
            const unsigned char& c9, const unsigned char& ca,
            const unsigned char& cb, const unsigned char& cc,
            const unsigned char& cd, const unsigned char& ce,
            const unsigned char& cf, const unsigned char& cg) {
    U.uc[0]=c1;  U.uc[1]=c2;  U.uc[2]=c3;  U.uc[3]=c4;  U.uc[4]=c5;
    U.uc[5]=c6;  U.uc[6]=c7;  U.uc[7]=c8;  U.uc[8]=c9;  U.uc[9]=ca;
    U.uc[10]=cb; U.uc[11]=cc; U.uc[12]=cd; U.uc[13]=ce; U.uc[14]=cf;
    U.uc[15]=cg;
  }

  template <typename T>
  void fill(Unique128Bit& U, const T* d) {
    _copy(_TYPE(double,&U),_TYPE(double,const_cast<T*>(d)),uTwo);
  }

}

#endif

#include "array/1d/content/fill.h"

namespace mysimulator {

  void _fill(Unique128Bit* p, const Unique128Bit& U, const unsigned int& n,
             const  unsigned int& del) {
    _fill(_TYPE(double,p),U.d[0],n,del*2);
    _fill(_TYPE(double,p)+1,U.d[1],n,del*2);
  }
  void _fill(Unique128Bit* p, const Unique128Bit& U, const unsigned int& n) {
    _fill(_TYPE(double,p),U.d[0],n,2);
    _fill(_TYPE(double,p)+1,U.d[1],n,2);
  }

  void _fill(Unique128Bit* p, const long double& ld, const unsigned int& n,
             const unsigned int& del) {
    _fill(_TYPE(float,p),*_TYPE(const float,&ld),n,del*4);
    _fill(_TYPE(float,p)+1,*(_TYPE(const float,&ld)+1),n,del*4);
    _fill(_TYPE(float,p)+2,*(_TYPE(const float,&ld)+2),n,del*4);
  }
  void _fill(Unique128Bit* p, const long double& ld, const unsigned int& n) {
    _fill(_TYPE(float,p),*_TYPE(const float,&ld),n,4);
    _fill(_TYPE(float,p)+1,*(_TYPE(const float,&ld)+1),n,4);
    _fill(_TYPE(float,p)+2,*(_TYPE(const float,&ld)+2),n,4);
  }

}

#define _FILLV_WithDel(type) \
  void _fill(Unique128Bit* p, const type& d, const unsigned int& n,\
             const unsigned int& del) {\
    static const unsigned int m=sizeof(double)*2/sizeof(type);\
    for(unsigned int i=0;i<m;++i) _fill(_TYPE(type,p)+i,d,n,del*m);\
  }

#define _FILLV(type) \
  void _fill(Unique128Bit* p, const type& d, const unsigned int& n) {\
    static const unsigned int m=sizeof(double)*2/sizeof(type);\
    _fill(_TYPE(type,p),d,n*m);\
  }

#define _FILL(type) \
  _FILLV_WithDel(type)\
  _FILLV(type)

namespace mysimulator {

  _FILL(double)
  _FILL(float)
  _FILL(long long)
  _FILL(unsigned long long)
  _FILL(int)
  _FILL(unsigned int)
  _FILL(long)
  _FILL(unsigned long)
  _FILL(short)
  _FILL(unsigned short)
  _FILL(char)
  _FILL(unsigned char)

}

#undef _FILL
#undef _FILLV
#undef _FILLV_WithDel

#undef _TYPE

#endif

