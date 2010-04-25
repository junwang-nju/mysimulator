
#ifndef _Unique_Parameter_H_
#define _Unique_Parameter_H_

#include "error-proc.h"
#include <cstdlib>
#include <cctype>

namespace std {

  union UniqueParameter {

    double d;
    unsigned int u;
    int i;
    unsigned long long int ull;
    void *ptr;

    typedef UniqueParameter Type;

    UniqueParameter() : ull(0) {}
    UniqueParameter(const Type&) {
      myError("Cannot create from Unique Parameter");
    }
    Type& operator=(const Type& UP) { ull=UP.ull; return *this; }
    Type& operator=(const double dv) { d=dv; return *this; }
    template <typename T>
    Type& operator=(const T* tptr) { ptr=const_cast<T*>(tptr); return *this; }
    Type& operator=(const unsigned int uv) { u=uv; return *this; }
    Type& operator=(const int iv) { i=iv; return *this; } 

    double& operator()() { return d; }
    const double& operator()() const { return d; }

  };

  istream& operator>>(istream& is, UniqueParameter& UP) {
    static char flag;
    is>>flag;
    if((flag=='D')||(flag=='d'))  is>>UP.d;
    else if((flag=='U')||(flag=='u')) is>>UP.u;
    else if((flag=='I')||(flag=='i')) is>>UP.i;
    else if((flag=='P')||(flag=='p')) is>>UP.ptr;
    else if(isdigit(flag)||(flag=='+')) {
      is.unget();
      is>>UP.ull;
    }
    else is.setstate(ios_base::failbit);
    return is;
  }

  ostream& operator<<(ostream& os, const UniqueParameter& UP) {
    os<<UP.ull;
    return os;
  }

}

#endif

