
#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "type.h"

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

  template <int> class Convertor;

  template <uint LoopFac=19937>
  class dSFMT {

    private:

      static const uint32_t MExp;

      static const uint32_t N;

      static const uint32_t N32;

      static const uint32_t N64;

      static const uint64_t LowMask;

      static const uint64_t HighConst;

      static const uint32_t SR;

#ifdef HAVE_SSE2

      static const uint32_t SSE2_Shuff;

#endif

      static const uint32_t Pos1;

      static const uint32_t SL1;

      static const uint32_t Msk1;

      static const uint32_t Msk2;

      static const uint32_t Msk32_1;

      static const uint32_t Msk32_2;

      static const uint32_t Msk32_3;

      static const uint32_t Msk32_4;

      static const uint64_t Fix1;

      static const uint64_t Fix2;

      static const uint64_t Pcv1;

      static const uint64_t Pcv2;

      static const char* IDStr;

      union W128_T {

#ifdef HAVE_SSE2

        __m128i   si;

        __m128d   sd;

#endif

        uint64_t  u[2];

        uint32_t  u32[4];

        double    d[2];

      };

      W128_T  status[(LoopFac-128)/104+2];    /// namely N+1

      int idx;

      uint32_t  oui;

      double    od;

      const uint& idxof(const uint& I) { return I; }

#ifdef HAVE_SSE2

      __m128i   SSE2_ParamMask;

      __m128i   SSE2_IntOne;

      __m128d   SSE2_DoubleTwo;

      __m128d   SSE2_DoubleMOne;

      void SetupConst() {
        static int first=1;
        if(!first)  return;
        SSE2_ParamMask=_mm_set_epi32(Msk32_3,Msk32_4,Msk32_1,Msk32_2);
        SSE2_IntOne=_mm_set_epi32(0,1,0,1);
        SSE2_DoubleTwo=_mm_set_pd(2.0,2.0);
        SSE2_DoubleMOne=_mm_set_pd(-1.0,-1.0);
        first=0;
      }

      void DoRecursion(const W128_T& a, const W128_T& b, W128_T& r, W128_T& u){
        __m128i v,w,x,y,z;
        x=a.si;
        z=_mm_slli_epi64(x,SL1);
        y=_mm_shuffle_epi32(u.si,SSE2_Shuff);
        z=_mm_xor_si128(z,b.si);
        y=_mm_xor_si128(y,z);
        v=_mm_srli_epi64(y,SR);
        w=_mm_and_si128(y,SSE2_ParamMask);
        v=_mm_xor_si128(v,x);
        v=_mm_xor_si128(v,w);
        r.si=v;
        u.si=y;
      }

#else

      void DoRecursion(const W128_T& a, const W128_T& b,
                       W128_T& r, W128_T& lung) {
        uint64_t t0,t1,L0,L1;
        t0=a.u[0];
        t1=a.u[1];
        L0=lung.u[0];
        L1=lung.u[1];
        lung.u[0]=(t0<<SL1)^(L1>>32)^(L1<<32)^b.u[0];
        lung.u[1]=(t1<<SL1)^(L0>>32)^(L0<<32)^b.u[1];
        r.u[0]=(lung.u[0]>>SR)^(lung.u[0]&Msk1)^t0;
        r.u[1]=(lung.u[1]>>SR)^(lung.u[1]&Msk2)^t1;
      }

#endif

      template <int BoundaryType>
      void GenRandArray(W128_T& Array, int Size) {
        int i,j;
        W128_T lung;
        static Convertor<BoundaryType> Convert;
        lung=status[N];
        DoRecursion(status[0],status[Pos1],Array[0],lung);
        for(i=0;i<N-Pos1;++i)
          DoRecursion(status[i],status[i+Pos1],Array[i],lung);
        for(;i<Size-N;++i)
          DoRecursion(status[i],Array[i+Pos1-N],Array[i],lung);
        for(;i<Size-N;++i) {
          DoRecursion(Array[i-N],Array[i+Pos1-N],Array[i],lung);
          Convert(Array[i-N]);
        }
        for(j=0;j<N+N-Size;++j) status[j]=Array[j+Size-N];
        for(;i<Size;++i,++j) {
          DoRecursion(Array[i-N],Array[i+Pos1-N],Array[i],lung);
          status[j]=Array[i];
          Convert(Array[i-N]);
        }
        for(i=Size-N;i<Size;++i)  Convert(Array[i]);
        status[N]=lung;
      }

    public:

      dSFMT() {}

  };

}

#endif

