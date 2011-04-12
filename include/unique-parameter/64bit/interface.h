
#ifndef _Unique_Parameter_64bit_Interface_H_
#define _Unique_Parameter_64bit_Interface_H_

#include "io/error.h"

namespace mysimulator {

  union UniqueParameter64Bit {

    typedef UniqueParameter64Bit  Type;

    double d;
    float f;
    unsigned long long ull;
    unsigned int u;
    int i;
    short s;
    char c;
    void *ptr;
    float fdata[2];
    unsigned int udata[2];
    int idata[2];
    short sdata[4];
    char cdata[8];
    void *pdata[2];

    UniqueParameter64Bit() : ull(0) {}
    UniqueParameter64Bit(const unsigned long long int& l) : ull(l) {}
    UniqueParameter64Bit(const Type&) {
      Error("Copier of UniqueParameter64Bit Disabled!");
    }
    Type& operator=(const Type& P) {
      Error("Operator= for UniqueParameter64Bit Disabled!");
      return *this;
    }
    ~UniqueParameter64Bit() { clearData(); }

    void clearData() {}
    template <typename T>
    T& value() {
      Error("Not-Included Type in UniqueParameter64Bit!");
      static T tvalue=static_cast<T>(0);
      return tvalue;
    }
    template <typename T>
    const T& value() const {
      Error("Not-Included Type in UniqueParameter64Bit!");
      static T tvalue=static_cast<T>(0);
      return tvalue;
    }
    template <typename T>
    T*& pointer() { return reinterpret_cast<T*&>(ptr); }
    template <typename T>
    T* const& pointer() const { return reinterpret_cast<T* const&>(ptr); }

  };

  template <>
  double& UniqueParameter64Bit::value<double>() { return d; }
  template <>
  const double& UniqueParameter64Bit::value<double>() const { return d; }

  template <>
  float& UniqueParameter64Bit::value<float>() { return f; }
  template <>
  const float& UniqueParameter64Bit::value<float>() const { return f; }

  template <>
  int& UniqueParameter64Bit::value<int>() { return i; }
  template <>
  const int& UniqueParameter64Bit::value<int>() const { return i; }

  template <>
  unsigned int& UniqueParameter64Bit::value<unsigned int>() { return u; }
  template <>
  const unsigned int& UniqueParameter64Bit::value<unsigned int>() const {
    return u;
  }

  template <>
  short& UniqueParameter64Bit::value<short>() { return s; }
  template <>
  const short& UniqueParameter64Bit::value<short>() const { return s; }

  template <>
  char& UniqueParameter64Bit::value<char>() { return c; }
  template <>
  const char& UniqueParameter64Bit::value<char>() const { return c; }

  template <>
  unsigned long long& UniqueParameter64Bit::value<unsigned long long>() {
    return ull;
  }
  template <>
  const unsigned long long&
  UniqueParameter64Bit::value<unsigned long long>() const { return ull; }

  template <>
  void*& UniqueParameter64Bit::value<void*>() { return ptr; }
  template <>
  void* const& UniqueParameter64Bit::value<void*>() const { return ptr; }

  bool IsValid(const UniqueParameter64Bit& P) { return true; }
  void release(UniqueParameter64Bit& P) { P.clearData(); }

}

#endif

