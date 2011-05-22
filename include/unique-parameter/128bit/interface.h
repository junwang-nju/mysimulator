
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
    long long ll[2];
    int i[4];
    unsigned int u[4];
    unsigned short us[8];
    short s[8];
    unsigned char uc[16];
    char c[16];
    void *ptr[4];

    UniqueParameter128Bit() { ull[0]=ull[1]=0; }
    UniqueParameter128Bit(const unsigned long long int& l1,
                          const unsigned long long int& l2) {
      ull[0]=l1;
      ull[1]=l2;
    }
    UniqueParameter128Bit(const double& d1, const double& d2) {
      ull[0]=*reinterpret_cast<const unsigned long long*>(&d1);
      ull[1]=*reinterpret_cast<const unsigned long long*>(&d2);
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
  double& UniqueParameter128Bit::value<double>() { return d[0]; }
  template <>
  const double& UniqueParameter128Bit::value<double>() const { return d[0]; }

  template <>
  float& UniqueParameter128Bit::value<float>() { return f[0]; }
  template <>
  const float& UniqueParameter128Bit::value<float>() const { return f[0]; }

  template <>
  unsigned long long&
  UniqueParameter128Bit::value<unsigned long long>() { return ull[0]; }
  template <>
  const unsigned long long&
  UniqueParameter128Bit::value<unsigned long long>() const { return ull[0]; }

  template <>
  long long&
  UniqueParameter128Bit::value<long long>() { return ll[0]; }
  template <>
  const long long&
  UniqueParameter128Bit::value<long long>() const { return ll[0]; }

  template <>
  int& UniqueParameter128Bit::value<int>() { return i[0]; }
  template <>
  const int& UniqueParameter128Bit::value<int>() const { return i[0]; }

  template <>
  unsigned int& UniqueParameter128Bit::value<unsigned int>() { return u[0]; }
  template <>
  const unsigned int&
  UniqueParameter128Bit::value<unsigned int>() const { return u[0]; }

  template <>
  short& UniqueParameter128Bit::value<short>() { return s[0]; }
  template <>
  const short& UniqueParameter128Bit::value<short>() const { return s[0]; }

  template <>
  unsigned short&
  UniqueParameter128Bit::value<unsigned short>() { return us[0]; }
  template <>
  const unsigned short&
  UniqueParameter128Bit::value<unsigned short>() const { return us[0]; }

  template <>
  char& UniqueParameter128Bit::value<char>() { return c[0]; }
  template <>
  const char& UniqueParameter128Bit::value<char>() const { return c[0]; }

  template <>
  unsigned char&
  UniqueParameter128Bit::value<unsigned char>() { return uc[0]; }
  template <>
  const unsigned char&
  UniqueParameter128Bit::value<unsigned char>() const { return uc[0]; }

  template <>
  void*& UniqueParameter128Bit::value<void*>() { return ptr[0]; }
  template <>
  void* const& UniqueParameter128Bit::value<void*>() const { return ptr[0]; }

  bool IsValid(const UniqueParameter128Bit&) { return true; }
  void release(UniqueParameter128Bit& P) { return P.clearData(); }

}

#endif

