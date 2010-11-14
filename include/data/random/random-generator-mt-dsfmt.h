
#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter-128bit.h"

namespace std {

#ifdef HAVE_SSE2
  __m128i   dSFMT_SSE2_ParamMask;
  __m128i   dSFMT_SSE2_IntOne;
  __m128d   dSFMT_SSE2_DoubleTwo;
  __m128d   dSFMT_SSE2_DoubleMOne;
#endif

  template <unsigned int LoopFac=19937>
  struct dSFMT : public Vector<UniqueParameter128b> {
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

    unsigned int *idx;
    UniqueParameter128b output;

    typedef dSFMT<LoopFac>    Type;
    typedef Vector<UniqueParameter128b> ParentType;

    dSFMT() : ParentType(), idx(NULL), output() {}
    dSFMT(const Type& G) { myError("Cannot create dSFMT"); }
    Type& operator=(const Type& G) {
      myError("Cannot copy dSFMT");
      return *this;
    }
    ~dSFMT() { release(*this); }

    unsigned int initfunc1(const unsigned int x) {
      return (x^(x>>27))*1664525UL;
    }
    unsigned int initfunc2(const unsigned int x) {
      return (x^(x>>27))*1566083941UL;
    }
    void initMask() {
      unsigned long long int *pSFMT;
      pSFMT=&(this->data->ull[0]);
      for(unsigned int i=0;i<N+N;++i) pSFMT[i]=(pSFMT[i]&LowMask)|HighConst;
    }

#ifdef HAVE_SSE2
    void initConst() {
      static bool first=true;
      if(!first)  return;
      dSFMT_SSE2_ParamMask=_mm_set_epi32(Msk32_3,Msk32_4,Msk32_1,Msk32_2);
      dSFMT_SSE2_IntOne=_mm_set_epi32(0,1,0,1);
      dSFMT_SSE2_DoubleTwo=_mm_set_pd(2.0,2.0);
      dSFMT_SSE2_DoubleMOne=_mm_set_pd(-1.0,-1.0);
      first=false;
    }
    void DoRecursion(const UniqueParameter128b& a,const UniqueParameter128b& b,
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
    void DoRecursion(const UniqueParameter128b& a,const UniqueParameter128b& b,
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

    void PeriodCertification() {
      unsigned long long int tmp0,tmp1,inner;
      tmp0=this->operator[](N).ull[0]^Fix1;
      tmp1=this->operator[](N).ull[1]^Fix1;
      inner=tmp0&pcv[0];
      inner^=tmp1&pcv[1];
      for(unsigned int i=32;i>0;i>>=1)  inner^=inner>>i;
      inner&=1;
      if(inner==1)  return;
      this->operator[](N).ull[1]^=1;
      return;
    }
  };

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::MExp=LoopFac;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N=(dSFMT<LoopFac>::MExp-128)/104+1;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatus=dSFMT<LoopFac>::N+1;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatusU32=dSFMT<LoopFac>::NStatus*4;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::NStatusByte=dSFMT<LoopFac>::NStatus*16;
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Lag=(dSFMT<LoopFac>::NStatusU32>623?11:
                                          dSFMT<LoopFac>::NStatusU32>68?7:
                                          dSFMT<LoopFac>::NStatusU32>39?5:3);
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
  const unsigned int dSFMT<LoopFac>::Msk32_4=dSFMT<LoopFac>::Msk2&0xFFFFFFFFUL;
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

  template <unsigned int LoopFac>
  bool IsAvailable(const dSFMT<LoopFac>& G) {
    return IsAvailable(static_cast<const Vector<UniqueParameter128b>&>(G));
  }
  template <unsigned int LoopFac>
  bool IsRandomGenerator(const dSFMT<LoopFac>& G) { return true; }

  template <unsigned int LoopFac>
  void release(dSFMT<LoopFac>& G) {
    if(G.state==Allocated)  safe_delete(G.idx);
    else G.idx=NULL;
    release(static_cast<Vector<UniqueParameter128b>&>(G));
    copy(G.output,0.L);
  }
  template <unsigned int LoopFac>
  void copy(dSFMT<LoopFac>& G, const dSFMT<LoopFac>& cG) {
    assert(IsAvailable(G));
    assert(IsAvailable(cG));
    copy(static_cast<Vector<UniqueParameter128b>&>(G),
         static_cast<const Vector<UniqueParameter128b>&>(cG));
    copy(*(G.idx),*(cG.idx));
  }
  template <unsigned int LoopFac>
  void init(dSFMT<LoopFac>&,const unsigned int);
  template <unsigned int LoopFac>
  void allocate(dSFMT<LoopFac>& G) {
    release(G);
    allocate(static_cast<Vector<UniqueParameter128b>&>(G),
             dSFMT<LoopFac>::NStatus);
    G.idx=new unsigned int;
    init(G,5489UL);
  }
  template <unsigned int LoopFac>
  void refer(dSFMT<LoopFac>& G, const dSFMT<LoopFac>& rG) {
    assert(IsAvailable(rG));
    release(G);
    refer(static_cast<Vector<UniqueParameter128b>&>(G),
          static_cast<const Vector<UniqueParameter128b>&>(rG));
    G.idx=rG.idx;
  }

  template <unsigned int LoopFac>
  ostream& operator<<(ostream& os, const dSFMT<LoopFac>& G) {
    assert(IsAvailable(G));
    os<<LoopFac<<"\t";
    for(unsigned int i=0;i<G.size;++i)
    for(unsigned int k=0;k<4;++k)
      os<<G[i].u[k]<<"\t";
    os<<*(G.idx);
    return os;
  }

  template <unsigned int LoopFac>
  istream& operator>>(istream& is, dSFMT<LoopFac>& G) {
    assert(IsAvailable(G));
    unsigned int expLoopFac;
    is>>expLoopFac;
    if(expLoopFac!=LoopFac) myError("Imcompatiable LoopFac for dSFMT");
    for(unsigned int i=0;i<G.size;++i)
    for(unsigned int k=0;k<4;++k)
      is>>G[i].u[k];
    is>>*(G.idx);
    return is;
  }

}

#endif

