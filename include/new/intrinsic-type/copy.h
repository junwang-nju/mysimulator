
#ifndef _Intrinsic_Type_COPY_H_
#define _Intrinsic_Type_COPY_H_

#define _COPY(type1,type2) \
  void copy(type1& a, const type2& b) { a=const_cast<type2&>(b); }
#define _COPYBOOL(type) \
  void copy(bool& a, const type& b) { a=(b==0?false:true); }

namespace mysimulator {

  _COPY(long double,long double)
  _COPY(long double,double)
  _COPY(long double,float)
  _COPY(long double,long long)
  _COPY(long double,unsigned long long)
  _COPY(long double,int)
  _COPY(long double,unsigned int)
  _COPY(long double,long)
  _COPY(long double,unsigned long)
  _COPY(long double,short)
  _COPY(long double,unsigned short)
  _COPY(long double,char)
  _COPY(long double,unsigned char)

  _COPY(double,double)
  _COPY(double,float)
  _COPY(double,long long)
  _COPY(double,unsigned long long)
  _COPY(double,int)
  _COPY(double,unsigned int)
  _COPY(double,long)
  _COPY(double,unsigned long)
  _COPY(double,short)
  _COPY(double,unsigned short)
  _COPY(double,char)
  _COPY(double,unsigned char)

  _COPY(float,float)
  _COPY(float,long long)
  _COPY(float,unsigned long long)
  _COPY(float,int)
  _COPY(float,unsigned int)
  _COPY(float,long)
  _COPY(float,unsigned long)
  _COPY(float,short)
  _COPY(float,unsigned short)
  _COPY(float,char)
  _COPY(float,unsigned char)

  _COPY(long long,long long)
  _COPY(long long,int)
  _COPY(long long,unsigned int)
  _COPY(long long,long)
  _COPY(long long,unsigned long)
  _COPY(long long,short)
  _COPY(long long,unsigned short)
  _COPY(long long,char)
  _COPY(long long,unsigned char)

  _COPY(unsigned long long,unsigned long long)
  _COPY(unsigned long long,unsigned int)
  _COPY(unsigned long long,unsigned long)
  _COPY(unsigned long long,unsigned short)
  _COPY(unsigned long long,unsigned char)

  _COPY(int,int)
  _COPY(int,long)
  _COPY(int,short)
  _COPY(int,unsigned short)
  _COPY(int,char)
  _COPY(int,unsigned char)

  _COPY(unsigned int,unsigned int)
  _COPY(unsigned int,unsigned long)
  _COPY(unsigned int,unsigned short)
  _COPY(unsigned int,unsigned char)

  _COPY(long,int)
  _COPY(long,long)
  _COPY(long,short)
  _COPY(long,unsigned short)
  _COPY(long,char)
  _COPY(long,unsigned char)

  _COPY(unsigned long,unsigned int)
  _COPY(unsigned long,unsigned long)
  _COPY(unsigned long,unsigned short)
  _COPY(unsigned long,unsigned char)

  _COPY(short,short)
  _COPY(short,char)
  _COPY(short,unsigned char)

  _COPY(unsigned short,unsigned short)
  _COPY(unsigned short,unsigned char)

  _COPY(char,char)

  _COPY(unsigned char,unsigned char)

  _COPY(void*,void*)
  template <typename T> _COPY(void*,T* const)
  template <typename T> _COPY(T*,void* const)
  template <typename T> _COPY(T*,T* const)

  _COPY(bool,bool)
  _COPYBOOL(long long)
  _COPYBOOL(unsigned long long)
  _COPYBOOL(int)
  _COPYBOOL(unsigned int)
  _COPYBOOL(long)
  _COPYBOOL(unsigned long)
  _COPYBOOL(short)
  _COPYBOOL(unsigned short)
  _COPYBOOL(char)
  _COPYBOOL(unsigned char)

}

#undef _COPYBOOL
#undef _COPY

#endif

