
#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "type.h"
#include "region-boundary-type.h"

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

      uint32_t init_func1(const uint32_t& x) {
        return (x^(x>>27))*static_cast<uint32_t>(1664525UL);
      }

      uint32_t init_func2(const uint32_t& x) {
        return (x^(x>>27))*static_cast<uint32_t>(1566083941UL);
      }

      uint32_t init_mask() {
        uint64_t *pSFMT;
        pSFMT=&(status[0].u[0]);
        for(uint i=0;i<N+N;++i) pSFMT[i]=(pSFMT[i]&LowMask)|HighConst;
      }

      void PeriodCertification() {
        uint64_t pcv[2]={Pcv1,Pcv2};
        uint64_t tmp[2];
        uint64_t inner;
        int i;
        tmp[0]=status[N].u[0]^Fix1;
        tmp[1]=status[N].u[1]^Fix2;
        inner=tmp[0]&pcv[0];
        inner^=tmp[1]&pcv[1];
        for(i=32;i>0;i>>=1)   inner^=inner>>i;
        inner&=1;
        if(inner==1)    return;
        status[N].u[1]^=1;
        return;
      } // Here assuming Pcv2&1==1

      void GenRandAll() {
        uint32_t i;
        W128_T lung;
        DoRecursion(status[0],status[Pos1],status[0],lung);
        for(i=1;i<N-Pos1;++i)
          DoRecursion(status[i],status[i+Pos1],status[i],lung);
        for(;i<N;++i)
          DoRecursion(status[i],status[i+Pos1-N],status[i],lung);
        status[N]=lung;
      }

    public:

      typedef dSFMT<LoopFac>    Type;

      dSFMT() {}

      dSFMT(const Type& DR) { assert(false); }

      dSFMT(const uint32_t& seed) { Init(seed); }

      const char* IDString() { return IDStr; }

      int GetMinArraySize() { return N64; }

      template <uint BoundaryType>
      void FillArray(double *Array, int Size) {
        assert((Size&1)==0);
        assert(Size>=N64);
        GenRandArray<BoundaryType>(static_cast<W128_T*>(Array),Size>>1);
      }

      template <typename vType, uint BoundaryType>
      void FillArray(vType& V) {
        assert(vType::isVector);
        FillArray<BoundaryType>(V.data(),V.size());
      }

      void Init(const uint32_t& seed) {
        uint32_t *pSFMT;
        pSFMT=&status[0].u32[0];
        pSFMT[idxof(0)]=seed;
        uint sz=(N+1)*4;
        for(uint i=1;i<sz;++i)
          pSFMT[idxof(i)]=
            1812433253UL*(pSFMT[idxof(i-1)]^(pSFMT[idxof(i-1)]>>30))+i;
        init_mask();
        PeriodCertification();
        idx=N64;
#ifdef HAVE_SSE2
        SetupConst();
#endif
      }

      void Init(uint32_t* init_key, int key_length) {
        uint32_t r, *pSFMT32;
        int i,j,count,lag,mid,tmid;
        int size=(N+1)*4;
        if(size>=623)         lag=11;
        else if(size>=68)     lag=7;
        else if(size>=39)     lag=5;
        else                  lag=3;
        mid=(size-lag)/2;
        pSFMT32=&status[0].u32[0];
        memset(status,0x8B,sizeof(status));
        count=(key_length+1>size?key_length+1:size);
        tmid=mid%size;
        r=init_func1(pSFMT32[idxof(0)]^pSFMT32[idxof(tmid)]
                     ^pSFMT32[idxof(size-1)]);
        pSFMT32[idxof(tmid)]+=r;
        r+=key_length;
        pSFMT32[idxof((mid+lag)%size)]+=r;
        pSFMT32[idxof(0)]=r;
        --count;
      }

  };

}

#endif

