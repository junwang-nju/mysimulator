
#ifndef _Utility_H_
#define _Utility_H_

#include <cstdlib>
#include <cctype>

namespace std {
  inline void Nullify(int& I) { I=0; }
  inline void Nullify(unsigned int& I) { I=0U; }
  inline void Nullify(double& D) { D=0.; }
  inline int compare(const int I, const int J) { return (I<J?-1:(I>J?1:0)); }
  inline int compare(const double DI, const double DJ){
    return DI<DJ?-1:(DI>DJ?1:0);
  }
  inline void toupper(char* dest, const char* src, const unsigned int n) {
    for(unsigned int i=0;i<n;++i) dest[i]=static_cast<char>(toupper(src[i]));
  }
  inline void tolower(char* dest, const char* src, const unsigned int n) {
    for(unsigned int i=0;i<n;++i) dest[i]=static_cast<char>(tolower(src[i]));
  }
  template <typename T>
  inline void swap(T*& a, T*& b) { T* t; t=a; a=b; b=t; t=NULL; }
  inline void swap(unsigned int& a, unsigned int& b) {
    unsigned int t=a; a=b; b=t;
  }
  void swap(double& a, double& b) { double t=a; a=b; b=t; }
  void swap(int& a, int& b) { int t=a; a=b; b=t; }

  template <typename T>
  inline bool IsAvailable(const T* ptr) { return ptr!=NULL; }
  template <typename T>
  inline bool IsGeometry(const T&) { return false; }
  template <typename T>
  inline bool IsRandomGenerator(const T&) { return false; }

  void assign(double dest, const double src) { dest=src; }
  void assign(unsigned int dest, const unsigned int src) { dest=src; }
  void assign(int dest, const int src) { dest=src; }

  void shift(double& dest, const double fac, const double src) {
    dest+=fac*src;
  }
  void shift(unsigned int& dest, const unsigned int fac,
             const unsigned int src) {
    dest+=fac*src;
  }
  void shift(int& dest, const int fac, const int src) { dest+=fac*src; }
  double dot(const double a, const double b) { return a*b; }
  unsigned int dot(const unsigned int a, const unsigned int b) { return a*b; }
  int dot(const int a, const int b) { return a*b; }

  void updateParameter(double&) {}
  void updateParameter(unsigned int&) {}
  void updateParameter(int&) {}

}

#endif

