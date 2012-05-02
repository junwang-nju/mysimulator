
#ifndef _Unique_64Bit_Interface_H_
#define _Unique_64Bit_Interface_H_

#include <cstdio>

namespace mysimulator {

  union Unique64Bit {

    public:

      typedef Unique64Bit   Type;

      double                d;
      float                 f;
      float                 fv[2];
      long long             ll;
      unsigned long long    ull;
      int                   i;
      int                   iv[2];
      unsigned int          u;
      unsigned int          uv[2];
      long                  l;
      long                  lv[2];
      unsigned long         ul;
      unsigned long         ulv[2];
      short                 s;
      short                 sv[4];
      unsigned short        us;
      unsigned short        usv[4];
      char                  c;
      char                  cv[8];
      unsigned char         uc;
      unsigned char         ucv[8];
      void*                 ptr;
      void*                 pv[8];

      Unique64Bit() : ull(0) {}
      Unique64Bit(const unsigned long long& ill) : ull(ill) {}
      Unique64Bit(const double& d)
        : ull(*reinterpret_cast<const unsigned long long*>(&d)) {}
      ~Unique64Bit() { Clear(); }

      void Clear() { ull=0; }
      bool IsValid() const { return true; }

    private:

      Unique64Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#ifndef _NullValueDEF
#define _NullValueDEF(T) \
  fprintf(stderr,"Unknown Type T!\n"); return static_cast<T&>(U.ull)
#else
#error "Duplicate Definition for Macro _NullValueDEF"
#endif

namespace mysimulator {

  template <typename T>
  T& Value(Unique64Bit& U) { _NullValueDEF(T); }
  template <typename T>
  const T& Value(const Unique64Bit& U) { _NullValueDEF(const T); }

}

#ifdef _NullValueDEF
#undef _NullValueDEF
#endif

#if !(defined(_VarValueDEF)||defined(_ConstValueDEF)||defined(_ValueDEF))
#define _VarValueDEF(Type,Val) \
  template<> Type& Value<Type>(Unique64Bit& U) { return U.Val; }
#define _ConstValueDEF(Type,Val) \
  template<> const Type& Value<Type>(const Unique64Bit& U) { return U.Val; }
#define _ValueDEF(Type,Val) \
  _VarValueDEF(Type,Val) \
  _ConstValueDEF(Type,Val)
#else
#error "Duplicate Definition for Macro _VarValueDEF,_ConstValueDEF,_ValueDEF"
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
  _ValueDEF(unsigned char, uc)

}

#if defined(_VarValueDEF)||defined(_ConstValueDEF)||defined(_ValueDEF)
#undef _ValueDEF
#undef _ConstValueDEF
#undef _VarValueDEF
#endif

namespace mysimulator {

  template <typename T>
  T*& Pointer(Unique64Bit& U) { return reinterpret_cast<T*&>(U.ptr); }
  template <typename T>
  const T* const& Pointer(const Unique64Bit& U) {
    return reinterpret_cast<const T* const&>(U.ptr);
  }

}

#endif

