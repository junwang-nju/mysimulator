
#ifndef _Utility_H_
#define _Utility_H_

#include <cstdlib>

namespace std {
  void Nullify(int& I);
  void Nullify(unsigned int& I);
  void Nullify(double& D);
  int compare(const int I, const int J);
  int compare(const double DI, const double DJ);
  void toupper(char* dest, const char* src, const unsigned int n);
  void tolower(char* dest, const char* src, const unsigned int n);
  template <typename T>
  void swap(T*& a, T*& b) { T* t; t=a; a=b; b=t; t=NULL; }
  void swap(unsigned int& a, unsigned int& b);
}

#endif

