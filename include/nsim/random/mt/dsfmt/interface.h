
#ifndef _Random_MT_DSFMT_Interface_H_
#define _Random_MT_DSFMT_Interface_H_

#include "random/mt/interface.h"
#include "random/base/interface.h"
#include "random/mt/dsfmt/module/convert.h"
#include "random/mt/dsfmt/module/init-func.h"

namespace mysimulator {

  template <unsigned int Fac>
  struct MersenneTwister<dSFMT,Fac> : public RandomBase {

    public:

      typedef MersenneTwister<dSFMT,Fac>    Type;
      typedef RandomBase  ParentType;
      typedef void (*CvFuncType)(Unique128Bit&);

      static const unsigned int N;
      static const unsigned int DualN;
      static const unsigned int NStatus;
      static const unsigned int NStatusU32;
      static const unsigned int NStatusU32m1;
      static const unsigned int NStatusByte;
      static const unsigned int Lag;
      static const unsigned int Mid;
      static const unsigned int LagMid;
      static const unsigned int N64;
      static const unsigned long long Low;
      static const unsigned long long Upp;
      static const unsigned int SR;
      static const unsigned int Pos;
      static const unsigned int SL;
      static const Unique128Bit Msk;
      static const Unique128Bit Fix;
      static const Unique128Bit Pcv;
#ifdef _HAVE_SSE2
      static const unsigned int SSE2Shuffle;
#endif

      Array1D<Unique128Bit> s;
      unsigned int idx;

      MersenneTwister() : ParentType(), s(), idx(0U) {}
      ~MersenneTwister() { Clear(*this); }

      bool IsValid() const { return s.IsValid(); }

      void Allocate() { Clear(*this); s.Allocate(NStatus); R.idx=0; }

      void _InitMask() {
        unsigned long long *p=reinterpret_cast<unsigned long long*>(s._data);
        for(unsigned int i=0;i<DualN;++i) p[i]=(p[i]&Low)|Upp;
      }
      void _Recursion(const Unique128Bit& a,const Unique128Bit& b,
                      Unique128Bit& r,Unique128Bit& u) {
#ifdef _HAVE_SSE2
        Unique128Bit y,z,v,w,ta,tb,tMsk;
        ta.si=_mm_loadu_si128(&(a.si));
        tb.si=_mm_loadu_si128(&(b.si));
        z.si=_mm_slli_epi64(ta.si,SL);
        y.si=_mm_shuffle_epi32(u.si,SSE2Shuffle);
        z.si=_mm_xor_si128(z.si,tb.si);
        y.si=_mm_xor_si128(y.si,z.si);
        v.si=_mm_srli_epi64(y.si,SR);
        tMsk.si=_mm_loadu_si128(&(Msk.si));
        w.si=_mm_and_si128(y.si,tMsk.si);
        v.si=_mm_xor_si128(v.si,ta.si);
        v.si=_mm_xor_si128(v.si,w.si);
        Copy(r,v);
        Copy(u,y);
#else
        u.ullv[0]=(a.ullv[0]<<SL)^(u.ullv[1]>>32)^(u.ullv[1]<<32)^b.ullv[0];
        u.ullv[1]=(a.ullv[1]<<SL)^(u.ullv[0]>>32)^(u.ullv[0]<<32)^b.ullv[1];
        r.ullv[0]=(u.ullv[0]>>SR)^(u.ullv[0]&Msk.ullv[0])^a.ullv[0];
        r.ullv[1]=(u.ullv[1]>>SR)^(u.ullv[1]&Msk.ullv[1])^a.ullv[1];
#endif
      }
      void _PeriodicCertification() {
        Unique128Bit tmp;
#ifdef _HAVE_SSE2
        Unique128Bit tmp1;
        tmp.si=_mm_loadu_si128(&(s[N].si));
        tmp1.si=_mm_loadu_si128(&(Fix.si));
        tmp.si=_mm_xor_si128(tmp.si,tmp1.si);
        tmp1.si=_mm_loadu_si128(&(Pcv.si));
        tmp.si=_mm_and_si128(tmp.si,tmp1.si);
#else
        tmp.ull[0]=s[N].ullv[0]^Fix.ullv[0];
        tmp.ull[1]=s[N].ullv[1]^Fix.ullv[1];
        tmp.ull[0]&=Pcv.ullv[0];
        tmp.ull[1]&=Pcv.ullv[1];
#endif
        unsigned long long inner=tmp.ullv[0]^tmp.ullv[1];
        for(unsigned int i=32;i>0;i>>=1) inner^=(inner>>i);
        inner&=1;
        if(inner!=1)  s[N].ullv[1]^=1ULL;
      }

      virtual void Init(unsigned int seed) {
        unsigned int *p=reinterpret_cast<unsigned int*>(s._data);
        unsigned int *pend=p+NStatusU32;
        unsigned int r=seed, i=1;
        *p=seed;
        for(p!=pend) {
          r=1812433253UL*(r^(r>>30))+(i++);
          *(p++)=r;
        }
        _InitMask();
        _PeriodicCertification();
        idx=N64;
      }
      void Init(const Array1D<unsigned int>& Key, unsigned int n) {
        assert(Key.IsValid());
        unsigned int *p=reinterpret_cast<unsigned int*>(s._data);
        memset(reinterpret_cast<char*>(s._data),0x8B,NStatusByte);
        unsigned int count=(n+1>NStatusU32?n+1:NStatusU32);
        unsigned int tmid=Mid%NStatusU32;
        unsigned int i,j,g,r;
        r=_dSFMTInitFuncA(p[0]^p[tmid]^p[NStatusU32m1]);
        p[tmid]+=r;
        r+=nkey;
        p[LagMid%NStatusU32]+=r;
        p[0]=r;
        --count;
        for(i=0,j=0,g=off;j<nkey;++j,g+=step) {
          tmid=(i+Mid)%NStatusU32;
          r=_dSFMTInitFuncA(p[i]^p[tmid]^p[(i+NStatusU32m1)%NStatusU32]);
          p[tmid]+=r;
          r+=Key[g]+i;
          p[(i+LagMid)%NStatusU32]+=r;
          p[i]=r;
          i=(i+1)%NStatusU32;
        }
        for(;j<count;++j) {
          tmid=(i+Mid)%NStatusU32;
          r=_dSFMTInitFuncA(p[i]^p[tmid]^p[(i+NStatusU32m1)%NStatusU32]);
          p[tmid]+=r;
          r+=i;
          p[(i+LagMid)%NStatusU32]+=r;
          p[i]=r;
          i=(i+1)%NStatusU32;
        }
        for(j=0;j<NStatusU32;++j) {
          tmid=(i+Mid)%NStatusU32;
          r=_dSFMTInitFuncB(p[i]+p[tmid]+p[(i+NStatusU32m1)%NStatusU32]);
          p[tmid]^=r;
          r-=i;
          p[(i+LagMid)%NStatusU32]^=r;
          p[i]=r;
          i=(i+1)%NStatusU32;
        }
        _InitMask();
        _PeriodicCertification();
        idx=N64;
      }

      void _GenAll() {
        unsigned int i;
        Unique128Bit lung;
        _Recursion(s[0],s[Pos],s[0],lung);
        for(i=1;i<N-Pos;++i) _Recursion(s[i],s[i+Pos],s[i],lung);
        for(;i<N;++i) _Recursion(s[i],s[i+Pos-N],s[i],lung);
        Copy(s[N],lung);
      }

      double DoubleClose1Open2() {
        double *p=reinterpret_cast<double*>(s._data);
        if(idx>=N64) { _GenAll(); idx=0; }
        return p[idx++];
      }
      double DoubleOpen0Close1() { return 2.0-DoubleClose1Open2(); }
      double DoubleOpen0Open1() {
        Unique64Bit u;
        u.d=DoubleClose1Open2();
        u.ull|=1;
        return u.d-1.;
      }
      double DoubleClose0Open1() { return DoubleClose1Open2()-1.; }

      virtual double Double() { return DoubleClose0Open1(); }
      virtual unsigned int UInt() {
        unsigned long long *p=reinterpret_cast<unsigned long long*>(s._data);
        if(idx>=N64) { _GenAll(); idx=0; }
        return p[idx++]&0xFFFFFFFFUL;
      }

      void _GenArray(Unique128Bit* V,unsigned int n,CvFuncType Cv) {
        assert(n>=N64);
        unsigned int i,j;
        Unique128Bit lung;
        Copy(lung,s[N]);
        _Recursion(s[0],s[Pos],V[0],lung);
        for(i=0;i<N-Pos;++i) _Recursion(s[i],s[i+Pos],V[i],lung);
        for(;i<N;++i) _Recursion(s[i],V[i+Pos-N],V[i],lung);
        for(;i+N<n;++i) {
          _Recursion(V[i-N],V[i+Pos-N],V[i],lung);
          Cv(V[i-N]);
        }
        for(j=0;j+n<DualN;++j) Copy(s[j],V[j+n-N]);
        for(;i<n;++i,++j) {
          _Recursion(V[i-N],V[i+Pos-N],V[i],lung);
          Copy(s[j],V[i]);
          Cv(V[i-N]);
        }
        for(i=size-N;i<size;++j) CvFunc(V[i]);
        Copy(s[N],lung);
      }
      void _FillArray(Array1D<double>& V,unsigned int n,CvFuncType Cv) {
        assert((n&1)==0);
        _GenArray(reinterpret_cast<Unique128Bit*>(V._data),n>>1,Cv);
      }
      void FastFillClose1Open2(Array1D<double>& V,unsigned int n) {
        _FillArray(V,n,Convert2Close1Open2);
      }
      void FastFillClose0Open1(Array1D<double>& V,unsigned int n) {
        _FillArray(V,n,Convert2Close0Open1);
      }
      void FastFillOpen0Close1(Array1D<double>& V,unsigned int n) {
        _FillArray(V,n,Convert2Open0Close1);
      }
      void FastFillOpen0Open1(Array1D<double>& V,unsigned int n) {
        _FillArray(V,n,Convert2Open0Open1);
      }
      void FastFill(Array1D<double>& V,unsigned int n) {
        FastFillClose0Open1(V,n);
      }

    private:

      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <unsigned int Fac>
  void Clear(MersenneTwister<dSFMT,Fac>& R) {
    Clear(R.s);
    idx=0U;
    Clear(static_cast<typename MersenneTwister<dSFMT,Fac>::ParentType&>(R));
  }

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::N=(Fac-128)/104+1;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::DualN=
    MersenneTwister<dSFMT,Fac>::N*2;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::NStatus=
    MersenneTwister<dSFMT,Fac>::N+1;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::NStatusU32=
    MersenneTwister<dSFMT,Fac>::NStatus*4;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::NStatusU32m1=
    MersenneTwister<dSFMT,Fac>::NStatusU32-1;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::NStatusByte=
    MersenneTwister<dSFMT,Fac>::NStatus*16;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::Lag=
    (MersenneTwister<dSFMT,Fac>::NStatusU32>623?11:
    (MersenneTwister<dSFMT,Fac>::NStatusU32>68? 7:
    (MersenneTwister<dSFMT,Fac>::NStatusU32>39? 5:3)));

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::Mid=
    (MersenneTwister<dSFMT,Fac>::NStatusU32-
     MersenneTwister<dSFMT,Fac>::Lag)/2;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::LagMid=
    MersenneTwister<dSFMT,Fac>::Lag+MersenneTwister<dSFMT,Fac>::Mid;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::N64=
    MersenneTwister<dSFMT,Fac>::DualN;

  template <unsigned int Fac>
  const unsigned long long MersenneTwister<dSFMT,Fac>::Low=
    0x000FFFFFFFFFFFFFULL;

  template <unsigned int Fac>
  const unsigned long long MersenneTwister<dSFMT,Fac>::Upp=
    0x3FF0000000000000ULL;

#ifdef _HAVE_SSE2
  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::SSE2Shuffle=0x1BU;
#endif

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::SR=12;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::Pos=0;
  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::SL=0;
  template <unsigned int Fac>
  const Unique128Bit MersenneTwister<dSFMT,Fac>::Msk(0ULL,0ULL);
  template <unsigned int Fac>
  const Unique128Bit MersenneTwister<dSFMT,Fac>::Fix(0ULL,0ULL);
  template <unsigned int Fac>
  const Unique128Bit MersenneTwister<dSFMT,Fac>::Pcv(0ULL,0ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,521>::Pos=3;
  template <>
  const unsigned int MersenneTwister<dSFMT,521>::SL=25;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,521>::Msk(0x000FBFEFFF77EFFFULL,
                                                     0x000FFEEBFBDFBFDFULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,521>::Fix(0xCFB393D661638469ULL,
                                                     0xC166867883AE2ADBULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,521>::Pcv(0xCCAA588000000000ULL,
                                                     0x0000000000000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,1279>::Pos=9;
  template <>
  const unsigned int MersenneTwister<dSFMT,1279>::SL=19;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,1279>::Msk(0x000EFFF7FFDDFFEEULL,
                                                      0x000FBFFFFFF77FFFULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,1279>::Fix(0xB66627623D1A31BEULL,
                                                      0x04B6C51147B6109BULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,1279>::Pcv(0x7049F2DA382A6AEBULL,
                                                      0xDE4CA84A40000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,2203>::Pos=7;
  template <>
  const unsigned int MersenneTwister<dSFMT,2203>::SL=19;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,2203>::Msk(0x000FDFFFF5EDBFFFULL,
                                                      0x000F77FFFFFFFBFEULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,2203>::Fix(0xB14E907A39338485ULL,
                                                      0xF98F0735C637EF90ULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,2203>::Pcv(0x8000000000000000ULL,
                                                      0x0000000000000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,4253>::Pos=19;
  template <>
  const unsigned int MersenneTwister<dSFMT,4253>::SL=19;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,4253>::Msk(0x0007B7FFFEF5FEFFULL,
                                                      0x000FFDFFEFFEFBFCULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,4253>::Fix(0x80901B5FD7A11C65ULL,
                                                      0x5A63FF0E7CB0BA74ULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,4253>::Pcv(0x1AD277BE12000000ULL,
                                                      0x0000000000000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,11213>::Pos=37;
  template <>
  const unsigned int MersenneTwister<dSFMT,11213>::SL=19;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,11213>::Msk(0x000FFFFFFDF7FFFDULL,
                                                       0x000DFFFFFFF6BFFFULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,11213>::Fix(0xD0EF7B7C75B06793ULL,
                                                       0x9C50FF4CAAE0A641ULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,11213>::Pcv(0x8234C51207C80000ULL,
                                                       0x0000000000000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,19937>::Pos=117;
  template <>
  const unsigned int MersenneTwister<dSFMT,19937>::SL=19;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,19937>::Msk(0x000FFAFFFFFFFB3FULL,
                                                       0x000FFDFFFC90FFFDULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,19937>::Fix(0x90014964B32F4329ULL,
                                                       0x3B8D12AC548A7C7AULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,19937>::Pcv(0x3D84E1AC0DC82880ULL,
                                                       0x0000000000000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,44497>::Pos=304;
  template <>
  const unsigned int MersenneTwister<dSFMT,44497>::SL=19;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,44497>::Msk(0x000FF6DFFFFFFFEFULL,
                                                       0x0007FFDDDEEFFF6FULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,44497>::Fix(0x75D910F235F6E10EULL,
                                                       0x7B32158AEDC8E969ULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,44497>::Pcv(0x4C3356B2A0000000ULL,
                                                       0x0000000000000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,86243>::Pos=231;
  template <>
  const unsigned int MersenneTwister<dSFMT,86243>::SL=13;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,86243>::Msk(0x000FFEDFF6FFFFDFULL,
                                                       0x000FFFF7FDFFFF7EULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,86243>::Fix(0x1D553E776B975E68ULL,
                                                       0x648FAADF1416BF91ULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,86243>::Pcv(0x5F2CD03E2758A373ULL,
                                                       0xC0B7EB8410000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,132049>::Pos=371;
  template <>
  const unsigned int MersenneTwister<dSFMT,132049>::SL=23;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,132049>::Msk(0x000FB9F4EFF4BF77ULL,
                                                        0x000FFFFFBFEFFF37ULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,132049>::Fix(0x4CE24C0E4E234F3BULL,
                                                        0x62612409B5665C2DULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,132049>::Pcv(0x181232889145D000ULL,
                                                        0x0000000000000001ULL);

  template <>
  const unsigned int MersenneTwister<dSFMT,216091>::Pos=1890;
  template <>
  const unsigned int MersenneTwister<dSFMT,216091>::SL=23;
  template <>
  const Unique128Bit MersenneTwister<dSFMT,216091>::Msk(0x000BF7DF7FEFCFFFULL,
                                                        0x000E7FFFFEF737FFULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,216091>::Fix(0xD7F95A04764C27D7ULL,
                                                        0x6A483861810BEBC2ULL);
  template <>
  const Unique128Bit MersenneTwister<dSFMT,216091>::Pcv(0x3AF0A8F3D5600000ULL,
                                                        0x0000000000000001ULL);

}

#endif

