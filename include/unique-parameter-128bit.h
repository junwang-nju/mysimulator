
#ifndef _Unique_Parameter_128bit_H_
#define _Unique_Parameter_128bit_H_

#include "error-proc.h"
#include "vector-impl.h"

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

  union UniqueParameter128b {

#ifdef HAVE_SSE2
    __m128i si;
    __m128d sd;
#endif
    long double ld;
    double d[2];
    unsigned int u[4];
    int i[4];
    unsigned long long int ull[2];
    void* ptr[4];

    typedef UniqueParameter128b   Type;
    UniqueParameter128b() { ull[0]=0; ull[1]=0; }
    UniqueParameter128b(const Type&) {
      myError("Cannot create from 128bit Unique Parameter");
    }
    Type& operator=(const Type& UP) { return operator=(UP.ull); }
    Type& operator=(const long double rld) { ld=rld; return *this; }
    Type& operator=(const double rd[2]) { assign(d,rd,2); return *this; }
    Type& operator=(const unsigned int ru[4]) { assign(u,ru,4); return *this; }
    Type& operator=(const int ri[8]) { assign(i,ri,4); return *this; }
    Type& operator=(const unsigned long long rull[2]) {
      assign(ull,rull,2);
      return *this;
    }
    template <typename T>
    Type& operator=(T* const rptr[4]) {
      assign(reinterpret_cast<unsigned int*>(ptr),
             reinterpret_cast<const unsigned int*>(rptr),4);
      return *this;
    }

    long double& operator()() { return ld; }
    const long double& operator()() const { return ld; }

  };

  istream& operator>>(istream& is, UniqueParameter128b& UP) {
    static char flag;
    static char buff[1024];
    is>>flag;
    if((flag=='G')||(flag=='g'))  is>>UP.ld;
    else if((flag=='D')||(flag=='d')) {
      is>>buff; is>>UP.d[0]; is>>UP.d[1]; is>>buff;
    } else if((flag=='U')||(flag=='u')) {
      is>>buff; for(unsigned int i=0;i<4;++i) is>>UP.u[i];  is>>buff;
    } else if((flag=='I')||(flag=='i')) {
      is>>buff; for(unsigned int i=0;i<4;++i) is>>UP.i[i];  is>>buff;
    } else if((flag=='L')||(flag=='l')) {
      is>>buff; is>>UP.ull[0];  is>>UP.ull[1];  is>>buff;
    } else if((flag=='P')||(flag=='p')) {
      is>>buff; for(unsigned int i=0;i<4;++i) is>>UP.ptr[i];  is>>buff;
    } else is.setstate(ios_base::failbit);
    return is;
  }

  ostream& operator<<(ostream& os, const UniqueParameter128b& UP) {
    os<<"L [ "<<UP.ull[0]<<"  "<<UP.ull[1]<<" ] ";
    return os;
  }

}

#endif

