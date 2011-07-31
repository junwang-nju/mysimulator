
#ifndef _Intrinsic_Type_Release_H_
#define _Intrinsic_Type_Release_H_

#include <cstdlib>

#define _RELEASE(type) void release(type&) {}

namespace mysimulator {

  _RELEASE(long double)
  _RELEASE(double)
  _RELEASE(float)
  _RELEASE(long long)
  _RELEASE(unsigned long long)
  _RELEASE(int)
  _RELEASE(unsigned int)
  _RELEASE(long)
  _RELEASE(unsigned long)
  _RELEASE(short)
  _RELEASE(unsigned short)
  _RELEASE(char)
  _RELEASE(unsigned char)

  template <typename T>
  void delete_pointer(T*& p) { if(p!=NULL) delete p; p=NULL; }

  template <typename T>
  void delete_array(T*& p) { if(p!=NULL) delete[] p; p=NULL; }

}

#endif

