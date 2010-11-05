
#ifndef _Unique_Parameter_H_
#define _Unique_Parameter_H_

#include "error-proc.h"
#include <cstdlib>
#include <cctype>

namespace std {

  union UniqueParameter {
    double d;
    float f;
    unsigned int u;
    int i;
    unsigned long long int ull;
    void *ptr;
    
    typedef UniqueParameter Type;
    UniqueParameter() : ull(0) {}
    UniqueParameter(const Type& P) {
      myError("Cannot create Unique Parameter");
    }
    Type& operator=(const Type& P) {
      myError("Cannot copy Unique Parameter");
      return *this;
    }
  };

  void copy(UniqueParameter& P, const double& d) { P.d=d; }
  void copy(UniqueParameter& P, const float& f) { P.f=f; }
  void copy(UniqueParameter& P, const unsigned int& u) { P.u=u; }
  void copy(UniqueParameter& P, const int& i) { P.i=i; }
  void copy(UniqueParameter& P, const unsigned long long int& l) { P.ull=l; }
  template <typename T>
  void copy(UniqueParameter& P, const T* ptr) {
    P.ptr=reinterpret_cast<void*>(const_cast<T*>(ptr));
  }
  void copy(double& d, const UniqueParameter& P) { d=P.d; }
  void copy(float& f, const UniqueParameter& P) { f=P.f; }
  void copy(int& i, const UniqueParameter& P) { i=P.i; }
  void copy(unsigned int& u, const UniqueParameter& P) { u=P.u; }
  void copy(unsigned long long int& l, const UniqueParameter& P) { l=P.ull; }
  template <typename T>
  void copy(T*& ptr, const UniqueParameter& P) {
    ptr=reinterpret_cast<T*>(const_cast<void*>(P.ptr));
  }

  istream& operator>>(istream& is, UniqueParameter& P) {
    static char flag;
    is>>flag;
    if((flag=='D')||(flag=='d'))  is>>P.d;
    else if((flag='F')||(flag=='f'))  is>>P.f;
    else if((flag='U')||(flag=='u'))  is>>P.u;
    else if((flag='I')||(flag=='i'))  is>>P.i;
    else if((flag='P')||(flag=='P'))  is>>P.ptr;
    else if(isdigit(flag)||(flag=='+')) { is.unget(); is>>P.ull; }
    else is.setstate(ios_base::failbit);
    return is;
  }

  ostream* operator<<(ostream& os, const UniqueParameter& P) {
    os<<P.ull;
    return os;
  }

}

#endif
