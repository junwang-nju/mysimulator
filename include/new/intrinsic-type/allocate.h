
#ifndef _Intrinsic_Type_Allocate_H_
#define _Intrinsic_Type_Allocate_H_

#define _ALLOC(type) void allocate(type&) {}
#define _IMPRINT(type) void imprint(type&,const type&) {}

namespace mysimulator {

  _ALLOC(long double)
  _ALLOC(double)
  _ALLOC(float)
  _ALLOC(long long)
  _ALLOC(unsigned long long)
  _ALLOC(int)
  _ALLOC(unsigned int)
  _ALLOC(long)
  _ALLOC(unsigned long)
  _ALLOC(short)
  _ALLOC(unsigned short)
  _ALLOC(char)
  _ALLOC(unsigned char)
  _ALLOC(bool)

  template <typename T>
  void allocate(T* &p) { p=new T; }

  template <typename T>
  void allocate(T* &p, const unsigned int& n) { p=new T[n]; }

  _IMPRINT(long double)
  _IMPRINT(double)
  _IMPRINT(float)
  _IMPRINT(long long)
  _IMPRINT(unsigned long long)
  _IMPRINT(int)
  _IMPRINT(unsigned int)
  _IMPRINT(long)
  _IMPRINT(unsigned long)
  _IMPRINT(short)
  _IMPRINT(unsigned short)
  _IMPRINT(char)
  _IMPRINT(unsigned char)
  _IMPRINT(bool)

}

#endif

