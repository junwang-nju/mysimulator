
#ifndef _Utility_H_
#define _Utility_H_

#include <cstdlib>
#include <cctype>

namespace std {
  void Nullify(int& I) { I=0; }
  void Nullify(unsigned int& I) { I=0U; }
  void Nullify(double& D) { D=0.; }
  int compare(const int I, const int J) { return (I<J?-1:(I>J?1:0)); }
  int compare(const double DI, const double DJ){ return DI<DJ?-1:(DI>DJ?1:0); }
  void toupper(char* dest, const char* src, const unsigned int n) {
    for(unsigned int i=0;i<n;++i) dest[i]=toupper(src[i]);
  }
  void tolower(char* dest, const char* src, const unsigned int n) {
    for(unsigned int i=0;i<n;++i) dest[i]=tolower(src[i]);
  }
  template <typename T>
  void swap(T*& a, T*& b) { T* t; t=a; a=b; b=t; t=NULL; }
  void swap(unsigned int& a, unsigned int& b) { unsigned int t=a; a=b; b=t; }
  template <typename T>
  bool IsAvailable(const T* ptr) { return ptr!=NULL; }
  template <typename T>
  bool IsGeometry(const T&) { return false; }

}

#endif

