
#ifndef _IntrinsicType_IO_H_
#define _IntrinsicType_IO_H_

#ifndef _WRITE
#define _WRITE(Type,TStr) \
  void Write(const Type & var) { printf(TStr,var); }
#else
#error "Duplicate Definition for Macro _WRITE"
#endif

namespace mysimulator {

  _WRITE(long double,"%Lg")
  _WRITE(double,"%lg")
  _WRITE(float,"%f")
  _WRITE(long long,"%lld")
  _WRITE(unsigned long long,"%llu")
  _WRITE(int,"%d")
  _WRITE(unsigned int,"%u")
  _WRITE(long,"%ld")
  _WRITE(unsigned long,"%lu")
  _WRITE(short,"%hd")
  _WRITE(unsigned short,"%hu")
  _WRITE(char,"%c")
  _WRITE(unsigned char,"%c")
  _WRITE(bool,"%d")
  _WRITE(char* const,"%s")
  _WRITE(void* const,"%p")

}

#ifdef _WRITE
#undef _WRITE
#endif

namespace mysimulator {

  template <typename T1,typename T2>
  void Write(const T1& A,const T2& B) { Write(A); Write(B); }

  template <typename T1,typename T2,typename T3>
  void Write(const T1& A,const T2& B,const T3& C) {
    Write(A); Write(B); Write(C);
  }

  template <typename T1,typename T2,typename T3,typename T4>
  void Write(const T1& A,const T2& B,const T3& C,const T4& D) {
    Write(A); Write(B); Write(C); Write(D);
  }

  template <typename T1,typename T2,typename T3,typename T4,typename T5>
  void Write(const T1& A,const T2& B,const T3& C,const T4& D,const T5& E) {
    Write(A); Write(B); Write(C); Write(D); Write(E);
  }

}

#endif

