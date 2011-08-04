
#ifndef _Unique_64Bit_Fill_H_
#define _Unique_64Bit_Fill_H_

#include "unique/64bit/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  void fill(Unique64Bit& U, const double& d) { copy(U.d,d); }

  void fill(Unique64Bit& U, const float& f) { copy(U.f[0],f); copy(U.f[1],f); }

  void fill(Unique64Bit& U, const float& f1, const float& f2) {
    copy(U.f[0],f1);  copy(U.f[1],f2);
  }

  void fill(Unique64Bit& U, const unsigned long long& l) { copy(U.ull,l); }

  void fill(Unique64Bit& U, const long long& l) { copy(U.ll,l); }

  void fill(Unique64Bit& U, const int& i) { copy(U.i[0],i); copy(U.i[1],i); }

  void fill(Unique64Bit& U, const int& i1, const int& i2) {
    copy(U.i[0],i1);  copy(U.i[1],i2);
  }

  void fill(Unique64Bit& U, const unsigned int& u) {
    copy(U.u[0],u); copy(U.u[1],u);
  }

  void fill(Unique64Bit& U, const unsigned int& u1, const unsigned int& u2) {
    copy(U.u[0],u1); copy(U.u[1],u2);
  }

  void fill(Unique64Bit& U, const long& l) { copy(U.l[0],l); copy(U.l[1],l); }

  void fill(Unique64Bit& U, const unsigned long& ul) {
    copy(U.u[0],ul);  copy(U.u[1],ul);
  }

  void fill(Unique64Bit& U, const short& s) {
    copy(U.s[0],s);   copy(U.s[1],s);   copy(U.s[2],s);   copy(U.s[3],s);
  }

  void fill(Unique64Bit& U, const short& s1, const short& s2, const short& s3,
            const short& s4) {
    copy(U.s[0],s1);  copy(U.s[1],s2);  copy(U.s[2],s3);  copy(U.s[3],s4);
  }

  void fill(Unique64Bit& U, const unsigned short& us) {
    copy(U.us[0],us); copy(U.us[1],us);   copy(U.us[2],us);   copy(U.us[3],us);
  }

  void fill(Unique64Bit& U,
            const unsigned short& us1, const unsigned short& us2,
            const unsigned short& us3, const unsigned short& us4) {
    copy(U.us[0],us1); copy(U.us[1],us2); copy(U.us[2],us3); copy(U.us[3],us4);
  }

  void fill(Unique64Bit& U, const char& c) {
    char* p=U.c;
    char* e=p+8;
    for(;p!=e;) *(p++)=c;
  }

  void fill(Unique64Bit& U, const char& c1, const char& c2, const char& c3,
            const char& c4, const char& c5, const char& c6, const char& c7,
            const char& c8) {
    copy(U.c[0],c1); copy(U.c[1],c2); copy(U.c[2],c3); copy(U.c[3],c4);
    copy(U.c[4],c5); copy(U.c[5],c6); copy(U.c[6],c7); copy(U.c[7],c8);
  }

  void fill(Unique64Bit& U, const unsigned char& uc) {
    unsigned char* p=U.uc;
    unsigned char* e=p+8;
    for(;p!=e;) *(p++)=uc;
  }

  void fill(Unique64Bit& U, const unsigned char& c1, const unsigned char& c2,
            const unsigned char& c3, const unsigned char& c4,
            const unsigned char& c5, const unsigned char& c6,
            const unsigned char& c7, const unsigned char& c8) {
    copy(U.uc[0],c1); copy(U.uc[1],c2); copy(U.uc[2],c3); copy(U.uc[3],c4);
    copy(U.uc[4],c5); copy(U.uc[5],c6); copy(U.uc[6],c7); copy(U.uc[7],c8);
  }

}

#include "array/1d/content/fill.h"

#define _TYPE(type,a) reinterpret_cast<type*>(a)

#define _FILLU_WithDel(type) \
  void _fill(Unique64Bit* p, const type& d, const unsigned int& n,\
             const unsigned int& del) {\
    unsigned int m=sizeof(double)/sizeof(type);\
    for(unsigned int i=0;i<m;++i)\
      _fill(_TYPE(type,p)+i,d,n,del*sizeof(double)/sizeof(type));\
  }

#define _FILLU(type) \
  void _fill(Unique64Bit* p, const type& d, const unsigned int& n) {\
    _fill(_TYPE(type,p),d,n*sizeof(double)/sizeof(type));\
  }

#define _FILL(type) \
  _FILLU_WithDel(type)\
  _FILLU(type)

namespace mysimulator {

  void _fill(Unique64Bit* p, const Unique64Bit& d, const unsigned int& n,
             const unsigned int& del) { _fill_blas(_TYPE(double,p),d.d,n,del); }

  void _fill(Unique64Bit* p, const Unique64Bit& d, const unsigned int& n) {
    _fill_blas(_TYPE(double,p),d.d,n);
  }

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
#undef _FILLU
#undef _FILLU_WithDel
#undef _TYPE

#endif

