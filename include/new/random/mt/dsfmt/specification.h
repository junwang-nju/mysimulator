
#ifndef _Random_MT_DSFMT_Specification_H_
#define _Random_MT_DSFMT_Specification_H_

#include "random/mt/interface.h"
#include "unique/128bit/copy.h"
#include "array/1d/interface.h"
#include <cstring>

namespace mysimulator {

  unsigned int _initFuncA(const unsigned int x) { return (x^(x>>27))*1664525U; }
  unsigned int _initFuncB(const unsigned int x) {
    return (x^(x>>27))*1566083941U;
  }

  static const Unique128Bit SSE2_DoubleTwo(dTwo,dTwo);
  static const Unique128Bit SSE2_DoubleNOne(dNOne,dNOne);
  static const Unique128Bit SSE2_IntOne(1ULL,1ULL);

  void convert2Close1Open2(Unique128Bit&) {}
#ifdef _Have_SSE2
  void convert2Close0Open1(Unique128Bit& w) {
    _mm_storeu_pd(w.d,_mm_add_pd(_mm_loadu_pd(w.d),SSE2_DoubleNOne.sd));
  }
  void convert2Open0Close1(Unique128Bit& w) {
    _mm_storeu_pd(w.d,_mm_sub_pd(SSE2_DoubleTwo.sd,_mm_loadu_pd(w.d)));
  }
  void convert2Open0Open1(Unique128Bit& w) {
    _mm_storeu_si128(&(w.si),_mm_or_si128(_mm_loadu_si128(&(w.si)),SSE2_IntOne.si));
    convert2Close0Open1(w);
  }
#else
  void convert2Close0Open1(Unique128Bit& w) { w.d[0]-=1.; w.d[1]-=1.; }
  void convert2Open0Close1(Unique128Bit& w) {
    w.d[0]=2.-w.d[0]; w.d[1]=2.-w.d[1];
  }
  void convert2Open0Open1(Unique128Bit& w) {
    w.ull[0]|=1;  w.ull[1]|=1; convert2Close0Open1(w);
  }
#endif

  template <unsigned int Fac>
  struct MersenneTwister<dSFMT,Fac> : public RandomBase {

    public:

      typedef MersenneTwister<dSFMT,Fac>  Type;
      typedef RandomBase  ParentType;

      static const unsigned int N;
      static const unsigned int DualN;
      static const unsigned int NStatus;
      static const unsigned int NStatusU32;
      static const unsigned int NStatusU32m1;
      static const unsigned int NStatusByte;
      static const unsigned int Lag;
      static const unsigned int Mid;
      static const unsigned int LagMid;
      static const unsigned int N32;
      static const unsigned int N64;
      static const unsigned long long Low;
      static const unsigned long long Upp;
      static const unsigned int SR;
      static const unsigned int Pos;
      static const unsigned int SL;
      static const Unique128Bit Msk;
      static const Unique128Bit Fix;
      static const Unique128Bit Pcv;
#ifdef _Have_SSE2
      static const unsigned int SSE2_Shuff;
#endif

      Array1D<Unique128Bit> s;
      unsigned int idx;

      MersenneTwister() : s(), idx(0U) {}
      ~MersenneTwister() { clearData(); }

      void clearData() { release(s); idx=0U; }
      bool isvalid() const { return IsValid(s); }

      void _initMask() {
        unsigned long long *p=s[0].ull;
        for(unsigned int i=0;i<DualN;++i) p[i]=(p[i]&Low)|Upp;
      }
      void _Recursion(
          const Unique128Bit& a, const Unique128Bit& b, Unique128Bit& r,
          Unique128Bit& u) {
#ifdef _Have_SSE2
        Unique128Bit y,z,v,w,ta,tb,tMsk;
        ta.si=_mm_loadu_si128(&(a.si));
        tb.si=_mm_loadu_si128(&(b.si));
        z.si=_mm_slli_epi64(ta.si,SL);
        y.si=_mm_shuffle_epi32(u.si,SSE2_Shuff);
        z.si=_mm_xor_si128(z.si,tb.si);
        y.si=_mm_xor_si128(y.si,z.si);
        v.si=_mm_srli_epi64(y.si,SR);
        tMsk.si=_mm_loadu_si128(&(Msk.si));
        w.si=_mm_and_si128(y.si,tMsk.si);
        v.si=_mm_xor_si128(v.si,ta.si);
        v.si=_mm_xor_si128(v.si,w.si);
        copy(r,v);
        copy(u,y);
#else
        u.ull[0]=(a.ull[0]<<SL)^(u.ull[1]>>32)^(u.ull[1]<<32)^b.ull[0];
        u.ull[1]=(a.ull[1]<<SL)^(u.ull[0]>>32)^(u.ull[0]<<32)^b.ull[1];
        r.ull[0]=(u.ull[0]>>SR)^(u.ull[0]&Msk.ull[0])^a.ull[0];
        r.ull[1]=(u.ull[1]>>SR)^(u.ull[1]&Msk.ull[1])^a.ull[1];
#endif
      }
      void _PeriodCertification() {
        Unique128Bit tmp;
#ifdef _Have_SSE2
        Unique128Bit tmp1;
        tmp.si=_mm_loadu_si128(&(s[N].si));
        tmp1.si=_mm_loadu_si128(&(Fix.si));
        tmp.si=_mm_xor_si128(tmp.si,tmp1.si);
        tmp1.si=_mm_loadu_si128(&(Pcv.si));
        tmp.si=_mm_and_si128(tmp.si,tmp1.si);
#else
        tmp.ull[0]=s[N].ull[0]^Fix.ull[0];
        tmp.ull[1]=s[N].ull[1]^Fix.ull[1];
        tmp.ull[0]&=Pcv.ull[0];
        tmp.ull[1]&=Pcv.ull[1];
#endif
        unsigned long long inner=tmp.ull[0]^tmp.ull[1];
        for(unsigned int i=32;i>0;i>>=1)  inner^=(inner>>i);
        inner&=1;
        if(inner!=1)  s[N].ull[1]^=1ULL;
        return;
      }

      virtual void init(const unsigned int& seed) {
        unsigned int *p=s[0].u;
        unsigned int *pend=p+NStatusU32;
        unsigned int r=seed, i=1;
        *p=seed;
        while(p!=pend) {
          r=1812433253UL*(r^(r>>30))+(i++);
          *(p++)=r;
        }
        _initMask();
        _PeriodCertification();
        idx=N64;
      }
      void init(const unsigned int* key, const unsigned int nkey,
                const unsigned int off=uZero, const int step=iOne) {
        assert(IsValid(key));
        unsigned int *p=s[0].u;
        memset(s[0].c,0x8B,NStatusByte);
        unsigned int count=(nkey+1>NStatusU32?nkey+1:NStatusU32);
        unsigned int tmid=Mid%NStatusU32;
        unsigned int i,j,g,r;
        r=_initFuncA(p[0]^p[tmid]^p[NStatusU32-1]);
        p[tmid]+=r;
        r+=nkey;
        p[LagMid%NStatusU32]+=r;
        p[0]=r;
        --count;
        for(i=0,j=0,g=off;j<nkey;++j,g+=step) {
          tmid=(i+Mid)%NStatusU32;
          r=_initFuncA(p[i]^p[tmid]^p[(i+NStatusU32m1)%NStatusU32]);
          p[tmid]+=r;
          r+=key[g]+i;
          p[(i+LagMid)%NStatusU32]+=r;
          p[i]=r;
          i=(i+1)%NStatusU32;
        }
        for(;j<count;++j) {
          tmid=(i+Mid)%NStatusU32;
          r=_initFuncA(p[i]^p[tmid]^p[(i+NStatusU32m1)%NStatusU32]);
          p[tmid]+=r;
          r+=i;
          p[(i+LagMid)%NStatusU32]+=r;
          p[i]=r;
          i=(i+1)%NStatusU32;
        }
        for(j=0;j<NStatusU32;++j) {
          tmid=(i+Mid)%NStatusU32;
          r=_initFuncB(p[i]+p[tmid]+p[(i+NStatusU32m1)%NStatusU32]);
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
      void init(const Array1DContent<unsigned int>& key) {
        init(key.start,key.size);
      }

      void _GenAll() {
        unsigned int i;
        Unique128Bit lung;
        _Recursion(s[0],s[Pos],s[0],lung);
        for(i=1;i<N-Pos;++i) _Recursion(s[i],s[i+Pos],s[i],lung);
        for(;i<N;++i) _Recursion(s[i],s[i+Pos-N],s[i],lung);
        copy(s[N],lung);
      }

      template <typename T>
      const T rand() {
        Error("This type of data cannot be generated by dSFMT method!");
        return static_cast<T>(cZero);
      }

      const double doubleClose1Open2() {
        double *p=s[0].d;
        if(idx>=N64)  { _GenAll(); idx=0; }
        return p[idx++];
      }
      const double doubleOpen0Close1() { return 2.0-doubleClose1Open2(); }
      const double doubleOpen0Open1() {
        Unique128Bit u;
        u.d[0]=doubleClose1Open2();
        u.ull[0]|=1;
        return u.d[0]-dOne;
      }

      const unsigned int _irand() {
        unsigned long long *p=s[0].ull;
        if(idx>=N64)  { _GenAll(); idx=0; }
        return p[idx++]&0xFFFFFFFFUL;
      }
      const double _drand() { return doubleClose1Open2()-1.0; }

      virtual const double randomDouble();
      virtual const unsigned int randomUInt();

      typedef void (*ConvertFuncType)(Unique128Bit&);

      void _GenArray(Unique128Bit* array, const unsigned int& size,
                     const ConvertFuncType& cvfunc) {
        unsigned int i,j;
        Unique128Bit lung;
        copy(lung,s[N]);
        _Recursion(s[0],s[Pos],array[0],lung);
        for(i=0;i<N-Pos;++i) _Recursion(s[i],s[i+Pos],array[i],lung);
        for(;i<N;++i) _Recursion(s[i],array[i+Pos-N],array[i],lung);
        for(;i+N<size;++i)  {
          _Recursion(array[i-N],array[i+Pos-N],array[i],lung);
          cvfunc(array[i-N]);
        }
        for(j=0;j+size<DualN;++j)  copy(s[j],array[j+size-N]);
        for(;i<size;++i,++j)  {
          _Recursion(array[i-N],array[i+Pos-N],array[i],lung);
          copy(s[j],array[i]);
          cvfunc(array[i-N]);
        }
        for(i=size-N;i<size;++i)  cvfunc(array[i]);
        copy(s[N],lung);
      }
      void _FillArray(double* const& array, const unsigned int& size,
                      const ConvertFuncType& cvfunc) {
        assert((size&1)==0);
        assert(size>=N64);
        _GenArray(reinterpret_cast<Unique128Bit*>(array),size>>1,cvfunc);
      }

      void fillFast(double* const& array, const unsigned int& size) {
        _FillArray(array,size,convert2Close0Open1);
      }
      void fillFast(Array1DContent<double>& v) { fillFast(v.start,v.size); }
      void fillFastClose1Open2(double* const& array, const unsigned int& size) {
        _FillArray(array,size,convert2Close1Open2);
      }
      void fillFastClose1Open2(Array1DContent<double>& v) {
        fillFastClose1Open2(v.start,v.size);
      }
      void fillFastOpen0Close1(double* const& array, const unsigned int& size) {
        _FillArray(array,size,convert2Open0Close1);
      }
      void fillFastOpen0Close1(Array1DContent<double>& v) {
        fillFastOpen0Close1(v.start,v.size);
      }
      void fillFastOpen0Open1(double* const& array, const unsigned int* size) {
        _FillArray(array,size,convert2Open0Open1);
      }
      void fillFastOpen0Open1(Array1DContent<double>& v) {
        fillFastOpen0Open1(v.start,v.size);
      }

    private:

      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

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
    (MersenneTwister<dSFMT,Fac>::NStatusU32>68?7:
    (MersenneTwister<dSFMT,Fac>::NStatusU32>39?5:3)));
  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::Mid=
    (MersenneTwister<dSFMT,Fac>::NStatusU32-MersenneTwister<dSFMT,Fac>::Lag)/2;
  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::LagMid=
    MersenneTwister<dSFMT,Fac>::Lag+MersenneTwister<dSFMT,Fac>::Mid;
  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::N32=
    MersenneTwister<dSFMT,Fac>::N*4;
  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::N64=
    MersenneTwister<dSFMT,Fac>::DualN;
  template <unsigned int Fac>
  const unsigned long long MersenneTwister<dSFMT,Fac>::Low=
    0x000FFFFFFFFFFFFFULL;
  template <unsigned int Fac>
  const unsigned long long MersenneTwister<dSFMT,Fac>::Upp=
    0x3FF0000000000000ULL;
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

#ifdef _Have_SSE2
  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::SSE2_Shuff=0x1BU;
#endif

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

  template <> template <>
  const unsigned int MersenneTwister<dSFMT,521>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,1279>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,2203>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,4253>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,11213>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,19937>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,44497>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,86243>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,132049>::rand<unsigned int>() {
    return _irand();
  }
  template <> template <>
  const unsigned int MersenneTwister<dSFMT,216091>::rand<unsigned int>() {
    return _irand();
  }

  template <> template <>
  const double MersenneTwister<dSFMT,521>::rand<double>() { return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,1279>::rand<double>() { return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,2203>::rand<double>() { return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,4253>::rand<double>() { return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,11213>::rand<double>() { return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,19937>::rand<double>() { return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,44497>::rand<double>() { return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,86243>::rand<double>() { return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,132049>::rand<double>(){ return _drand(); }
  template <> template <>
  const double MersenneTwister<dSFMT,216091>::rand<double>(){ return _drand(); }

  template <unsigned int Fac>
  const double MersenneTwister<dSFMT,Fac>::randomDouble() {
    return rand<double>();
  }

  template <unsigned int Fac>
  const unsigned int MersenneTwister<dSFMT,Fac>::randomUInt() {
    return rand<unsigned int>();
  }

}

#endif

