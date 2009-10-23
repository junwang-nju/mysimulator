
#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "type.h"
#include "region-boundary-type.h"

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

  template <uint> class Convertor;

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

      static const uint64_t Msk1;

      static const uint64_t Msk2;

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

      void init_mask() {
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

      dSFMT() { assert(false); }

      dSFMT(const Type& DR) { assert(false); }

      dSFMT(const uint32_t& seed) { assert(false); }

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
        for(i=1,j=0;(j<count)&&(j<key_length);++j) {
          tmid=(i+mid)%size;
          r=init_func1(pSFMT32[idxof(i)]^pSFMT32[idxof(tmid)]
                       ^pSFMT32[idxof((i+size-1)%size)]);
          pSFMT32[idxof(tmid)]+=r;
          r+=init_key[j]+i;
          pSFMT32[idxof((i+mid+lag)%size)]+=r;
          pSFMT32[idxof(i)]=r;
          i=(i+1)%size;
        }
        for(;j<count;++j) {
          tmid=(i+mid)%size;
          r=init_func1(pSFMT32[idxof(i)]^pSFMT32[idxof(tmid)]
                       ^pSFMT32[idxof((i+size-1)%size)]);
          pSFMT32[idxof(tmid)]+=r;
          r+=i;
          pSFMT32[idxof((i+mid+lag)%size)]+=r;
          pSFMT32[idxof(i)]=r;
          i=(i+1)%size;
        }
        for(j=0;j<size;++j) {
          tmid=(i+mid)%size;
          r=init_func2(pSFMT32[idxof(i)]+pSFMT32[idxof(tmid)]
                       +pSFMT32[idxof((i+size-1)%size)]);
          pSFMT32[idxof(tmid)]^=r;
          r-=i;
          pSFMT32[idxof((i+mid+lag)%size)]^=r;
          pSFMT32[idxof(i)]=r;
          i=(i+1)%size;
        }
        init_mask();
        PeriodCertification();
        idx=N64;
#ifdef HAVE_SSE2
        SetupConst();
#endif
      }

      const uint32_t& GenRandUint32() {
        uint64_t *pSFMT64=&status[0].u[0];
        if(idx>=N64) {
          GenRandAll();
          idx=0;
        }
        oui=pSFMT64[idx++]&0xFFFFFFFFUL;
        return oui;
      }

      const double& GenRand_Close1Open2() {
        double *pSFMT64=&status[0].d[0];
        if(static_cast<uint32_t>(idx)>=N64) {
          GenRandAll();
          idx=0;
        }
        od=pSFMT64[idx++];
        return od;
      }

      const double& GenRand_Close0Open1() {
        od=GenRand_Close1Open2()-1.0;
        return od;
      }

      const double& GenRand_Open0Close1() {
        od=2.0-GenRand_Close1Open2();
        return od;
      }

      const double& GenRand_Open0Open1() {
        double *dSFMT64=&status[0].d[0];
        union {
          double d;
          uint64_t u;
        } r;
        if(idx>=N64) {
          GenRandAll();
          idx=0;
        }
        r.d=dSFMT64[idx++];
        r.u|=1;
        od=r.d-1.0;
        return od;
      }

      const double& Default(const double&) { return GenRand_Close0Open1(); }

      const uint32_t& Default(const uint32_t&) { return GenRandUint32(); }

  };

  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::MExp=LoopFac;

  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::N=((MExp-128)/104+1);

  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::N32=N*4;

  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::N64=N*2;

  template <uint LoopFac>
  const uint64_t dSFMT<LoopFac>::LowMask=0x000FFFFFFFFFFFFFULL;

  template <uint LoopFac>
  const uint64_t dSFMT<LoopFac>::HighConst=0x3FF0000000000000ULL;

  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::SR=12;

#ifdef HAVE_SSE2

  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::SSE2_Shuff=0x1BU;

#endif

  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::Pos1=0U;

  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::SL1=0U;

  template <uint LoopFac>
  const uint64_t dSFMT<LoopFac>::Msk1=0ULL;

  template <uint LoopFac>
  const uint64_t dSFMT<LoopFac>::Msk2=0ULL;
  
  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::Msk32_1=0U;
  
  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::Msk32_3=0U;
  
  template <uint LoopFac>
  const uint32_t dSFMT<LoopFac>::Msk32_4=0U;
  
  template <uint LoopFac>
  const uint64_t dSFMT<LoopFac>::Fix1=0ULL;
  
  template <uint LoopFac>
  const uint64_t dSFMT<LoopFac>::Fix2=0ULL;
  
  template <uint LoopFac>
  const uint64_t dSFMT<LoopFac>::Pcv1=0ULL;
  
  template <uint LoopFac>
  const uint64_t dSFMT<LoopFac>::Pcv2=0ULL;
  
  template <uint LoopFac>
  const char* dSFMT<LoopFac>::IDStr="";
  
  template <>
  const uint32_t dSFMT<521>::Pos1=3;
  
  template <>
  const uint32_t dSFMT<521>::SL1=25;

  template <>
  const uint64_t dSFMT<521>::Msk1=0x000FBFEFFF77EFFFULL;
  
  template <>
  const uint64_t dSFMT<521>::Msk2=0x000FFEEBFBDFBFDFULL;
  
  template <>
  const uint32_t dSFMT<521>::Msk32_1=0x000FBFEFU;
  
  template <>
  const uint32_t dSFMT<521>::Msk32_2=0xFF77EFFFU;
  
  template <>
  const uint32_t dSFMT<521>::Msk32_3=0x000FFEEBU;
  
  template <>
  const uint32_t dSFMT<521>::Msk32_4=0xFBDFBFDFU;
  
  template <>
  const uint64_t dSFMT<521>::Fix1=0xCFB393D661638469ULL;
  
  template <>
  const uint64_t dSFMT<521>::Fix2=0xC166867883AE2ADBULL;
  
  template <>
  const uint64_t dSFMT<521>::Pcv1=0xCCAA588000000000ULL;

  template <>
  const uint64_t dSFMT<521>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<521>::IDStr=
    "dSFMT2-521:3-25:FBFEFFF77EFFF-FFEEBFBDFBFDF";

  template <>
  dSFMT<521>::dSFMT() {}
  
  template <>
  dSFMT<521>::dSFMT(const uint32_t& seed) { Init(seed); }

  template <>
  const uint32_t dSFMT<1279>::Pos1=9;
  
  template <>
  const uint32_t dSFMT<1279>::SL1=19;
  
  template <>
  const uint64_t dSFMT<1279>::Msk1=0x000EFFF7FFDDFFEEULL;
  
  template <>
  const uint64_t dSFMT<1279>::Msk2=0x000FBFFFFFF77FFFULL;
  
  template <>
  const uint32_t dSFMT<1279>::Msk32_1=0x000EFFF7U;
  
  template <>
  const uint32_t dSFMT<1279>::Msk32_2=0xFFDDFFEEU;
  
  template <>
  const uint32_t dSFMT<1279>::Msk32_3=0x000FBFFFU;
  
  template <>
  const uint32_t dSFMT<1279>::Msk32_4=0xFFF77FFFU;
  
  template <>
  const uint64_t dSFMT<1279>::Fix1=0xB66627623D1A31BEULL;
  
  template <>
  const uint64_t dSFMT<1279>::Fix2=0x04B6C51147B6109BULL;
  
  template <>
  const uint64_t dSFMT<1279>::Pcv1=0x7049F2DA382A6AEBULL;
  
  template <>
  const uint64_t dSFMT<1279>::Pcv2=0xDE4CA84A40000001ULL;

  template <>
  const char* dSFMT<1279>::IDStr=
    "dSFMT2-1279:9-19:EFFF7FFDDFFEE-FBFFFFFF77FFF";

  template <>
  dSFMT<1279>::dSFMT() {}
  
  template <>
  dSFMT<1279>::dSFMT(const uint32_t& seed) { Init(seed); }

  template <>
  const uint32_t dSFMT<2203>::Pos1=7;

  template <>
  const uint32_t dSFMT<2203>::SL1=19;

  template <>
  const uint64_t dSFMT<2203>::Msk1=0x000FDFFFF5EDBFFFULL;
  
  template <>
  const uint64_t dSFMT<2203>::Msk2=0x000F77FFFFFFFBFEULL;

  template <>
  const uint32_t dSFMT<2203>::Msk32_1=0x000FDFFFU;
  
  template <>
  const uint32_t dSFMT<2203>::Msk32_2=0xF5EDBFFFU;
  
  template <>
  const uint32_t dSFMT<2203>::Msk32_3=0x000F77FFU;
  
  template <>
  const uint32_t dSFMT<2203>::Msk32_4=0xFFFFFBFEU;
  
  template <>
  const uint64_t dSFMT<2203>::Fix1=0xB14E907A39338485ULL;
  
  template <>
  const uint64_t dSFMT<2203>::Fix2=0xF98F0735C637EF90ULL;
  
  template <>
  const uint64_t dSFMT<2203>::Pcv1=0x8000000000000000ULL;
  
  template <>
  const uint64_t dSFMT<2203>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<2203>::IDStr=
    "dSFMT2-2203:7-19:FDFFFF5EDBFFF-F77FFFFFFFBFE";

  template <>
  dSFMT<2203>::dSFMT() {}
  
  template <>
  dSFMT<2203>::dSFMT(const uint32_t& seed) { Init(seed); }

  template <>
  const uint32_t dSFMT<4253>::Pos1=19;
  
  template <>
  const uint32_t dSFMT<4253>::SL1=19;
  
  template <>
  const uint64_t dSFMT<4253>::Msk1=0x0007B7FFFEF5FEFFULL;
  
  template <>
  const uint64_t dSFMT<4253>::Msk2=0x000FFDFFEFFEFBFCULL;
  
  template <>
  const uint32_t dSFMT<4253>::Msk32_1=0x0007B7FFU;
  
  template <>
  const uint32_t dSFMT<4253>::Msk32_2=0xFEF5FEFFU;
  
  template <>
  const uint32_t dSFMT<4253>::Msk32_3=0x000FFDFFU;
  
  template <>
  const uint32_t dSFMT<4253>::Msk32_4=0xEFFEFBFCU;

  template <>
  const uint64_t dSFMT<4253>::Fix1=0x80901B5FD7A11C65ULL;
  
  template <>
  const uint64_t dSFMT<4253>::Fix2=0x5A63FF0E7CB0BA74ULL;
  
  template <>
  const uint64_t dSFMT<4253>::Pcv1=0x1AD277BE12000000ULL;
  
  template <>
  const uint64_t dSFMT<4253>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<4253>::IDStr=
    "dSFMT2-4253:19-19:7B7FFFEF5FEFF-FFDFFEFFEFBFC";

  template <>
  dSFMT<4253>::dSFMT() {}
  
  template <>
  dSFMT<4253>::dSFMT(const uint32_t& seed) { Init(seed); }

  template <>
  const uint32_t dSFMT<11213>::Pos1=37;
  
  template <>
  const uint32_t dSFMT<11213>::SL1=19;
  
  template <>
  const uint64_t dSFMT<11213>::Msk1=0x000FFFFFFDF7FFFDULL;
  
  template <>
  const uint64_t dSFMT<11213>::Msk2=0x000DFFFFFFF6BFFFULL;
  
  template <>
  const uint32_t dSFMT<11213>::Msk32_1=0x000FFFFFU;
  
  template <>
  const uint32_t dSFMT<11213>::Msk32_2=0xFDF7FFFDU;
  
  template <>
  const uint32_t dSFMT<11213>::Msk32_3=0x000DFFFFU;
  
  template <>
  const uint32_t dSFMT<11213>::Msk32_4=0xFFF6BFFFU;
  
  template <>
  const uint64_t dSFMT<11213>::Fix1=0xD0EF7B7C75B06793ULL;

  template <>
  const uint64_t dSFMT<11213>::Fix2=0x9C50FF4CAAE0A641ULL;
  
  template <>
  const uint64_t dSFMT<11213>::Pcv1=0x8234C51207C80000ULL;
  
  template <>
  const uint64_t dSFMT<11213>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<11213>::IDStr=
    "dSFMT2-11213:37-19:FFFFFFDF7FFFD-DFFFFFFF6BFFF";
    
  template <>
  dSFMT<11213>::dSFMT() {}
  
  template <>
  dSFMT<11213>::dSFMT(const uint32_t& seed) { Init(seed); }
  
  template <>
  const uint32_t dSFMT<19937>::Pos1=117;
  
  template <>
  const uint32_t dSFMT<19937>::SL1=19;
  
  template <>
  const uint64_t dSFMT<19937>::Msk1=0x000FFAFFFFFFFB3FULL;
  
  template <>
  const uint64_t dSFMT<19937>::Msk2=0x000FFDFFFC90FFFDULL;
  
  template <>
  const uint32_t dSFMT<19937>::Msk32_1=0x000FFAFFU;
  
  template <>
  const uint32_t dSFMT<19937>::Msk32_2=0xFFFFFB3FU;
  
  template <>
  const uint32_t dSFMT<19937>::Msk32_3=0x000FFDFFU;
  
  template <>
  const uint32_t dSFMT<19937>::Msk32_4=0xFC90FFFDU;
  
  template <>
  const uint64_t dSFMT<19937>::Fix1=0x90014964B32F4329ULL;
  
  template <>
  const uint64_t dSFMT<19937>::Fix2=0x3B8D12AC548A7C7AULL;
  
  template <>
  const uint64_t dSFMT<19937>::Pcv1=0x3D84E1AC0DC82880ULL;
  
  template <>
  const uint64_t dSFMT<19937>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<19937>::IDStr=
    "dSFMT2-19937:117-19:FFAFFFFFFFB3F-FFDFFFC90FFFD";
    
  template <>
  dSFMT<19937>::dSFMT() {}
  
  template <>
  dSFMT<19937>::dSFMT(const uint32_t& seed) { Init(seed); } 

  template <>
  const uint32_t dSFMT<44497>::Pos1=304;
  
  template <>
  const uint32_t dSFMT<44497>::SL1=19;
  
  template <>
  const uint64_t dSFMT<44497>::Msk1=0x000FF6DFFFFFFFEFULL;
  
  template <>
  const uint64_t dSFMT<44497>::Msk2=0x0007FFDDDEEFFF6FULL;
  
  template <>
  const uint32_t dSFMT<44497>::Msk32_1=0x000FF6DFU;
  
  template <>
  const uint32_t dSFMT<44497>::Msk32_2=0xFFFFFFEFU;
  
  template <>
  const uint32_t dSFMT<44497>::Msk32_3=0x0007FFDDU;
  
  template <>
  const uint32_t dSFMT<44497>::Msk32_4=0xDEEFFF6FU;
  
  template <>
  const uint64_t dSFMT<44497>::Fix1=0x75D910F235F6E10EULL;
  
  template <>
  const uint64_t dSFMT<44497>::Fix2=0x7B32158AEDC8E969ULL;
  
  template <>
  const uint64_t dSFMT<44497>::Pcv1=0x4C3356B2A0000000ULL;
  
  template <>
  const uint64_t dSFMT<44497>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<44497>::IDStr=
    "dSFMT2-44497:304-19:FF6DFFFFFFFEF-7FFDDDEEFFF6F";
    
  template <>
  dSFMT<44497>::dSFMT() {}
  
  template <>
  dSFMT<44497>::dSFMT(const uint32_t& seed) { Init(seed); }

  template <>
  const uint32_t dSFMT<86243>::Pos1=231;
  
  template <>
  const uint32_t dSFMT<86243>::SL1=13;
  
  template <>
  const uint64_t dSFMT<86243>::Msk1=0x000FFEDFF6FFFFDFULL;
  
  template <>
  const uint64_t dSFMT<86243>::Msk2=0x000FFFF7FDFFFF7EULL;
  
  template <>
  const uint32_t dSFMT<86243>::Msk32_1=0x000FFEDFU;
  
  template <>
  const uint32_t dSFMT<86243>::Msk32_2=0xF6FFFFDFU;
  
  template <>
  const uint32_t dSFMT<86243>::Msk32_3=0x000FFFF7U;
  
  template <>
  const uint32_t dSFMT<86243>::Msk32_4=0xFDFFFF7EU;
  
  template <>
  const uint64_t dSFMT<86243>::Fix1=0x1D553E776B975E68ULL;
  
  template <>
  const uint64_t dSFMT<86243>::Fix2=0x648FAADF1416BF91ULL;
  
  template <>
  const uint64_t dSFMT<86243>::Pcv1=0x5F2CD03E2758A373ULL;
  
  template <>
  const uint64_t dSFMT<86243>::Pcv2=0xC0B7EB8410000001ULL;
  
  template <>
  const char* dSFMT<86243>::IDStr=
    "dSFMT2-86243:231-13:FFEDFF6FFFFDF-FFFF7FDFFFF7E";
    
  template <>
  dSFMT<86243>::dSFMT() {}
  
  template <>
  dSFMT<86243>::dSFMT(const uint32_t& seed) { Init(seed); }

  template <>
  const uint32_t dSFMT<132049>::Pos1=371;
  
  template <>
  const uint32_t dSFMT<132049>::SL1=23;
  
  template <>
  const uint64_t dSFMT<132049>::Msk1=0x000FB9F4EFF4BF77ULL;
  
  template <>
  const uint64_t dSFMT<132049>::Msk2=0x000FFFFFBFEFFF37ULL;
  
  template <>
  const uint32_t dSFMT<132049>::Msk32_1=0x000FB9F4U;
  
  template <>
  const uint32_t dSFMT<132049>::Msk32_2=0xEFF4BF77U;
  
  template <>
  const uint32_t dSFMT<132049>::Msk32_3=0x000FFFFFU;
  
  template <>
  const uint32_t dSFMT<132049>::Msk32_4=0xBFEFFF37U;
  
  template <>
  const uint64_t dSFMT<132049>::Fix1=0x4CE24C0E4E234F3BULL;
  
  template <>
  const uint64_t dSFMT<132049>::Fix2=0x62612409B5665C2DULL;
  
  template <>
  const uint64_t dSFMT<132049>::Pcv1=0x181232889145D000ULL;
  
  template <>
  const uint64_t dSFMT<132049>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<132049>::IDStr=
    "dSFMT2-132049:371-23:FB9F4EFF4BF77-FFFFFBFEFFF37";
    
  template <>
  dSFMT<132049>::dSFMT() {}
  
  template <>
  dSFMT<132049>::dSFMT(const uint32_t& seed) { Init(seed); }

  template <>
  const uint32_t dSFMT<216091>::Pos1=1890;
  
  template <>
  const uint32_t dSFMT<216091>::SL1=23;
  
  template <>
  const uint64_t dSFMT<216091>::Msk1=0x000BF7DF7FEFCFFFULL;
  
  template <>
  const uint64_t dSFMT<216091>::Msk2=0x000E7FFFFEF737FFULL;
  
  template <>
  const uint32_t dSFMT<216091>::Msk32_1=0x000BF7DFU;
  
  template <>
  const uint32_t dSFMT<216091>::Msk32_2=0x7FEFCFFFU;
  
  template <>
  const uint32_t dSFMT<216091>::Msk32_3=0x000E7FFFU;
  
  template <>
  const uint32_t dSFMT<216091>::Msk32_4=0xFEF737FFU;
  
  template <>
  const uint64_t dSFMT<216091>::Fix1=0xD7F95A04764C27D7ULL;
  
  template <>
  const uint64_t dSFMT<216091>::Fix2=0x6A483861810BEBC2ULL;
  
  template <>
  const uint64_t dSFMT<216091>::Pcv1=0x3AF0A8F3D5600000ULL;
  
  template <>
  const uint64_t dSFMT<216091>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<216091>::IDStr=
    "dSFMT2-216091:1890-23:BF7DF7FEFCFFF-E7FFFFEF737FF";
    
  template <>
  dSFMT<216091>::dSFMT() {}
  
  template <>
  dSFMT<216091>::dSFMT(const uint32_t& seed) { Init(seed); }

  template <uint BoundaryType>
  class Convertor { public: Convertor() { assert(false); } };
  
  template <>
  class Convertor<Close1_Open2> {
    public:
      template <uint LoopFac>
      void operator()(typename dSFMT<LoopFac>::W128_T& w) {}
  };
  
#ifdef HAVE_SSE2

  template <>
  class Convertor<Close0_Open1> {
    public:
      template <uint LoopFac>
      void operator()(typename dSFMT<LoopFac>::W128_T& w) {
        w.sd=_mm_add_pd(w.sd,dSFMT<LoopFac>::SSE2_DoubleMOne);
      }
  };
  
  template <>
  class Convertor<Open0_Close1> {
    public:
      template <uint LoopFac>
      void operator()(typename dSFMT<LoopFac>::W128_T& w) {
        w.sd=_mm_sub_pd(dSFMT<LoopFac>::SSE2_DoubleTwo,w.sd);
      }
  };

  template <>
  class Convertor<Open0_Open1> {
    public:
      template <uint LoopFac>
      void operator()(typename dSFMT<LoopFac>::W128_T& w) {
        w.si=_mm_or_si128(w.si,dSFMT<LoopFac>::SSE2_IntOne);
        w.sd=_mm_add_pd(w.sd,dSFMT<LoopFac>::SSE2_DoubleMOne);
      }
  };

#else

  template <>
  class Convertor<Close0_Open1> {
    public:
      template <uint LoopFac>
      void operator()(typename dSFMT<LoopFac>::W128_T& w) {
        w.d[0]-=1.0;
        w.d[1]-=1.0;
      }
  };
  
  template <>
  class Convertor<Open0_Close1> {
    template <uint LoopFac>
    void operator()(typename dSFMT<LoopFac>::W128_T& w) {
      w.d[0]=2.0-w.d[0];
      w.d[1]=2.0-w.d[1];
    }
  };

  template <>
  class Convertor<Open0_Open1> {
    public:
      template <uint LoopFac>
      void operator()(typename dSFMT<LoopFac>::W128_T& w) {
        w.u[0]|=1;
        w.u[1]|=1;
        w.d[0]-=1.0;
        w.d[1]-=1.0;
      }
  };

#endif

}

#endif

