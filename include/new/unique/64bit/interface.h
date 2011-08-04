
#ifndef _Unique_64Bit_Interface_H_
#define _Unique_64Bit_Interface_H_

#include "io/error.h"

namespace mysimulator {

  union Unique64Bit {

    public:

      typedef Unique64Bit   Type;

      double              d;
      float               f[2];
      long long           ll;
      unsigned long long  ull;
      int                 i[2];
      unsigned int        u[2];
      long                l[2];
      unsigned long       ul[2];
      short               s[4];
      unsigned short      us[4];
      char                c[8];
      unsigned char       uc[8];
      void*               ptr[2];

      Unique64Bit() : ull(0) {}
      Unique64Bit(const unsigned long long& l) : ull(l) {}
      Unique64Bit(const double& d)
        : ull(*reinterpret_cast<const unsigned long long*>(&d)) {}
      ~Unique64Bit() { clearData(); }

      void clearData() { ull=0; }
      bool isvalid() const { return true; }

      template <typename T>
      T& value() {
        Error("Type Not included in Unique64Bit!");
        return static_cast<T&>(ull);
      }
      template <typename T>
      const T& value() const {
        Error("Type Not included in Unique64Bit!");
        return static_cast<const T&>(ull);
      }
      template <typename T>
      T*& pointer() { return reinterpret_cast<T*&>(ptr[0]); }
      template <typename T>
      const T* const& pointer() const {
        return reinterpret_cast<const T* const&>(ptr[0]); }

    private:

      Unique64Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const Unique64Bit& U) { return U.isvalid(); }
  void release(Unique64Bit& U) { U.clearData(); }

}


#define _VVALUEDEF(type,val) \
  template<> type& Unique64Bit::value<type>() { return val; }
#define _CVALUEDEF(type,val) \
  template<> const type& Unique64Bit::value<type>() const { return val; }

#define _VALUEDEF(type,val) \
  _VVALUEDEF(type,val)\
  _CVALUEDEF(type,val)

namespace mysimulator {

  _VALUEDEF(double,d)
  _VALUEDEF(float,f[0])
  _VALUEDEF(long long,ll)
  _VALUEDEF(unsigned long long,ull)
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

