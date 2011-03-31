
#ifndef _Intrinsic_Type_Release_H_
#define _Intrinsic_Type_Release_H_

#include <cstdlib>

namespace mysimulator {

  void release(long double&) {}
  void release(double&) {}
  void release(float&) {}
  void release(long long int&) {}
  void release(unsigned long long int&) {}
  void release(int&) {}
  void release(unsigned int&) {}
  void release(long&) {}
  void release(unsigned long&) {}
  void release(short&) {}
  void release(unsigned short&) {}
  void release(char&) {}
  void release(unsigned char&) {}
  template <typename T>
  void release(T*& ptr) {
    if(ptr==NULL) return;
    delete[] ptr;
    ptr=NULL;
  }

}

#endif
