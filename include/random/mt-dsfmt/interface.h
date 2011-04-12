
#ifndef _Random_MT_DSFMT_Interface_H_
#define _Random_MT_DSFMT_Interface_H_

#include "unique-parameter/128bit/copy.h"
#include "unique-parameter/128bit/fill.h"
#include "vector/interface.h"

namespace mysimulator {

  unsigned int _initFunc1(const unsigned int x) {return (x^(x>.27))*1664525U;}
  unsigned int _initFunc2(const unsigned int x) {return (x^(x>.27))*1566083941;}

  template <unsigned int LFac=19937>
  struct MT_dSFMT {

    typedef MT_dSFMT<LFac>    Type;

    static const unsigned int N=(LFac-128)/104+1;
    static const unsigned int DN=N+N;
    static const unsigned int NStatus=N+1;
    static const unsigned int NStatusU32=NStatus*4;
    static const unsigned int NStatusByte=NStatus*16;
    static const unsigned int Lag=(NStatusU32>623?11:
                                  (NStatusU32>68?7:
                                  (NStatusU32>39?5:3)));
    static const unsigned int Mid=(NStatusU32-Lag)/2;
    static const unsigned int LagMid=Lag+Mid;
    static const unsigned int N32=N*4;
    static const unsigned int N64=DN;
    static const unsigned long long int LowMask=0x000FFFFFFFFFFFFFULL;
    static const unsigned long long int HighConst=0x3FF0000000000000ULL;
    static const unsigned int SR=12;
    static const unsigned int Pos1;
    static const unsigned int SL1;
    static const UniqueParameter128Bit Msk;
    static const UniqueParameter128Bit Fix;
    static const UniqueParameter128Bit Pcv;
#ifdef _Have_SSE2
    static const unsigned int SSE2_Shuff=0x1BU;
#endif

    Vector<UniqueParameter128Bit> s;
    unsigned int idx;

    MT_dSFMT() : s(),idx(0) {}
    MT_dSFMT(const Type&) { Error("Copier of MT_dSFMT Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MT_dSFMT Disabled!");
      return *this;
    }
    ~MT_dSFMT() { clearData(); }

    void clearData() { release(s); idx=0; }
    void _initMask() {
      unsigned long long int *p=s[0].ull;
      for(unsigned int i=0;i<DN;++i)  p[i]=(p[i]&LowMask)|HighConst;
    }
    void _Recursion(
        const UniqueParameter128Bit& a, const UniqueParameter128Bit& b,
        UniqueParameter128Bit& r, UniqueParameter128Bit& u) {
#ifdef _Have_SSE2
      UniqueParameter128Bit y,z,v,w;
      z.si=_mm_slli_epi64(a.si,SL1);
      y.si=_mm_shuffle_epi32(u.si,SSE2_Shuff);
      z.si=_mm_xor_si128(z.si,b.si);
      y.si=_mm_xor_si128(y.si,z.si);
      v.si=_mm_srli_epi64(y.si,SR);
      w.si=_mm_and_si128(y.si,Msk.si);
      v.si=_mm_xor_si128(v.si,a.si);
      v.si=_mm_xor_si128(v.si,w.si);
      copy(r,v);
      copy(u,y);
#else
      u.ull[0]=(a.ull[0]<<SL1)^(u.ull[1]>>32)^(u.ull[1]<<32)^b.ull[0];
      u.ull[1]=(a.ull[1]<<SL1)^(u.ull[0]>>32)^(u.ull[0]<<32)^b.ull[1];
      r.ull[0]=(u.ull[0]>>SR)^(u.ull[0]&Msk.ull[0])^a.ull[0];
      r.ull[1]=(u.ull[1]>>SR)^(u.ull[1]&Msk.ull[1])^a.ull[1];
#endif
    }
    void _PeriodCertification() {
      UniqueParameter128Bit tmp;
#ifdef _Have_SSE2
      tmp.si=_mm_xor_si128(s[N].si,Fix);
#else
      tmp.ull[0]=s[N].ull[0]^Fix.ull[0];
      tmp.ull[1]=s[N].ull[1]^Fix.ull[1];
#endif
#ifdef _Have_SSE2
      tmp=_mm_and_si128(tmp.si,Pcv.si);
#else
      tmp.ull[0]&=Pcv.ull[0];
      tmp.ull[1]&=Pcv.ull[1];
#endif
      unsigned long long inner=tmp.ull[0]^tmp.ull[1];
      for(unsigned int i=32;i>0;i>>=1)  inner^=inner>>i;
      inner&=1;
      if(inner!=1)  s[N].ull[1]^=1;
      return;
    }

    void init(const unsigned int seed) {
      assert(IsValid(*this));
      unsigned int *p=s[0].u;
      unsigned int *pend=p+NStatusU32;
      unsigned int r=seed,i=1;
      *p=seed;
      for(;p!=pend;) {
        r=1812433253UL*(r^(r>>30))+(i++);
        *(p++)=r;
      }
      _initMask();
      _PeriodCertification();
      idx=N64;
    }
    void init(const unsigned int *key, const unsigned int nkey,
              const unsigned int off=uZero, const int step=iOne) {
      assert(IsValid(*this)&&IsValid(key));
      unsigned int *p=s[0].u;
      UniqueParameter128Bit tmp;
      fill(tmp,0x8B);
      fill(s,tmp);
      unsigned int count=(nkey+1>NStatusU32?nkey+1:NStatusU32);
      unsigned int tmid=Mid%NStatusU32;
      unsigned int i,j,g,r;
      r=_initFunc1(p[0]^p[tmid]^p[NStatusU32-1]);
      p[tmid]+=r;
      r+=nkey;
      p[LagMid%NStatusU32]+=r;
      p[0]=r;
      --count;
      for(i=0,j=0,g=off;j<nkey;++j,g+=step) {
        tmid=(i+Mid)%NStatusU32;
        r=_initFunc1(p[i]^p[tmid]^p[(i+NStatusU32-1)%NStatusU32]);
        p[tmid]+=r;
        r+=key[g]+i;
        p[(i+LagMid)%NStatusU32]+=r;
        p[i]=r;
        i=(i+1)%NStatusU32;
      }
      for(;j<count;++j) {
        tmid=(i+Mid)%NStatusU32;
        r=_initFunc1(p[i]^p[tmid]^p[(i+NStatusU32-1)%NStatusU32]);
        p[tmid]+=r;
        r+=i;
        p[(i+LagMid)%NStatusU32]+=r;
        p[i]=r;
        i=(i+1)%NStatusU32;
      }
      for(j=0;j<NStatusU32;++j) {
        tmid=(i+Mid)%NStatusU32;
        r=_initFunc2(p[i]+p[tmid]+p[(i+NStatusU32-1)%NStatusU32]);
        p[tmid]^=r;
        r-=i;
        p[(i+LagMid)%NStatusU32]^=r;
        p[i]=r;
        i=(i+1)%NStatusU32;
      }
      _initMask();
      _PeriodCertification();
      idx=N64;
    }
    void init(const Vector<unsigned int>& key) { init(key.pdata,key.size); }

    void _GenAll() {
      unsigned int i;
      UniqueParameter128Bit lung;
      _Recursion(s[0],s[Pos1],s[0],lung);
      for(i=1;i<N-Pos1;++i) _Recursion(s[i],s[i+Pos1],s[i],lung);
      for(;i<N;++i) _Recursion(s[i],s[i+Pos1-N],s[i],lung);
      copy(s[N],lung);
    }

    template <typename T>
    const T rand() {
      Error("This type of data cannot be generated by MT_dSFMT!");
      return static_cast<T>(cZero);
    }

    const double doubleClose1Open2() {
      double *p=s[0].d;
      if(idx>=N64) { _GenAll(); idx=0; }
      return p[idx++];
    }
    const double doubleOpen0Open1() {
      UniqueParameter128Bit u;
      u.dvalue=doubleClose1Open2();
      u.ull[0]|=1;
      return u.dvalue-dOne;
    }

    const unsigned int _irand() {
      unsigned long long int *p=s[0].ull;
      if(idx>=N64) { _GenAll(); idx=0; }
      return p[idx++]&0xFFFFFFFFUL;
    }
    const double _drand() { return doubleClose1Open2()-1.0; }

  };

  template <>
  const unsigned int MT_dSFMT<521>::Pos1=3;
  template <>
  const unsigned int MT_dSFMT<521>::SL1=25;
  template <>
  const UniqueParameter128Bit MT_dSFMT<521>::Msk(0x000FBFEFFF77EFFFULL,
                                                 0x000FFEEBFBDFBFDFULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<521>::Fix(0xCFB393D661638469ULL,
                                                 0xC166867883AE2ADBULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<521>::Pcv(0xCCAA588000000000ULL,
                                                 0x0000000000000001ULL);

  template <>
  const unsigned int MT_dSFMT<1279>::Pos1=9;
  template <>
  const unsigned int MT_dSFMT<1279>::SL1=19;
  template <>
  const UniqueParameter128Bit MT_dSFMT<1279>::Msk(0x000EFFF7FFDDFFEEULL,
                                                  0x000FBFFFFFF77FFFULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<1279>::Fix(0xB66627623D1A31BEULL,
                                                  0x04B6C51147B6109BULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<1279>::Pcv(0x7049F2DA382A6AEBULL,
                                                  0xDE4CA84A40000001ULL);

  template <>
  const unsigned int MT_dSFMT<2203>::Pos1=7;
  template <>
  const unsigned int MT_dSFMT<2203>::SL1=19;
  template <>
  const UniqueParameter128Bit MT_dSFMT<2203>::Msk(0x000FDFFFF5EDBFFFULL,
                                                  0x000F77FFFFFFFBFEULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<2203>::Fix(0xB14E907A39338485ULL,
                                                  0xF98F0735C637EF90ULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<2203>::Pcv(0x8000000000000000ULL,
                                                  0x0000000000000001ULL);

  template <>
  const unsigned int MT_dSFMT<4253>::Pos1=19;
  template <>
  const unsigned int MT_dSFMT<4253>::SL1=19;
  template <>
  const UniqueParameter128Bit MT_dSFMT<4253>::Msk(0x0007B7FFFEF5FEFFULL,
                                                  0x000FFDFFEFFEFBFCULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<4253>::Fix(0x80901B5FD7A11C65ULL,
                                                  0x5A63FF0E7CB0BA74ULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<4253>::Pcv(0x1AD277BE12000000ULL,
                                                  0x0000000000000001ULL);

  template <>
  const unsigned int MT_dSFMT<11213>::Pos1=37;
  template <>
  const unsigned int MT_dSFMT<11213>::SL1=19;
  template <>
  const UniqueParameter128Bit MT_dSFMT<11213>::Msk(0x000FFFFFFDF7FFFDULL,
                                                   0x000DFFFFFFF6BFFFULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<11213>::Fix(0xD0EF7B7C75B06793ULL,
                                                   0x9C50FF4CAAE0A641ULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<11213>::Pcv(0x8234C51207C80000ULL,
                                                   0x0000000000000001ULL);

  template <>
  const unsigned int MT_dSFMT<19937>::Pos1=117;
  template <>
  const unsigned int MT_dSFMT<19937>::SL1=19;
  template <>
  const UniqueParameter128Bit MT_dSFMT<19937>::Msk(0x000FFAFFFFFFFB3FULL,
                                                   0x000FFDFFFC90FFFDULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<19937>::Fix(0x90014964B32F4329ULL,
                                                   0x3B8D12AC548A7C7AULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<19937>::Pcv(0x3D84E1AC0DC82880ULL,
                                                   0x0000000000000001ULL);

  template <>
  const unsigned int MT_dSFMT<44497>::Pos1=304;
  template <>
  const unsigned int MT_dSFMT<44497>::SL1=19;
  template <>
  const UniqueParameter128Bit MT_dSFMT<44497>::Msk(0x000FF6DFFFFFFFEFULL,
                                                   0x0007FFDDDEEFFF6FULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<44497>::Fix(0x75D910F235F6E10EULL,
                                                   0x7B32158AEDC8E969ULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<44497>::Pcv(0x4C3356B2A0000000ULL,
                                                   0x0000000000000001ULL);

  template <>
  const unsigned int MT_dSFMT<86243>::Pos1=231;
  template <>
  const unsigned int MT_dSFMT<86243>::SL1=13;
  template <>
  const UniqueParameter128Bit MT_dSFMT<86243>::Msk(0x000FFEDFF6FFFFDFULL,
                                                   0x000FFFF7FDFFFF7EULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<86243>::Fix(0x1D553E776B975E68ULL,
                                                   0x648FAADF1416BF91ULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<86243>::Pcv(0x5F2CD03E2758A373ULL,
                                                   0xC0B7EB8410000001ULL);

  template <>
  const unsigned int MT_dSFMT<132049>::Pos1=371;
  template <>
  const unsigned int MT_dSFMT<132049>::SL1=23;
  template <>
  const UniqueParameter128Bit MT_dSFMT<132049>::Msk(0x000FB9F4EFF4BF77ULL,
                                                    0x000FFFFFBFEFFF37ULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<132049>::Fix(0x4CE24C0E4E234F3BULL,
                                                    0x62612409B5665C2DULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<132049>::Pcv(0x181232889145D000ULL,
                                                    0x0000000000000001ULL);

  template <>
  const unsigned int MT_dSFMT<216091>::Pos1=1890;
  template <>
  const unsigned int MT_dSFMT<216091>::SL1=23;
  template <>
  const UniqueParameter128Bit MT_dSFMT<216091>::Msk(0x000BF7DF7FEFCFFFULL,
                                                    0x000E7FFFFEF737FFULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<216091>::Fix(0xD7F95A04764C27D7ULL,
                                                    0x6A483861810BEBC2ULL);
  template <>
  const UniqueParameter128Bit MT_dSFMT<216091>::Pcv(0x3AF0A8F3D5600000ULL,
                                                    0x0000000000000001ULL);

  template <unsigned int LFac>
  bool IsValid(const MT_dSFMT<LFac>& G) { return IsValid(G.s)&&(G.idx!=0); }

  template <unsigned int LFac>
  void release(MT_dSFMT<LFac>& G) { G.clearData(); }

  template <> template <>
  const unsigned int MT_dSFMT<521>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<1279>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<2203>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<4253>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<11213>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<19937>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<44497>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<86243>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<132049>::rand<unsigned int>() { return _irand(); }
  template <> template <>
  const unsigned int MT_dSFMT<216091>::rand<unsigned int>() { return _irand(); }

  template <> template <>
  const double MT_dSFMT<521>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<1279>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<2203>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<4253>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<11213>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<19937>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<44497>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<86243>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<132049>::rand<double>() { return _drand(); }
  template <> template <>
  const double MT_dSFMT<216091>::rand<double>() { return _drand(); }

}

#endif

