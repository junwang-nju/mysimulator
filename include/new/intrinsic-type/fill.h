
#ifndef _Intrinsic_Type_Fill_H_
#define _Intrinsic_Type_Fill_H_

#include "intrinsic-type/copy.h"

#define _FILL(type1,type2) \
  void fill(type1& a, const type2& b) { copy(a,b); }

namespace mysimulator {

  _FILL(long double,long double)
  _FILL(long double,double)
  _FILL(long double,float)
  _FILL(long double,long long)
  _FILL(long double,unsigned long long)
  _FILL(long double,int)
  _FILL(long double,unsigned int)
  _FILL(long double,long)
  _FILL(long double,unsigned long)
  _FILL(long double,short)
  _FILL(long double,unsigned short)
  _FILL(long double,char)
  _FILL(long double,unsigned char)

  _FILL(double,double)
  _FILL(double,float)
  _FILL(double,long long)
  _FILL(double,unsigned long long)
  _FILL(double,int)
  _FILL(double,unsigned int)
  _FILL(double,long)
  _FILL(double,unsigned long)
  _FILL(double,short)
  _FILL(double,unsigned short)
  _FILL(double,char)
  _FILL(double,unsigned char)

  _FILL(float,float)
  _FILL(float,long long)
  _FILL(float,unsigned long long)
  _FILL(float,int)
  _FILL(float,unsigned int)
  _FILL(float,long)
  _FILL(float,unsigned long)
  _FILL(float,short)
  _FILL(float,unsigned short)
  _FILL(float,char)
  _FILL(float,unsigned char)

  _FILL(long long,long long)
  _FILL(long long,int)
  _FILL(long long,unsigned int)
  _FILL(long long,long)
  _FILL(long long,unsigned long)
  _FILL(long long,short)
  _FILL(long long,unsigned short)
  _FILL(long long,char)
  _FILL(long long,unsigned char)

  _FILL(unsigned long long,unsigned long long)
  _FILL(unsigned long long,unsigned int)
  _FILL(unsigned long long,unsigned long)
  _FILL(unsigned long long,unsigned short)
  _FILL(unsigned long long,unsigned char)

  _FILL(int,int)
  _FILL(int,long)
  _FILL(int,short)
  _FILL(int,unsigned short)
  _FILL(int,char)
  _FILL(int,unsigned char)

  _FILL(unsigned int,unsigned int)
  _FILL(unsigned int,unsigned long)
  _FILL(unsigned int,unsigned short)
  _FILL(unsigned int,unsigned char)

  _FILL(long,int)
  _FILL(long,long)
  _FILL(long,short)
  _FILL(long,unsigned short)
  _FILL(long,char)
  _FILL(long,unsigned char)

  _FILL(unsigned long,unsigned int)
  _FILL(unsigned long,unsigned long)
  _FILL(unsigned long,unsigned short)
  _FILL(unsigned long,unsigned char)

  _FILL(short,short)
  _FILL(short,char)
  _FILL(short,unsigned char)

  _FILL(unsigned short,unsigned short)
  _FILL(unsigned short,unsigned char)

  _FILL(char,char)

  _FILL(unsigned char,unsigned char)

  _FILL(void*,void*)
  template <typename T> _FILL(void*,T*)
  template <typename T> _FILL(T*,void*)
  template <typename T> _FILL(T*,T*)

  _FILL(bool,bool)
  _FILL(bool,long long)
  _FILL(bool,unsigned long long)
  _FILL(bool,int)
  _FILL(bool,unsigned int)
  _FILL(bool,long)
  _FILL(bool,unsigned long)
  _FILL(bool,short)
  _FILL(bool,unsigned short)
  _FILL(bool,char)
  _FILL(bool,unsigned char)

}

#undef _FILL

#endif

