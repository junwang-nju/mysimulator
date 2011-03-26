
#ifndef _Intrinsic_Type_Validity_Check_H_
#define _Intrinsic_Type_Validity_Check_H_

#include <cstdlib>

namespace mysimulator {

  bool IsValid(const long double&) { return true; }
  bool IsValid(const double&) { return true; }
  bool IsValid(const float&) { return true; }
  bool IsValid(const long long int&) { return true; }
  bool IsValid(const unsigned long long int&) { return true; }
  bool IsValid(const int&) { return true; }
  bool IsValid(const unsigned int&) { return true; }
  bool IsValid(const long&) { return true; }
  bool IsValid(const unsigned long&) { return true; }
  bool IsValid(const short&) { return true; }
  bool IsValid(const unsigned short&) { return true; }
  bool IsValid(const char&) { return true; }
  bool IsValid(const unsigned char&) { return true; }
  bool IsValid(const void* ptr) { return ptr!=NULL; }
}

#endif

