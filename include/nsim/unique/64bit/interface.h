
#ifndef _Unique_64Bit_Interface_H_
#define _Unique_64Bit_Interface_H_

#include <cstdio>

#ifndef _NullValueDEF
#define _NullValueDEF(T) \
  fprintf(stderr,"Unknown Type T!\n"); return static_cast<T&>(_data.ull)
#else
#error "Duplicate Definition for Macro _NullValueDEF"
#endif

namespace mysimulator {

  union Unique64BitData {
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
  };

  struct Unique64Bit {

    public:

      typedef Unique64Bit   Type;

      Unique64BitData _data;

      Unique64Bit() : _data() { _data.ull=0; }
      Unique64Bit(const unsigned long long& ill) : _data() { _data.ull=ill; }
      Unique64Bit(const double& d) : _data() {
        _data.ull=*reinterpret_cast<const unsigned long long*>(&d);
      }
      ~Unique64Bit() { Clear(); }

      void Clear() { _data.ull=0; }
      bool IsValid() const { return true; }

      template <typename T>
      T& value() { _NullValueDEF(T); }

      template <typename T>
      const T& value() const { _NullValueDEF(const T); }

    private:

      Unique64Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#ifdef _NullValueDEF
#undef _NullValueDEF
#endif

#if !(defined(_VarValueDEF)||defined(_ConstValueDEF)||defined(_ValueDEF))
#define _VarValueDEF(Type,Val) \
  template<> Type& Unique64Bit::value<Type>() { return _data.Val; }
#define _ConstValueDEF(Type,Val) \
  template<> const Type& Unique64Bit::value<Type>() const { return _data.Val; }
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

#endif

