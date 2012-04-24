
#ifndef _Unique_128Bit_Interface_H_
#define _Unique_128Bit_Interface_H_

#ifdef _HAVE_SSE2
#include <emmintrin.h>
#endif

#include <cstdio>

namespace mysimulator {

  union Unique128Bit;
  void Clear(Unique128Bit&);

  union Unique128Bit {

    public:

      typedef Unique128Bit    Type;

#ifdef _HAVE_SSE2
      __m128              sm;
      __m128i             si;
      __m128d             sd;
#endif
      long double         ld;
      double              d;
      double              dv[2];
      float               f;
      float               fv[4];
      unsigned long long  ull;
      unsigned long long  ullv[2];
      long long           ll;
      long long           llv[2];
      int                 i;
      int                 iv[4];
      unsigned int        u;
      unsigned int        uv[4];
      long                l;
      long                lv[4];
      unsigned long       ul;
      unsigned long       ulv[4];
      short               s;
      short               sv[8];
      unsigned short      us;
      unsigned short      usv[8];
      char                c;
      char                cv[16];
      unsigned char       uc;
      unsigned char       ucv[16];
      void*               ptr;
      void*               pv[4];

      Unique128Bit() { ullv[0]=ullv[1]=0; }
      Unique128Bit(unsigned long long l1,unsigned long long l2) {
        ullv[0]=l1;   ullv[1]=l2;
      }
      Unique128Bit(double d1,double d2) {
        ullv[0]=*reinterpret_cast<unsigned long long*>(&d1);
        ullv[1]=*reinterpret_cast<unsigned long long*>(&d2);
      }
      ~Unique128Bit() { Clear(*this); }

      bool IsValid() const { return true; }

      void Allocate() {}

    private:

      Unique128Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(Unique128Bit& U) { U.ullv[0]=U.ullv[1]=0; }

}

#ifndef _NullDef
#define _NullDef(T) \
  fprintf(stderr,"Unknown Type!\n"); return static_cast<T&>(U.ull);
#else
#error "Duplicate Definition for Macro _NullDef!"
#endif

namespace mysimulator {

  template <typename T>
  T& Value(Unique128Bit& U) { _NullDef(T) }
  template <typename T>
  const T& Value(const Unique128Bit& U) { _NullDef(const T) }

}

#ifdef _NullDef
#undef _NullDef
#endif

#if !(defined(_VarValue)||defined(_CstValue)||defined(_Value))
#define _VarValue(Type,Val) \
  template <> \
  Type& Value<Type>(Unique128Bit& U) { return U.Val; }
#define _CstValue(Type,Val) \
  template <> \
  const Type& Value<Type>(const Unique128Bit& U) { return U.Val; }
#define _Value(Type,Val) \
  _VarValue(Type,Val) \
  _CstValue(Type,Val)
#else
#error "Duplicate Definition for Macro _VarValue,_CstValue,_Value"
#endif

namespace mysimulator {

  _Value(long double,ld)
  _Value(double,d)
  _Value(float,f)
  _Value(unsigned long long,ull)
  _Value(long long,ll)
  _Value(unsigned int,u)
  _Value(int,i)
  _Value(unsigned long,ul)
  _Value(long,l)
  _Value(unsigned short,us)
  _Value(short,s)
  _Value(unsigned char,uc)
  _Value(char,c)

}

#if defined(_VarValue)||defined(_CstValue)||defined(_Value)
#undef _Value
#undef _CstValue
#undef _VarValue
#endif

namespace mysimulator {

  template <typename T>
  T*& Pointer(Unique128Bit& U) { return reinterpret_cast<T*&>(U.ptr); }
  template <typename T>
  const T* const& Pointer(const Unique128Bit& U) {
    return reinterpret_cast<const T* const&>(U.ptr);
  }

}

#endif

