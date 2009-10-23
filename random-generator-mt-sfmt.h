
#ifndef _Random_Generator_MT_SFMT_H_
#define _Random_Generator_MT_SFMT_H_

#include <cstdlib>
#include <cassert>
#include <tr1/csdtint>

namespace std {

  union W128_T {

#ifdef HAVE_SSE2

    __m128i   si;

#endif

    uint32_t u[4];

  };

  template <uint LoopFac=19937>
  class SFMT {

    private:

      static const uint32_t MExp;

      static const uint32_t N;

      static const uint32_t N32;

      static const uint32_t N64;

      static const uint32_t Pos1;

      static const uint32_t SL1;

      static const uint32_t SL2;

      static const uint32_t SR1;

      static const uint32_t SR2;

      static const uint32_t Msk1;

      static const uint32_t Msk2;

      static const uint32_t Msk3;

      static const uint32_t Msk4;
      
      static const uint32_t Parity1;

      static const uint32_t Parity2;

      static const uint32_t Parity3;

      static const uint32_t Parity4;

      static const uint32_t Parity[4];
      
      static const char* IDStr;

      W128_T sfmt[LoopFac/128+1];
      
      uint32_t *psfmt32;
      
      uint64_t *psfmt64;
      
      int idx;
      
      int initialized;
      
      uint32_t oui32;
      
      uint64_t oui64;
      
      double od;
      
      long double old;
      
#ifdef HAVE_SSE2

      __m128i mm_recursion(const __m128i& a, const __m128i& b,
                           const __m128i& c, const __m128i& d,
                           const __m128i& mask) {
      }

#else

#endif

  };

}

#endif

