
#ifndef _Unique_Parameter_64bit_Interface_H_
#define _Unique_Parameter_64bit_Interface_H_

#include "io/error.h"

namespace mysimulator {

  union UniqueParameter64Bit {

    typedef UniqueParameter64Bit  Type;

    double d;
    float f[2];
    unsigned long long ull;
    long long ll;
    int i[2];
    unsigned int u[2];
    short s[4];
    unsigned short us[4];
    char c[8];
    unsigned char uc[8];
    void *ptr[2];

    UniqueParameter64Bit() : ull(0) {}
    UniqueParameter64Bit(const unsigned long long int& l) : ull(l) {}
    UniqueParameter64Bit(const double& d)
      : ull(*reinterpret_cast<const unsigned long long*>(&d)) {}
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
    T*& pointer() { return reinterpret_cast<T*&>(ptr[0]); }
    template <typename T>
    T* const& pointer() const { return reinterpret_cast<T* const&>(ptr[0]); }

  };

  template <>
  double& UniqueParameter64Bit::value<double>() { return d; }
  template <>
  const double& UniqueParameter64Bit::value<double>() const { return d; }

  template <>
  float& UniqueParameter64Bit::value<float>() { return f[0]; }
  template <>
  const float& UniqueParameter64Bit::value<float>() const { return f[0]; }

  template <>
  unsigned long long&
  UniqueParameter64Bit::value<unsigned long long>() { return ull; }
  template <>
  const unsigned long long&
  UniqueParameter64Bit::value<unsigned long long>() const { return ull; }

  template <>
  long long&
  UniqueParameter64Bit::value<long long>() { return ll; }
  template <>
  const long long&
  UniqueParameter64Bit::value<long long>() const { return ll; }

  template <>
  int& UniqueParameter64Bit::value<int>() { return i[0]; }
  template <>
  const int& UniqueParameter64Bit::value<int>() const { return i[0]; }

  template <>
  unsigned int& UniqueParameter64Bit::value<unsigned int>() { return u[0]; }
  template <>
  const unsigned int&
  UniqueParameter64Bit::value<unsigned int>() const { return u[0]; }

  template <>
  unsigned short&
  UniqueParameter64Bit::value<unsigned short>() { return us[0]; }
  template <>
  const unsigned short&
  UniqueParameter64Bit::value<unsigned short>() const { return us[0]; }

  template <>
  short& UniqueParameter64Bit::value<short>() { return s[0]; }
  template <>
  const short& UniqueParameter64Bit::value<short>() const { return s[0]; }

  template <>
  unsigned char& UniqueParameter64Bit::value<unsigned char>() { return uc[0]; }
  template <>
  const unsigned char&
  UniqueParameter64Bit::value<unsigned char>() const { return uc[0]; }

  template <>
  char& UniqueParameter64Bit::value<char>() { return c[0]; }
  template <>
  const char& UniqueParameter64Bit::value<char>() const { return c[0]; }

  template <>
  void*& UniqueParameter64Bit::value<void*>() { return ptr[0]; }
  template <>
  void* const& UniqueParameter64Bit::value<void*>() const { return ptr[0]; }

  bool IsValid(const UniqueParameter64Bit& P) { return true; }
  void release(UniqueParameter64Bit& P) { P.clearData(); }

}

#endif

