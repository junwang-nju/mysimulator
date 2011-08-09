
#ifndef _Unique_128Bit_Interface_H_
#define _Unique_128Bit_Interface_H_

#ifdef _Have_SSE2
#include <emmintrin.h>
#endif

#include "io/error.h"

namespace mysimulator {

  union Unique128Bit {

    public:

      typedef Unique128Bit  Type;

#ifdef _Have_SSE2
      __m128  sm;
      __m128i si;
      __m128d sd;
#endif
      long double ld;
      double d[2];
      float f[4];
      long long ll[2];
      unsigned long long ull[2];
      int i[4];
      unsigned int u[4];
      long l[4];
      unsigned long ul[4];
      short s[8];
      unsigned short us[8];
      char c[16];
      unsigned char uc[16];
      void* ptr[4];

      Unique128Bit() { clearData(); }
      Unique128Bit(const unsigned long long& l1, const unsigned long long& l2) {
        ull[0]=l1;  ull[1]=l2;
      }
      Unique128Bit(const double& d1, const double& d2) {
        ull[0]=*reinterpret_cast<const unsigned long long*>(&d1);
        ull[1]=*reinterpret_cast<const unsigned long long*>(&d2);
      }
      ~Unique128Bit() { clearData(); }

      void clearData() { ull[0]=ull[1]=0; }
      bool isvalid() const { return true; }

      template <typename T>
      T& value() {
        Error("Type Not included in Unique128Bit!");
        return static_cast<T&>(ld);
      }
      template <typename T>
      const T& value() const {
        Error("Type Not included in Unique128Bit!");
        return static_cast<const T&>(ld);
      }

      template <typename T>
      T*& pointer() { return reinterpret_cast<T*&>(ptr[0]); }
      template <typename T>
      const T* const& pointer() const {
        return reinterpret_cast<const T* const&>(ptr[0]);
      }

    private:

      Unique128Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const Unique128Bit& U) { return U.isvalid(); }
  void release(Unique128Bit& U) { U.clearData(); }

}

#define _VVALUEDEF(type,val) \
  template<> type& Unique128Bit::value<type>() { return val; }
#define _CVALUEDEF(type,val) \
  template<> const type& Unique128Bit::value<type>() const { return val; }

#define _VALUEDEF(type,val) \
  _VVALUEDEF(type,val)\
  _CVALUEDEF(type,val)

namespace mysimulator {

#ifdef _Have_SSE2
  _VALUEDEF(__m128i,si)
  _VALUEDEF(__m128d,sd)
#endif

  _VALUEDEF(long double,ld)
  _VALUEDEF(double,d[0])
  _VALUEDEF(float,f[0])
  _VALUEDEF(long long,ll[0])
  _VALUEDEF(unsigned long long,ull[0])
  _VALUEDEF(int,i[0])
  _VALUEDEF(unsigned int,u[0])
  _VALUEDEF(long,l[0])
  _VALUEDEF(unsigned long,ul[0])
  _VALUEDEF(short,s[0])
  _VALUEDEF(unsigned short,us[0])
  _VALUEDEF(char,c[0])
  _VALUEDEF(unsigned char,uc[0])

}

#undef _VALUEDEF
#undef _CVALUEDEF
#undef _VVALUEDEF

#endif

