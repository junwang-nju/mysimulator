
/**
 * @file unique/64bit/interface.h
 * @brief the object with 64 bits and various data formats
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Unique_64Bit_Interface_H_
#define _Unique_64Bit_Interface_H_

#include "type/is-copyable.h"
#include "type/is-fillable.h"

namespace mysimulator {

  union Unique64Bit;
  union Unique128Bit;
  void Clear(Unique64Bit&);

  union Unique64Bit {

    public:

      typedef Unique64Bit   Type;
      template <typename T> friend T& Value(Unique64Bit&);
      template <typename T> friend const T& Value(const Unique64Bit&);
      template <typename T> friend T& Value(Unique64Bit&,unsigned int);
      template <typename T>
      friend const T& Value(const Unique64Bit&,unsigned int);
      template <typename T> friend T*& Pointer(Unique64Bit&);
      template <typename T> friend const T* const& Pointer(const Unique64Bit&);

      Unique64Bit() : ull(0) {}
      Unique64Bit(const unsigned long long& u) : ull(u) {}
      Unique64Bit(const double& d)
        : ull(*reinterpret_cast<const unsigned long long*>(&d)) {}
      ~Unique64Bit() { Clear(*this); }

      bool IsValid() const { return true; }

      void Imprint(const Unique64Bit&) {}
      void Copy(const Unique64Bit& P) { ull=P.ull; }
      template <typename T>
      void Copy(const T& v) {
        typedef typename IsCopyable<Unique64Bit,T>::Type  CopyCheck;
        Value<T>(*this)=v;
      }
      void Copy(const Unique128Bit&);
      template <typename T>
      void Fill(const T& v) {
        typedef typename IsFillable<Unique64Bit,T>::Type  FillCheck;
        for(unsigned int i=0;i<sizeof(double)/sizeof(T);++i)
          Value<T>(*this,i)=v;
      }

    protected:

      double                d;
      double                dv[1];
      float                 f;
      float                 fv[2];
      long long             ll;
      long long             llv[1];
      unsigned long long    ull;
      unsigned long long    ullv[1];
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

    private:

      Unique64Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void _Imprint(Unique64Bit&,const Unique64Bit&) {}
  template <typename T>
  void _Copy(Unique64Bit& P,const T& v) { P.Copy(v); }
  template <typename T>
  void _Copy(T& v,const Unique64Bit& P) {
    typedef typename IsCopyable<T,Unique64Bit>::Type  CopyCheck;
    v=Value<T>(P);
  }
  template <typename T>
  void _Fill(Unique64Bit& P,const T& v) { P.Fill(v); }

}

#include <cstdio>

namespace mysimulator {

  template <typename T>
  T& Value(Unique64Bit& P) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<T&>(P.d);
  }
  template <typename T>
  const T& Value(const Unique64Bit& P) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<const T&>(P.d);
  }

}

#ifndef _VValueDEF_
#define _VValueDEF_(T,v) \
  template <> T& Value<T>(Unique64Bit& P) { return P.v; }
#else
#error "Duplicate _VValueDEF_"
#endif

#ifndef _CValueDEF_
#define _CValueDEF_(T,v)  \
  template <> const T& Value<T>(const Unique64Bit& P) { return P.v; }
#else
#error "Duplicate _CValueDEF_"
#endif

#ifndef _ValueDEF_
#define _ValueDEF_(T,v) \
  _VValueDEF_(T,v) \
  _CValueDEF_(T,v)
#endif

namespace mysimulator {

  _ValueDEF_(double,d)
  _ValueDEF_(float,f)
  _ValueDEF_(long long,ll)
  _ValueDEF_(unsigned long long,ull)
  _ValueDEF_(int,i)
  _ValueDEF_(unsigned int,u)
  _ValueDEF_(long,l)
  _ValueDEF_(unsigned long,ul)
  _ValueDEF_(short,s)
  _ValueDEF_(unsigned short,us)
  _ValueDEF_(char,c)
  _ValueDEF_(unsigned char, uc)

}

#ifdef _ValueDEF_
#undef _ValueDEF_
#endif

#ifdef _CValueDEF_
#undef _CValueDEF_
#endif

#ifdef _VValueDEF_
#undef _VValueDEF_
#endif

namespace mysimulator {

  template <typename T>
  T& Value(Unique64Bit& P, unsigned int n) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<T&>(P.d);
  }
  template <typename T>
  const T& Value(const Unique64Bit& P, unsigned int n) {
    fprintf(stderr,"Unknown Type for Unique64Bit!\n");
    return static_cast<const T&>(P.d);
  }

}

#include <cassert>

#ifndef _VValueDEF_
#define _VValueDEF_(T,u) \
  template <> T& Value<T>(Unique64Bit& P,unsigned int n) { \
    assert(n<sizeof(double)/sizeof(T)); \
    return P.u[n]; \
  }
#else
#error "Duplicate _VValueDEF_"
#endif

#ifndef _CValueDEF_
#define _CValueDEF_(T,u) \
  template <> const T& Value<T>(const Unique64Bit& P,unsigned int n) { \
    assert(n<sizeof(double)/sizeof(T)); \
    return P.u[n]; \
  }
#else
#error "Duplicate _CValueDEF_"
#endif

#ifndef _ValueDEF_
#define _ValueDEF_(T,u) \
  _VValueDEF_(T,u) \
  _CValueDEF_(T,u)
#else
#error "Duplicate _ValueDEF_"
#endif

namespace mysimulator {

  _ValueDEF_(double,dv)
  _ValueDEF_(float,fv)
  _ValueDEF_(long long,llv)
  _ValueDEF_(unsigned long long,ullv)
  _ValueDEF_(int,iv)
  _ValueDEF_(unsigned int,uv)
  _ValueDEF_(long,lv)
  _ValueDEF_(unsigned long,ulv)
  _ValueDEF_(short,sv)
  _ValueDEF_(unsigned short,usv)
  _ValueDEF_(char,cv)
  _ValueDEF_(unsigned char, ucv)

}

#ifdef _ValueDEF_
#undef _ValueDEF_
#endif

#ifdef _CValueDEF_
#undef _CValueDEF_
#endif

#ifdef _VValueDEF_
#undef _VValueDEF_
#endif

namespace mysimulator {

  template <typename T>
  T*& Pointer(Unique64Bit& P) { return reinterpret_cast<T*&>(P.ptr); }

  template <typename T>
  const T* const& Pointer(const Unique64Bit& P) {
    return reinterpret_cast<const T* const&>(P.ptr);
  }

  void Clear(Unique64Bit& P) { Value<unsigned long long>(P)=0; }

}

#include "unique/128bit/interface.h"

namespace mysimulator {

  void Unique64Bit::Copy(const Unique128Bit& U) {
    Copy(Value<unsigned long long>(U));
  }

  void _Copy(Unique64Bit& U,const Unique128Bit& LU) { U.Copy(LU); }

}

#endif

