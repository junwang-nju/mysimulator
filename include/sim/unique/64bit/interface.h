
#ifndef _Unique_64Bit_Interface_H_
#define _Unique_64Bit_Interface_H_

#include <cstdio>

namespace mysimulator {

  union Unique64Bit {

    public:

      typedef Unique64Bit Type;

      double              d;
      float               f;
      float               fv[2];
      long long           ll;
      unsigned long long  ull;
      int                 i;
      int                 iv[2];
      unsigned int        u;
      unsigned int        uv[2];
      long                l;
      long                lv[2];
      unsigned long       ul;
      unsigned long       ulv[2];
      short               s;
      short               sv[4]
      unsigned short      us;
      unsigned short      usv[4];
      char                c;
      char                cv[8]
      unsigned char       uc;
      unsigned char       ucv[8];
      void*               ptr;
      void*               pv[2];

      Unique64Bit() : ull(0) {}
      Unique64Bit(const unsigned long long& ill) : ull(ill) {}
      Unique64Bit(const double& d)
        : ull(*reinterpret_cast<const unsigned long long*>(&d)) {}
      ~Unique64Bit() { clearData(); }

      void clearData() { ull=0; }
      bool isvalid() const { return true; }

      template <typename T>
      T& value() {
        sprintf("Unknown Type T!");
        return static_cast<T&>(ull);
      }
      template <typename T>
      const T& value() const {
        sprintf("Unknown Type T!");
        return static_cast<const T&>(ull);
      }

    private:

      Unique64Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  bool IsValid(const Unique64Bit& U) { return U.isvalid(); }
  void release(Unique64Bit& U) { U.clearData(); }

}

#if (!defined(_VValueDEF))&&(!defined(_CValueDEF))
#define _VValueDEF(type,val) \
  template<> type& Unique64Bit::value<type>() { return val; }
#define _CValueDEF(type,val) \
  template<> const type& Unique64Bit::value<type>() const { return val; }
#define _ValueDEF(type,val) \
  _VValueDEF(type,val) \
  _CValueDEF(type,val)
#else
#error "Duplicate Definitions of _VValueDEF and _CValueDEF"
#endif

namespace mysimulator {

  _ValueDEF(double,d)
  _ValueDEF(float,f)
  _ValueDEF(long long,ll)
  _ValueDEF(unsigned long long,ull)
  _ValueDEF(int,i)
  _ValueDEF(unsigned int,u)
  _ValueDEF(long,l)
  _ValueDEF(unsigned long,ul)
  _ValueDEF(short,s)
  _ValueDEF(unsigned short,us)
  _ValueDEF(char,c)
  _ValueDEF(unsigned char,uc)

}

#ifdef  _ValueDEF
#undef  _ValueDEF
#endif

#ifdef  _VValueDEF
#undef  _VValueDEF
#endif

#ifdef  _CValueDEF
#undef  _CValueDEF
#endif

#endif

