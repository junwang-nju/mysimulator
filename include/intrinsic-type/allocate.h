
#ifndef _Intrinsic_Type_Allocate_H_
#define _Intrinsic_Type_Allocate_H_

namespace mysimulator {

  void allocate(long double&) {}
  void allocate(double&) {}
  void allocate(float&) {}
  void allocate(long long int&) {}
  void allocate(unsigned long long int&) {}
  void allocate(int&) {}
  void allocate(unsigned int&) {}
  void allocate(long&) {}
  void allocate(unsigned long&) {}
  void allocate(short&) {}
  void allocate(unsigned short&) {}
  void allocate(char&) {}
  void allocate(unsigned char&) {}
  void allocate(bool&) {}

  void imprint(long double&,const long double&) {}
  void imprint(double&,const double&) {}
  void imprint(float&,const float&) {}
  void imprint(long long int&,const long long int&) {}
  void imprint(int&,const int&) {}
  void imprint(unsigned int&,const unsigned int&) {}
  void imprint(unsigned long&,const unsigned long&) {}
  void imprint(short&, const short&) {}
  void imprint(unsigned short&,const unsigned short&) {}
  void imprint(char&,const char&) {}
  void imprint(unsigned char&,const unsigned char&) {}
  void imprint(bool&,const bool&) {}

}

#endif

