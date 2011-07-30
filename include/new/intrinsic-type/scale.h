
#ifndef _Intrinsic_Type_Scale_H_
#define _Intrinsic_Type_Scale_H_

#define _SCALE(type1,type2) void scale(type1& a, const type2& b) { a*=b; }

namespace mysimulator {

  _SCALE(long double,long double)
  _SCALE(long double,double)
  _SCALE(long double,float)
  _SCALE(long double,long long)
  _SCALE(long double,unsigned long long)
  _SCALE(long double,int)
  _SCALE(long double,unsigned int)
  _SCALE(long double,long)
  _SCALE(long double,unsigned long)
  _SCALE(long double,short)
  _SCALE(long double,unsigned short)
  _SCALE(long double,char)
  _SCALE(long double,unsigned char)

  _SCALE(double,double)
  _SCALE(double,float)
  _SCALE(double,long long)
  _SCALE(double,unsigned long long)
  _SCALE(double,int)
  _SCALE(double,unsigned int)
  _SCALE(double,long)
  _SCALE(double,unsigned long)
  _SCALE(double,short)
  _SCALE(double,unsigned short)
  _SCALE(double,char)
  _SCALE(double,unsigned char)

  _SCALE(float,float)
  _SCALE(float,long long)
  _SCALE(float,unsigned long long)
  _SCALE(float,int)
  _SCALE(float,unsigned int)
  _SCALE(float,long)
  _SCALE(float,unsigned long)
  _SCALE(float,short)
  _SCALE(float,unsigned short)
  _SCALE(float,char)
  _SCALE(float,unsigned char)

  _SCALE(long long,long long)
  _SCALE(long long,int)
  _SCALE(long long,unsigned int)
  _SCALE(long long,long)
  _SCALE(long long,unsigned long)
  _SCALE(long long,short)
  _SCALE(long long,unsigned short)
  _SCALE(long long,char)
  _SCALE(long long,unsigned char)

  _SCALE(unsigned long long,unsigned long long)
  _SCALE(unsigned long long,unsigned int)
  _SCALE(unsigned long long,unsigned long)
  _SCALE(unsigned long long,unsigned short)
  _SCALE(unsigned long long,unsigned char)

  _SCALE(int,int)
  _SCALE(int,long)
  _SCALE(int,short)
  _SCALE(int,unsigned short)
  _SCALE(int,char)
  _SCALE(int,unsigned char)

  _SCALE(unsigned int,unsigned int)
  _SCALE(unsigned int,unsigned long)
  _SCALE(unsigned int,unsigned short)
  _SCALE(unsigned int,unsigned char)

  _SCALE(long,int)
  _SCALE(long,long)
  _SCALE(long,short)
  _SCALE(long,unsigned short)
  _SCALE(long,char)
  _SCALE(long,unsigned char)

  _SCALE(unsigned long,unsigned int)
  _SCALE(unsigned long,unsigned long)
  _SCALE(unsigned long,unsigned short)
  _SCALE(unsigned long,unsigned char)

  _SCALE(short,short)
  _SCALE(short,char)
  _SCALE(short,unsigned char)

  _SCALE(unsigned short,unsigned short)
  _SCALE(unsigned short,unsigned char)

  _SCALE(char,char)

  _SCALE(unsigned char,unsigned char)

}

#undef _SCALE

#endif

