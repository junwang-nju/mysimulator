
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
  template <typename T>
  inline bool IsAvailable(const T* ptr) { return ptr!=NULL; }
  template <typename T>
  inline bool IsGeometry(const T&) { return false; }
  template <typename T>
  inline bool IsRandomGenerator(const T&) { return false; }

}

#endif

