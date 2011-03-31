
#ifndef _Unique_Parameter_64bit_H_
#define _Unique_Parameter_64bit_H_

#include "io/error.h"
#include "intrinsic-type/copy.h"

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

  void copy(UniqueParameter64Bit& P, const UniqueParameter64Bit& cP) {
    P.ull=cP.ull;
  }
  template <typename T>
  void copy(UniqueParameter64Bit& P, const T& value) {
    copy(P.value<T>(),value);
  }
  template <typename T>
  void copy(UniqueParameter64Bit& P, const T* ptr) { copy(P.ptr,ptr); }

  template <typename T>
  void copy(T& value, const UniqueParameter64Bit& P) {
    copy(value,P.value<T>());
  }
  template <typename T>
  void copy(T*& ptr, const UniqueParameter64Bit& P) { copy(ptr,P.ptr); }

}

#include "vector/interface.h"

namespace mysimulator {

  void copy(Vector<UniqueParameter64Bit>& v,
            const Vector<UniqueParameter64Bit>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,
           reinterpret_cast<double*>(const_cast<UniqueParameter64Bit*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v, const UniqueParameter64Bit& d) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<UniqueParameter64Bit*>(&d)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v, const Vector<double>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,const_cast<double*>(cv()),const_cast<long*>(&lOne),
           reinterpret_cast<double*>(v()),const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v,
            const Vector<unsigned long long>& cv) {
    assert(IsValid(v)&&IsValid(cv));
    long n=(v.size<cv.size?v.size:cv.size);
    dcopy_(&n,reinterpret_cast<double*>(const_cast<unsigned long long*>(cv())),
           const_cast<long*>(&lOne),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

  void copy(Vector<UniqueParameter64Bit>& v, const double& d) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)), const_cast<double*>(&d),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }
  void copy(Vector<UniqueParameter64Bit>& v, const unsigned long long& d) {
    assert(IsValid(v));
    dcopy_(reinterpret_cast<long*>(&(v.size)),
           reinterpret_cast<double*>(const_cast<unsigned long long*>(&d)),
           const_cast<long*>(&lZero),reinterpret_cast<double*>(v()),
           const_cast<long*>(&lOne));
  }

}

#endif

