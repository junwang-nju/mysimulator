
#ifndef _Unique_Parameter_128bit_Interface_H_
#define _Unique_Parameter_128bit_Interface_H_

#ifdef _Have_SSE2
#include <emmintrin.h>
#endif

#include "io/error.h"

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
    UniqueParameter128Bit(const unsigned long long int& l1,
                          const unsigned long long int& l2) {
      ull[0]=l1;
      ull[1]=l2;
    }
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

}

#endif

