
#ifndef _Unique_Parameter_128bit_H_
#define _Unique_Parameter_128bit_H_

#ifdef _Have_SSE2
#include <emmintrin.h>
#endif

#include "io/error.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  union UniqueParameter128Bit {

    typedef UniqueParameter128Bit   Type;

#ifdef _Have_SSE2
    __m128i   si;
    __m128d   sd;
#endif
    long double ld;
    double d[2];
    float f[4];
    unsigned long long ull[2];
    int i[4];
    unsigned int u[4];
    short s[8];
    char c[16];
    void *ptr[4];
    double dvalue;
    float fvalue;
    unsigned long long ullvalue;
    int ivalue;
    unsigned int uvalue;
    short svalue;
    char cvalue;
    void* pvalue;

    UniqueParameter128Bit() { ull[0]=ull[1]=0; }
    UniqueParameter128Bit(const Type&) {
      Error("Copier of UniqueParameter128Bit Disabled!");
    }
    Type& operator=(const Type& P) {
      Error("Operator= for UniqueParameter128Bit Disabled!");
      return *this;
    }
    ~UniqueParameter128Bit() { clearData(); }

    void clearData() {}
    template <typename T>
    T& value() {
      Error("Not-Included Type in UniqueParameter128Bit!");
      static T tvalue=static_cast<T>(0);
      return tvalue;
    }
    template <typename T>
    const T& value() const {
      Error("Not-Included Type in UniqueParameter128Bit!");
      static T tvalue=static_cast<T>(0);
      return tvalue;
    }
    template <typename T>
    T*& pointer() { return reinterpret_cast<T*&>(ptr); }
    template <typename T>
    T* const& pointer() const { return reinterpret_cast<T* const&>(ptr); }

  };

  template <>
  long double& UniqueParameter128Bit::value<long double>() { return ld; }
  template <>
  const long double& UniqueParameter128Bit::value<long double>() const {
    return ld;
  }

  template <>
  double& UniqueParameter128Bit::value<double>() { return dvalue; }
  template <>
  const double& UniqueParameter128Bit::value<double>() const { return dvalue; }

  template <>
  float& UniqueParameter128Bit::value<float>() { return fvalue; }
  template <>
  const float& UniqueParameter128Bit::value<float>() const { return fvalue; }

  template <>
  unsigned long long& UniqueParameter128Bit::value<unsigned long long>() {
    return ullvalue;
  }
  template <>
  const unsigned long long&
  UniqueParameter128Bit::value<unsigned long long>() const { return ullvalue; }

  template <>
  int& UniqueParameter128Bit::value<int>() { return ivalue; }
  template <>
  const int& UniqueParameter128Bit::value<int>() const { return ivalue; }

  template <>
  unsigned int& UniqueParameter128Bit::value<unsigned int>() { return uvalue; }
  template <>
  const unsigned int& UniqueParameter128Bit::value<unsigned int>() const {
    return uvalue;
  }

  template <>
  short& UniqueParameter128Bit::value<short>() { return svalue; }
  template <>
  const short& UniqueParameter128Bit::value<short>() const { return svalue; }

  template <>
  char& UniqueParameter128Bit::value<char>() { return cvalue; }
  template <>
  const char& UniqueParameter128Bit::value<char>() const { return cvalue; }

  template <>
  void*& UniqueParameter128Bit::value<void*>() { return pvalue; }
  template <>
  void* const& UniqueParameter128Bit::value<void*>() const { return pvalue; }

  bool IsValid(const UniqueParameter128Bit&) { return true; }
  void release(UniqueParameter128Bit& P) { return P.clearData(); }

  void copy(UniqueParameter128Bit& P, const UniqueParameter128Bit& cP) {
    P.ull[0]=cP.ull[0];   P.ull[1]=cP.ull[1];
  }

  template <typename T>
  void copy(UniqueParameter128Bit& P, const T& value) {
    copy(P.value<T>(),value);
  }
  template <typename T>
  void copy(UniqueParameter128Bit& P, T* const& ptr) { copy(P.pvalue,ptr); }
  template <typename T>
  void copy(T& value, const UniqueParameter128Bit& P) {
    copy(value,P.value<T>());
  }
  template <typename T>
  void copy(T*& ptr, const UniqueParameter128Bit& P) { copy(ptr,P.pvalue); }

  void fill(UniqueParameter128Bit& P, const long double& ld) { copy(P,ld); }
  void fill(UniqueParameter128Bit& P, const double& d) {
    dcopy_(const_cast<long*>(&lTwo),const_cast<double*>(&d),
           const_cast<long*>(&lZero),P.d,const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const float& f) {
    scopy_(const_cast<long*>(&lFour),const_cast<float*>(&f),
           const_cast<long*>(&lZero),P.f,const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const unsigned long long& ull) {
    dcopy_(const_cast<long*>(&lTwo),
           reinterpret_cast<double*>(const_cast<unsigned long long*>(&ull)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(P.ull),
           const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const int& i) {
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<int*>(&i)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(P.i),
           const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const unsigned int& u) {
    scopy_(const_cast<long*>(&lFour),
           reinterpret_cast<float*>(const_cast<unsigned int*>(&u)),
           const_cast<long*>(&lZero),reinterpret_cast<float*>(P.u),
           const_cast<long*>(&lOne));
  }
  void fill(UniqueParameter128Bit& P, const short& s) {
    short *sp=P.s;
    short *pend=sp+8;
    for(;sp!=pend;) copy(*(sp++),s);
  }
  void fill(UniqueParameter128Bit& P, const char& c) {
    char *cp=P.c;
    char *pend=cp+16;
    for(;cp!=pend;) copy(*(cp++),c);
  }

}

#include "vector/interface.h"

namespace mysimulator {

  void copy(Vector<UniqueParameter128Bit>& v,
            const Vector<UniqueParameter128Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    n+=n;
    dcopy_(&n,
        reinterpret_cast<double*>(const_cast<UniqueParameter128Bit*>(cv())),
        const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
        const_cast<long*>(&lOne));
  }

  void fill(Vector<UniqueParameter128Bit>& v, const UniqueParameter128Bit& P) {
    dcopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
           reinterpret_cast<double*>(const_cast<UniqueParameter128Bit*>(&P)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lTwo));
    dcopy_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
           reinterpret_cast<double*>(const_cast<UniqueParameter128Bit*>(&P))+1,
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v())+1,
           const_cast<long*>(&lTwo));
  }

}

#endif

