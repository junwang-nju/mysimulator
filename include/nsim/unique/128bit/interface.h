
#ifndef _Unique_128Bit_Interface_H_
#define _Unique_128Bit_Interface_H_

#ifdef _HAVE_SSE2
#include <emmintrin.h>
#endif

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
      int                 i[4];
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

    private:

      Unique128Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(Unique128Bit& U) { U.ullv[0]=U.ullv[1]=0; }

}

#endif

