
#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "unique-parameter-128bit.h"
#include "vector.h"
#include <cstring>

namespace std {

#ifdef HAVE_SSE2
  __m128i   dSFMT_SSE2_ParamMask;
  __m128i   dSFMT_SSE2_IntOne;
  __m128d   dSFMT_SSE2_DoubleTwo;
  __m128d   dSFMT_SSE2_DoubleMOne;  
#endif

  void ConvertClose1Open2(UniqueParameter128b&) {}
#ifdef HAVE_SSE2
  void ConvertClose0Open1(UniqueParameter128b& w) {
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd((double*)(&dSFMT_SSE2_DoubleMOne));
    _mm_storeu_pd(w.d,_mm_add_pd(wd,cd));
  }
  void ConvertOpen0Close1(UniqueParameter128b& w) {
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd((double*)(&dSFMT_SSE2_DoubleTwo));
    _mm_storeu_pd(w.d,_mm_sub_pd(cd,wd));
  }
  void ConvertOpen0Open1(UniqueParameter128b& w) {
    __m128i wi,ci;
    wi=_mm_loadu_si128(&(w.si));
    ci=_mm_loadu_si128(&dSFMT_SSE2_IntOne);
    _mm_storeu_si128(&(w.si),_mm_or_si128(wi,ci));
    __m128d wd,cd;
    wd=_mm_loadu_pd(w.d);
    cd=_mm_loadu_pd((double*)(&dSFMT_SSE2_DoubleMOne));
    _mm_storeu_pd(w.d,_mm_add_pd(wd,cd));
  }
#else
  void ConvertClose0Open1(UniqueParameter128b& w) { w.d[0]-=1.0; w.d[1]-=1.0; }
  void ConvertOpen0Close1(UniqueParameter128b& w) {
    w.d[0]=2.0-w.d[0];
    w.d[1]=2.0-w.d[1];
  }
  void ConvertOpen0Open1(UniqueParameter128b& w) {
    w.ull[0]|=1;
    w.ull[1]|=1;
    w.d[0]-=1.0;
    w.d[1]-=1.0;
  }
#endif

  template <unsigned int LoopFac=19937>
  struct dSFMT {

    static const unsigned int MExp;
    static const unsigned int N;
    static const unsigned int NStatus;
    static const unsigned int NStatusU32;
    static const unsigned int NStatusByte;
    static const unsigned int Lag;
    static const unsigned int Mid;
    static const unsigned int LagMid;
    static const unsigned int N32;
    static const unsigned int N64;
    static const unsigned long long int LowMask;
    static const unsigned long long int HighConst;
    static const unsigned int SR;
#ifdef HAVE_SSE2
    static const unsigned int SSE2_Shuff;
#endif
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const unsigned long long int Msk1;
    static const unsigned long long int Msk2;
    static const unsigned int Msk32_1;
    static const unsigned int Msk32_2;
    static const unsigned int Msk32_3;
    static const unsigned int Msk32_4;
    static const unsigned long long int Fix1;
    static const unsigned long long int Fix2;
    static const unsigned long long int Pcv1;
    static const unsigned long long int Pcv2;
    static const unsigned long long int pcv[2];
    static const unsigned int IsFacAvailable;

    UniqueParameter128b *status;
    unsigned int *idx;
    UniqueParameter128b *output;
    unsigned int state;

    typedef dSFMT<LoopFac>    Type;
    typedef void (*ConvertFuncType)(UniqueParameter128b&);

    dSFMT() : status(NULL), idx(NULL), output(NULL), state(Unused) {
      assert(IsFacAvailable!=0);
    }
    dSFMT(const Type&) { myError("Cannot create from dSFMT generator"); }
    Type& operator=(const Type& dg) { assign(*this,dg); return *this; }
    ~dSFMT() { release(*this); }

    void Init(const unsigned int seed) { init(*this,seed); }
    void Init(const unsigned int* key, const unsigned int len,
              const unsigned int off=uZero, const unsigned int step=uOne) {
      init(*this,key,len,off,step);
    }
    void Init(const Vector<unsigned int>& key) { init(*this,key); }

    const unsigned int& UInt32() {
      unsigned long long int *pSFMT=&(status[0].ull[0]);
      if(*idx>=N64) { GenRandAll(); *idx=0; }
      output->u[0]=pSFMT[(*idx)++]&0xFFFFFFFFUL;
      return output->u[0];
    }
    const double& DoubleClose1Open2() {
      double* pSFMT=&(status[0].d[0]);
      if(*idx>=N64) { GenRandAll(); *idx=0; }
      output->d[0]=pSFMT[(*idx)++];
      return output->d[0];
    }
    const double& DoubleClose0Open1() {
      output->d[1]=DoubleClose1Open2()-1.0;
      return output->d[1];
    }
    const double& DoubleOpen0Close1() {
      output->d[1]=2.0-DoubleClose1Open2();
      return output->d[1];
    }
    const double& DoubleOpen0Open1() {
      double *pSFMT=&(status[0].d[0]);
      if(*idx>=N64) { GenRandAll(); *idx=0; }
      output->d[0]=pSFMT[(*idx)++];
      output->ull[0]|=1;
      output->d[1]=output->d[0]-1.0;
      return output->d[1];
    }

    void fillarrayClose1Open2(double* array, const unsigned int sz) {
      FillArrayImpl(array,sz,ConvertClose1Open2);
    }

    void fillarrayClose0Open1(double* array, const unsigned int sz) {
      FillArrayImpl(array,sz,ConvertClose0Open1);
    }

    void fillarrayOpen0Close1(double* array, const unsigned int sz) {
      FillArrayImpl(array,sz,ConvertOpen0Close1);
    }

    void fillarrayOpen0Open1(double* array, const unsigned int sz) {
      FillArrayImpl(array,sz,ConvertOpen0Open1);
    }

    void fillarrayClose1Open2(Vector<double>& v) {
      fillarrayClose1Open2(v(),v.size);
    }

    void fillarrayClose0Open1(Vector<double>& v) {
      fillarrayClose0Open1(v(),v.size);
    }

    void fillarrayOpen0Close1(Vector<double>& v) {
      fillarrayOpen0Close1(v(),v.size);
    }

    void fillarrayOpen0Open1(Vector<double>& v) {
      fillarrayOpen0Open1(v(),v.size);
    }

#ifdef HAVE_SSE2
    void InitConst() {
      static bool first=true;
      if(!first)  return;
      // Endian?
      dSFMT_SSE2_ParamMask=_mm_set_epi32(Msk32_3,Msk32_4,Msk32_1,Msk32_2);
      dSFMT_SSE2_IntOne=_mm_set_epi32(0,1,0,1);
      dSFMT_SSE2_DoubleTwo=_mm_set_pd(2.0,2.0);
      dSFMT_SSE2_DoubleMOne=_mm_set_pd(-1.0,-1.0);
      first=false;
    }
    void DoRecursion(const UniqueParameter128b& a,
                     const UniqueParameter128b& b,
                     UniqueParameter128b& r, UniqueParameter128b& u) {
      __m128i v,w,x,y,z,mask,bs;
      mask=_mm_loadu_si128(&dSFMT_SSE2_ParamMask);
      x=_mm_loadu_si128(&(a.si));
      bs=_mm_loadu_si128(&(b.si));
      z=_mm_slli_epi64(x,SL1);
      y=_mm_shuffle_epi32(u.si,SSE2_Shuff);
      z=_mm_xor_si128(z,bs);
      y=_mm_xor_si128(y,z);
      v=_mm_srli_epi64(y,SR);
      w=_mm_and_si128(y,dSFMT_SSE2_ParamMask);
      v=_mm_xor_si128(v,x);
      v=_mm_xor_si128(v,w);
      _mm_storeu_si128(&(r.si),v);
      _mm_storeu_si128(&(u.si),y);
    }
#else
    void DoRecursion(const UniqueParameter128b& a,
                     const UniqueParameter128b& b,
                     UniqueParameter128b& r, UniqueParameter128b& u) {
      unsigned long long int t0,t1,L0,L1;
      t0=a.ull[0];
      t1=a.ull[1];
      L0=u.ull[0];
      L1=u.ull[1];
      u.ull[0]=(t0<<SL1)^(L1>>32)^(L1<<32)^b.ull[0];
      u.ull[1]=(t1<<SL1)^(L0>>32)^(L0<<32)^b.ull[1];
      r.ull[0]=(u.ull[0]>>SR)^(u.ull[0]&Msk1)^t0;
      r.ull[1]=(u.ull[1]>>SR)^(u.ull[1]&Msk1)^t1;
    }
#endif

    void GenRandArrayImpl(UniqueParameter128b* array, const unsigned int size,
                          const ConvertFuncType& cvfunc) {
      unsigned int i,j;
      UniqueParameter128b lung;
      lung=status[N];
      DoRecursion(status[0],status[Pos1],array[0],lung);
      for(i=0;i<N-Pos1;++i)
        DoRecursion(status[i],status[i+Pos1],array[i],lung);
      for(;i<N;++i)
        DoRecursion(status[i],array[i+Pos1-N],array[i],lung);
      for(;i+N<size;++i) {
        DoRecursion(array[i-N],array[i+Pos1-N],array[i],lung);
        cvfunc(array[i-N]);
      }
      for(j=0;j+size<N+N;++j) status[j]=array[j+size-N];
      for(;i<size;++i,++j) {
        DoRecursion(array[i-N],array[i+Pos1-N],array[i],lung);
        status[j]=array[i];
        cvfunc(array[i-N]);
      }
      for(i=size-N;i<size;++i)  cvfunc(array[i]);
      status[N]=lung;
    }

    unsigned int initfunc1(const unsigned int x) {
      return (x^(x>>27))*1664525UL;
    }

    unsigned int initfunc2(const unsigned int x) {
      return (x^(x>>27))*1566083941UL;
    }

    void initmask() {
      unsigned long long int *pSFMT;
      pSFMT=&(status[0].ull[0]);
      for(unsigned int i=0;i<N+N;++i) pSFMT[i]=(pSFMT[i]&LowMask)|HighConst;
    }

    void PeriodCertification() {
      unsigned long long int tmp[2], inner;
      tmp[0]=status[N].ull[0]^Fix1;
      tmp[1]=status[N].ull[1]^Fix2;
      inner=tmp[0]&pcv[0];
      inner^=tmp[1]&pcv[1];
      for(unsigned int i=32;i>0;i>>=1)   inner^=inner>>i;
      inner&=1;
      if(inner==1)  return;
      status[N].ull[1]^=1;
      return;
    }

    void GenRandAll() {
      unsigned int i;
      UniqueParameter128b lung;
      DoRecursion(status[0],status[Pos1],status[0],lung);
      for(i=1;i<N-Pos1;++i)
        DoRecursion(status[i],status[i+Pos1],status[i],lung);
      for(;i<N;++i) DoRecursion(status[i],status[i+Pos1-N],status[i],lung);
      status[N]=lung;
    }

    void FillArrayImpl(double *array, unsigned int size,
                       const ConvertFuncType& cvfunc) {
      assert((size&1)==0);
      assert(size>=N64);
      GenRandArrayImpl(reinterpret_cast<UniqueParameter128b*>(array),size>>1,
                       cvfunc);
    }

  };

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::MExp=LoopFac;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N=((dSFMT<LoopFac>::MExp-128)/104+1);
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatus=dSFMT<LoopFac>::N+1;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatusU32=dSFMT<LoopFac>::NStatus*4;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatusByte=dSFMT<LoopFac>::NStatus*16;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Lag=
    (dSFMT<LoopFac>::NStatusU32>=623?11:
    (dSFMT<LoopFac>::NStatusU32>68?7:
    (dSFMT<LoopFac>::NStatusU32>39?5:3)));
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Mid=
    (dSFMT<LoopFac>::NStatusU32-dSFMT<LoopFac>::Lag)/2;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::LagMid=
    dSFMT<LoopFac>::Lag+dSFMT<LoopFac>::Mid;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N32=dSFMT<LoopFac>::N*4;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N64=dSFMT<LoopFac>::N*2;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::LowMask=0x000FFFFFFFFFFFFFULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::HighConst=0x3FF0000000000000ULL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SR=12;
#ifdef HAVE_SSE2
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SSE2_Shuff=0x1BU;
#endif 
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_1=
    (dSFMT<LoopFac>::Msk1>>32)&0xFFFFFFFFUL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_2=dSFMT<LoopFac>::Msk1&0xFFFFFFFFUL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_3=
    (dSFMT<LoopFac>::Msk2>>32)&0xFFFFFFFFUL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_4=dSFMT<LoopFac>::Msk1&0xFFFFFFFFUL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::pcv[2]={dSFMT<LoopFac>::Pcv1,
                                                       dSFMT<LoopFac>::Pcv2};

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Pos1=0U;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SL1=0U;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Msk1=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Msk2=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Fix1=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Fix2=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Pcv1=0ULL;
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Pcv2=0ULL;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::IsFacAvailable=0;

  template <> const unsigned int dSFMT<521>::Pos1=3;
  template <> const unsigned int dSFMT<521>::SL1=25;
  template <>
  const unsigned long long int dSFMT<521>::Msk1=0x000FBFEFFF77EFFFULL;
  template <>
  const unsigned long long int dSFMT<521>::Msk2=0x000FFEEBFBDFBFDFULL;
  template <>
  const unsigned long long int dSFMT<521>::Fix1=0xCFB393D661638469ULL;
  template <>
  const unsigned long long int dSFMT<521>::Fix2=0xC166867883AE2ADBULL;
  template <>
  const unsigned long long int dSFMT<521>::Pcv1=0xCCAA588000000000ULL;
  template <>
  const unsigned long long int dSFMT<521>::Pcv2=0x0000000000000001ULL;
  template <> const unsigned int dSFMT<521>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<1279>::Pos1=9;
  template <> const unsigned int dSFMT<1279>::SL1=19;
  template <>
  const unsigned long long int dSFMT<1279>::Msk1=0x000EFFF7FFDDFFEEULL;
  template <>
  const unsigned long long int dSFMT<1279>::Msk2=0x000FBFFFFFF77FFFULL;
  template <>
  const unsigned long long int dSFMT<1279>::Fix1=0xB66627623D1A31BEULL;
  template <>
  const unsigned long long int dSFMT<1279>::Fix2=0x04B6C51147B6109BULL;
  template <>
  const unsigned long long int dSFMT<1279>::Pcv1=0x7049F2DA382A6AEBULL;
  template <>
  const unsigned long long int dSFMT<1279>::Pcv2=0xDE4CA84A40000001ULL;
  template <> const unsigned int dSFMT<1279>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<2203>::Pos1=7;
  template <> const unsigned int dSFMT<2203>::SL1=19;
  template <>
  const unsigned long long int dSFMT<2203>::Msk1=0x000FDFFFF5EDBFFFULL;
  template <>
  const unsigned long long int dSFMT<2203>::Msk2=0x000F77FFFFFFFBFEULL;
  template <>
  const unsigned long long int dSFMT<2203>::Fix1=0xB14E907A39338485ULL;
  template <>
  const unsigned long long int dSFMT<2203>::Fix2=0xF98F0735C637EF90ULL;
  template <>
  const unsigned long long int dSFMT<2203>::Pcv1=0x8000000000000000ULL;
  template <>
  const unsigned long long int dSFMT<2203>::Pcv2=0x0000000000000001ULL;
  template <> const unsigned int dSFMT<2203>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<4253>::Pos1=19;
  template <> const unsigned int dSFMT<4253>::SL1=19;
  template <>
  const unsigned long long int dSFMT<4253>::Msk1=0x0007B7FFFEF5FEFFULL;
  template <>
  const unsigned long long int dSFMT<4253>::Msk2=0x000FFDFFEFFEFBFCULL;
  template <>
  const unsigned long long int dSFMT<4253>::Fix1=0x80901B5FD7A11C65ULL;
  template <>
  const unsigned long long int dSFMT<4253>::Fix2=0x5A63FF0E7CB0BA74ULL;
  template <>
  const unsigned long long int dSFMT<4253>::Pcv1=0x1AD277BE12000000ULL;
  template <>
  const unsigned long long int dSFMT<4253>::Pcv2=0x0000000000000001ULL;
  template <> const unsigned int dSFMT<4253>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<11213>::Pos1=37;
  template <> const unsigned int dSFMT<11213>::SL1=19;
  template <>
  const unsigned long long int dSFMT<11213>::Msk1=0x000FFFFFFDF7FFFDULL;
  template <>
  const unsigned long long int dSFMT<11213>::Msk2=0x000DFFFFFFF6BFFFULL;
  template <>
  const unsigned long long int dSFMT<11213>::Fix1=0xD0EF7B7C75B06793ULL;
  template <>
  const unsigned long long int dSFMT<11213>::Fix2=0x9C50FF4CAAE0A641ULL;
  template <>
  const unsigned long long int dSFMT<11213>::Pcv1=0x8234C51207C80000ULL;
  template <>
  const unsigned long long int dSFMT<11213>::Pcv2=0x0000000000000001ULL;
  template <> const unsigned int dSFMT<11213>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<19937>::Pos1=117;
  template <> const unsigned int dSFMT<19937>::SL1=19;
  template <>
  const unsigned long long int dSFMT<19937>::Msk1=0x000FFAFFFFFFFB3FULL;
  template <>
  const unsigned long long int dSFMT<19937>::Msk2=0x000FFDFFFC90FFFDULL;
  template <>
  const unsigned long long int dSFMT<19937>::Fix1=0x90014964B32F4329ULL;
  template <>
  const unsigned long long int dSFMT<19937>::Fix2=0x3B8D12AC548A7C7AULL;
  template <>
  const unsigned long long int dSFMT<19937>::Pcv1=0x3D84E1AC0DC82880ULL;
  template <>
  const unsigned long long int dSFMT<19937>::Pcv2=0x0000000000000001ULL;
  template <> const unsigned int dSFMT<19937>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<44497>::Pos1=304;
  template <> const unsigned int dSFMT<44497>::SL1=19;
  template <>
  const unsigned long long int dSFMT<44497>::Msk1=0x000FF6DFFFFFFFEFULL;
  template <>
  const unsigned long long int dSFMT<44497>::Msk2=0x0007FFDDDEEFFF6FULL;
  template <>
  const unsigned long long int dSFMT<44497>::Fix1=0x75D910F235F6E10EULL;
  template <>
  const unsigned long long int dSFMT<44497>::Fix2=0x7B32158AEDC8E969ULL;
  template <>
  const unsigned long long int dSFMT<44497>::Pcv1=0x4C3356B2A0000000ULL;
  template <>
  const unsigned long long int dSFMT<44497>::Pcv2=0x0000000000000001ULL;
  template <> const unsigned int dSFMT<44497>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<86243>::Pos1=231;
  template <> const unsigned int dSFMT<86243>::SL1=13;
  template <>
  const unsigned long long int dSFMT<86243>::Msk1=0x000FFEDFF6FFFFDFULL;
  template <>
  const unsigned long long int dSFMT<86243>::Msk2=0x000FFFF7FDFFFF7EULL;
  template <>
  const unsigned long long int dSFMT<86243>::Fix1=0x1D553E776B975E68ULL;
  template <>
  const unsigned long long int dSFMT<86243>::Fix2=0x648FAADF1416BF91ULL;
  template <>
  const unsigned long long int dSFMT<86243>::Pcv1=0x5F2CD03E2758A373ULL;
  template <>
  const unsigned long long int dSFMT<86243>::Pcv2=0xC0B7EB8410000001ULL;
  template <> const unsigned int dSFMT<86243>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<132049>::Pos1=371;
  template <> const unsigned int dSFMT<132049>::SL1=23;
  template <>
  const unsigned long long int dSFMT<132049>::Msk1=0x000FB9F4EFF4BF77ULL;
  template <>
  const unsigned long long int dSFMT<132049>::Msk2=0x000FFFFFBFEFFF37ULL;
  template <>
  const unsigned long long int dSFMT<132049>::Fix1=0x4CE24C0E4E234F3BULL;
  template <>
  const unsigned long long int dSFMT<132049>::Fix2=0x62612409B5665C2DULL;
  template <>
  const unsigned long long int dSFMT<132049>::Pcv1=0x181232889145D000ULL;
  template <>
  const unsigned long long int dSFMT<132049>::Pcv2=0x0000000000000001ULL;
  template <> const unsigned int dSFMT<132049>::IsFacAvailable=1;

  template <> const unsigned int dSFMT<216091>::Pos1=1890;
  template <> const unsigned int dSFMT<216091>::SL1=23;
  template <>
  const unsigned long long int dSFMT<216091>::Msk1=0x000BF7DF7FEFCFFFULL;
  template <>
  const unsigned long long int dSFMT<216091>::Msk2=0x000E7FFFFEF737FFULL;
  template <>
  const unsigned long long int dSFMT<216091>::Fix1=0xD7F95A04764C27D7ULL;
  template <>
  const unsigned long long int dSFMT<216091>::Fix2=0x6A483861810BEBC2ULL;
  template <>
  const unsigned long long int dSFMT<216091>::Pcv1=0x3AF0A8F3D5600000ULL;
  template <>
  const unsigned long long int dSFMT<216091>::Pcv2=0x0000000000000001ULL;
  template <> const unsigned int dSFMT<216091>::IsFacAvailable=1;

  template <unsigned int LoopFac>
  bool IsAvailable(const dSFMT<LoopFac>& dg) { return IsAvailable(dg.status); }

  template <unsigned int LoopFac>
  bool IsRandomGenerator(const dSFMT<LoopFac>&) { return true; }

  template <unsigned int LoopFac>
  void assign(dSFMT<LoopFac>& dest, const dSFMT<LoopFac>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.status.src.status,dSFMT<LoopFac>::NStatus);
    *dest.idx=*src.idx;
  }

  template <unsigned int LoopFac>
  void release(dSFMT<LoopFac>& dg) {
    if(dg.state==Allocated) {
      safe_delete_array(dg.status);
      safe_delete(dg.idx);
      safe_delete(dg.output);
    } else {
      dg.status=NULL;
      dg.idx=NULL;
      dg.output=NULL;
    }
    dg.state=Unused;
  }

  template <unsigned int LoopFac>
  void allocate(dSFMT<LoopFac>& dg) {
    release(dg);
    dg.status=new UniqueParameter128b[dSFMT<LoopFac>::NStatus];
    dg.idx=new unsigned int;
    dg.output=new UniqueParameter128b;
    dg.state=Allocated;
    dg.Init(5489UL);
  }

  template <unsigned int LoopFac>
  void refer(dSFMT<LoopFac>& dest, const dSFMT<LoopFac>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.status=src.status;
    dest.idx=src.idx;
    dest.output=src.output;
    dest.state=Reference;
  }

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg, const unsigned int seed) {
    unsigned int *pSFMT;
    pSFMT=&dg.status[0].u[0];
    pSFMT[0]=seed;
    unsigned int rmt;
    rmt=pSFMT[0];
    for(unsigned int i=1;i<dSFMT<LoopFac>::NStatusU32;++i) {
      rmt=1812433253UL*(rmt^(rmt>>30))+i;
      pSFMT[i]=rmt;
    }
    dg.initmask();
    dg.PeriodCertification();
    *(dg.idx)=dSFMT<LoopFac>::N64;
#ifdef HAVE_SSE2
    dg.InitConst();
#endif
  }

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg,
            const unsigned int* key, const unsigned int len,
            const unsigned int off=uZero, const unsigned int step=uOne) {
    unsigned int i,j,g,count,tmid,r, *pSFMT;
    pSFMT=&dg.status[0].u[0];
    memset(dg.status,0x8B,dSFMT<LoopFac>::NStatusByte);
    count=(len+1>dSFMT<LoopFac>::NStatusU32?len+1:dSFMT<LoopFac>::NStatusU32);
    tmid=dSFMT<LoopFac>::Mid%dSFMT<LoopFac>::NStatusU32;
    r=dg.initfunc1(pSFMT[0]^pSFMT[tmid]^pSFMT[dSFMT<LoopFac>::NStatusU32-1]);
    pSFMT[tmid]+=r;
    r+=len;
    pSFMT[dSFMT<LoopFac>::LagMid%dSFMT<LoopFac>::NStatusU32]+=r;
    pSFMT[0]=r;
    --count;
    for(i=0,j=0,g=off;(j<count)&&(j<len);++j,g+=step) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=dg.initfunc1(pSFMT[i]^pSFMT[tmid]
          ^pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]+=r;
      r+=key[g]+i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]+=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    for(;j<count;++j) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=dg.initfunc1(pSFMT[i]^pSFMT[tmid]
          ^pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]+=r;
      r+=i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]+=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    for(j=0;j<dSFMT<LoopFac>::NStatusU32;++j) {
      tmid=(i+dSFMT<LoopFac>::Mid)%dSFMT<LoopFac>::NStatusU32;
      r=dg.initfunc2(pSFMT[i]+pSFMT[tmid]
          +pSFMT[(i+dSFMT<LoopFac>::NStatusU32-1)%dSFMT<LoopFac>::NStatusU32]);
      pSFMT[tmid]^=r;
      r-=i;
      pSFMT[(i+dSFMT<LoopFac>::LagMid)%dSFMT<LoopFac>::NStatusU32]^=r;
      pSFMT[i]=r;
      i=(i+1)%dSFMT<LoopFac>::NStatusU32;
    }
    dg.initmask();
    dg.PeriodCertification();
    *(dg.idx)=dSFMT<LoopFac>::N64;
#ifdef HAVE_SSE2
    dg.InitConst();
#endif
  }

  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>& dg, const Vector<unsigned int>& key) {
    init(dg,key(),key.size);
  }

  template <unsigned int LoopFac>
  const double& rand(dSFMT<LoopFac>& dg) { return dg.DoubleClose0Open1(); }

  template <typename T>
  const T& rand(dSFMT<521>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<1279>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<2203>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<4253>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<11213>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<19937>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<44497>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<86243>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<132049>& dg) { myError("Default Form is prohibited"); }
  template <typename T>
  const T& rand(dSFMT<216091>& dg) { myError("Default Form is prohibited"); }

  template <>
  const double& rand<double>(dSFMT<521>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<1279>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<2203>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<4253>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<11213>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<19937>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<44497>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<86243>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<132049>& dg) { return rand(dg); }
  template <>
  const double& rand<double>(dSFMT<216091>& dg) { return rand(dg); }

  template <>
  const unsigned int& rand<unsigned int>(dSFMT<521>& dg){ return dg.UInt32(); }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<1279>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<2203>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<4253>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<11213>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<19937>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<44497>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<86243>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<132049>& dg) {
    return dg.UInt32();
  }
  template <>
  const unsigned int& rand<unsigned int>(dSFMT<216091>& dg) {
    return dg.UInt32();
  }

  template <unsigned int LoopFac>
  void fillarray(dSFMT<LoopFac>& dg, double* array, const unsigned int size) {
    dg.fillarrayClose0Open1(array,size);
  }

  template <unsigned int LoopFac>
  void fillarray(dSFMT<LoopFac>& dg, Vector<double>& v) {
    dg.fillarrayClose0Open1(v);
  }

  template <unsigned int LoopFac>
  ostream& operator<<(ostream& os, const dSFMT<LoopFac>& dg) {
    assert(IsAvailable(dg));
    os<<LoopFac<<"\t";
    for(unsigned int i=0;i<dSFMT<LoopFac>::NStatus;++i) os<<dg.status[i]<<"\t";
    os<<*(dg.idx);
    return os;
  }

  template <unsigned int LoopFac>
  istream& operator>>(istream& is, dSFMT<LoopFac>& dg) {
    assert(IsAvailable(dg));
    unsigned int expLoopFac;
    is>>expLoopFac;
    if(expLoopFac!=LoopFac) myError("Imcompatiable data for dSFMT generator");
    for(unsigned int i=0;i<dSFMT<LoopFac>::NStatus;++i) is>>dg.status[i];
    is>>*(dg.idx);
    return is;
  }

}

#endif
