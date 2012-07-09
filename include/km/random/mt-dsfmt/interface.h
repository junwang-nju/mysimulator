
#ifndef _Random_MT_DSFMT_Interface_H_
#define _Random_MT_DSFMT_Interface_H_

#include "random/interface.h"
#include "random/xSFMT-work-func.h"

namespace mysimulator {

  template <unsigned int Fac> class MersenneTwisterDSFMT;
  template <unsigned int Fac> void Clear(MersenneTwisterDSFMT<Fac>&);

  template <unsigned int Fac>
  class MersenneTwisterDSFMT : public Random {

    public:

      typedef MersenneTwisterDSFMT<Fac>   Type;
      typedef Random  ParentType;
      friend void Clear<Fac>(MersenneTwisterDSFMT<Fac>&);

      MersenneTwisterDSFMT() : ParentType(), s(), idx(0) {}
      virtual ~MersenneTwisterDSFMT() { Clear(*this); }

      virtual bool IsValid() const { return s.IsValid(); }
      virtual void Allocate() { Clear(*this); s.Allocate(NStatus); idx=0; }

      virtual void Init(unsigned int seed) {
        unsigned int *p=reinterpret_cast<unsigned int*>(s.Head());
        unsigned int *pend=p+NStatusU32;
        unsigned int r=seed, i=1;
        *p=seed;
        for(;p!=pend;) {
          r=1812433253UL*(r^(r>>30))+(i++);
          *(p++)=r;
        }
        _InitMask();
        _PeriodicCertification();
        idx=N64;
      }
      virtual void Init(const ArrayData<unsigned int>& A) {
        assert(A.IsValid());
        unsigned int *p=reinterpret_cast<unsigned int*>(s.Head());
        memset(reinterpret_cast<char*>(p),0x8B,NStatusByte);
        const unsigned int n=A.Size();
        unsigned int count=(n+1>NStatusU32?n+1:NStatusU32);
        unsigned int tmid=Mid%NStatusU32;
        unsigned int i,j,r;
        r=xSFMTWorkFuncA(p[0]^p[tmid]^p[NStatusU32m1]);
        p[tmid]+=r;
        r+=n;
        p[LagMid%NStatusU32]+=r;
        p[0]=r;
        --count;
        for(i=0,j=0;j<n;++j) {
          tmid=(i+Mid)%NStatusU32;
          r=xSFMTWorkFuncA(p[i]^p[tmid]^p[(i+NStatusU32m1)%NStatusU32]);
          p[tmid]+=r;
          r+=A[j]+i;
          p[(i+LagMid)%NStatusU32]+=r;
          p[i]=r;
          i=(i+1)%NStatusU32;
        }
        for(;j<count;++j) {
          tmid=(i+Mid)%NStatusU32;
          r=xSFMTWorkFuncA(p[i]^p[tmid]^p[(i+NStatusU32m1)%NStatusU32]);
          p[tmid]+=r;
          r+=+i;
          p[(i+LagMid)%NStatusU32]+=r;
          p[i]=r;
          i=(i+1)%NStatusU32;
        }
        for(j=0;j<NStatusU32;++j) {
          tmid=(i+Mid)%NStatusU32;
          r=xSFMTWorkFuncB(p[i]+p[tmid]+p[(i+NStatusU32m1)%NStatusU32]);
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

      double DoubleClose1Open2() {
        double *p=reinterpret_cast<double*>(s.Head());
        if(idx>=N64) { _GenAll(); idx=0; }
        return p[idx++];
      }
      double DoubleOpen0Close1() { return 2.0-DoubleClose1Open2(); }
      double DoubleOpen0Open1() {
        Unique64Bit u;
        Value<double>(u)=DoubleClose1Open2();
        Value<unsigned long long>(u)|=1;
        return Value<double>(u)-1.;
      }
      double DoubleClose0Open1() { return DoubleClose1Open2()-1.; }

      virtual double Double() { return DoubleClose0Open1(); }
      virtual unsigned int UInt() {
        unsigned long long *p=reinterpret_cast<unsigned long long*>(s.Head());
        if(idx>=N64) { _GenAll(); idx=0; }
        return p[idx++]&0xFFFFFFFFU;
      }

      void FastProduceClose1Open2(ArrayData<double>& V) {
        _GenArrayDouble(V,Convert2C1O2);
      }
      void FastProduceClose0Open1(ArrayData<double>& V) {
        _GenArrayDouble(V,Convert2C0O1);
      }
      void FastProduceOpen0Open1(ArrayData<double>& V) {
        _GenArrayDouble(V,Convert2O0O1);
      }
      void FastProduceOpen0Close1(ArrayData<double>& V) {
        _GenArrayDouble(V,Convert2O0C1);
      }

    protected:

      Array<Unique128Bit> s;
      unsigned int idx;

    private:

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
      static const unsigned int SL;
      static const unsigned int Pos;
      static const Unique128Bit Msk;
      static const Unique128Bit Fix;
      static const Unique128Bit Pcv;

      MersenneTwisterDSFMT(const Type&) {}
      Type& operator=(const Type&) { return *this; }

      void _InitMask() {
        unsigned long long *p=reinterpret_cast<unsigned long long*>(s.Head());
        for(unsigned int i=0;i<DualN;++i) p[i]=(p[i]&Low)|Upp;
      }
      void _Recursion(const Unique128Bit& a,const Unique128Bit& b,
                      Unique128Bit& r, Unique128Bit& u) {
#ifdef _HAVE_SSE2_
        __m128i y,z,v,w,ra,rb,rMsk;
        _Copy(ra,a);
        _Copy(rb,b);
        _Copy(rMsk,Msk);
        z=_mm_slli_epi64(Value<__m128i>(a),SL);
        y=_mm_shuffle_epi32(Value<__m128i>(u),0x1BU);
        z=_mm_xor_si128(z,rb);
        y=_mm_xor_si128(y,z);
        v=_mm_srli_epi64(y,SR);
        w=_mm_and_si128(y,rMsk);
        v=_mm_xor_si128(v,ta);
        v=_mm_xor_si128(v,w);
        r.Copy(v);
        u.Copy(y);
#else
        unsigned long long uv0,uv1;
        uv0=(Value<unsigned long long>(a,0)<<SL)^
            (Value<unsigned long long>(u,1)>>32)^
            (Value<unsigned long long>(u,1)<<32)^
            Value<unsigned long long>(b,0);
        uv1=(Value<unsigned long long>(a,1)<<SL)^
            (Value<unsigned long long>(u,0)>>32)^
            (Value<unsigned long long>(u,0)<<32)^
            Value<unsigned long long>(b,1);
        Value<unsigned long long>(u,0)=uv0;
        Value<unsigned long long>(u,1)=uv1;
        Value<unsigned long long>(r,0)=(uv0>>SR)^
                                       (uv0&Value<unsigned long long>(Msk,0))^
                                       Value<unsigned long long>(a,0);
        Value<unsigned long long>(r,1)=(uv1>>SR)^
                                       (uv1&Value<unsigned long long>(Msk,1))^
                                       Value<unsigned long long>(a,1);
#endif
      }
      void _PeriodicCertification() {
        Unique128Bit iU;
#ifdef _HAVE_SSE2_
        __m128i tmp,tmp1;
        _Copy(tmp,s[N]);
        _Copy(tmp1,Fix);
        tmp=_mm_xor_si128(tmp,tmp1);
        _Copy(tmp1,Pcv);
        tmp=_mm_and_si128(tmp,tmp1);
        iU.Copy(tmp);
#else
        Value<unsigned long long>(iU,0)=Value<unsigned long long>(s[N],0)^
                                        Value<unsigned long long>(Fix,0);
        Value<unsigned long long>(iU,1)=Value<unsigned long long>(s[N],1)^
                                        Value<unsigned long long>(Fix,1);
        Value<unsigned long long>(iU,0)&=Value<unsigned long long>(Pcv,0);
        Value<unsigned long long>(iU,1)&=Value<unsigned long long>(Pcv,1);
#endif
        unsigned long long inner=Value<unsigned long long>(iU,0)^
                                 Value<unsigned long long>(iU,1);
        for(unsigned int i=32;i>0;i>>=1)  inner^=(inner>>i);
        inner&=1;
        if(inner!=1)  Value<unsigned long long>(s[N],1)^=1ULL;
      }

      void _GenAll() {
        unsigned int i;
        Unique128Bit lung;
        lung.Copy(s[N]);
        for(i=0;i<N-Pos;++i) _Recursion(s[i],s[i+Pos],s[i],lung);
        for(;i<N;++i) _Recursion(s[i],s[i+Pos-N],s[i],lung);
        s[N].Copy(lung);
      }

      typedef void (*CvFuncType)(Unique128Bit&);

      void Convert2C1O2(Unique128Bit&) {}
#ifdef _HAVE_SSE2_
      static const Unique128Bit SSE2DoubleTwo;
      static const Unique128Bit SSE2DoubleNOne;
      static const Unique128Bit SSE2UIntOne;
      void Convert2C0O1(Unique128Bit& w) {
        __mm128d u,v;
        _Copy(u,w);
        _Copy(v,SSE2DoubleNOne);
        w.Copy(_mm_add_pd(u,v));
      }
      void Conert2O0C1(Unique128Bit& w) {
        __mm128d u,v;
        _Copy(u,SSE2DoubleTwo);
        _Copy(v,w);
        w.Copy(_mm_sub_pd(u,v));
      }
      void Convert2O0O1(Unique128Bit& w) {
        __m128i u,v;
        _Copy(u,w);
        _Copy(v,SSE2UIntOne);
        w.Copy(_mm_or_si128(u,v));
        Convert2C0O1(w);
      }
#else
      void Conver2C0O1(Unique128Bit& w) {
        Value<double>(w,0)-=1.; Value<double>(w,1)-=1.;
      }
      void Convert2O0C1(Unique128Bit& w) {
        Value<double>(w,0)=2.-Value<double>(w,0);
        Value<double>(w,1)=2.-Value<double>(w,1);
      }
      void Convert2O0O1(Unique128Bit& w) {
        Value<unsigned long long>(w,0)|=1;
        Value<unsigned long long>(w,1)|=1;
        Convert2C0O1(w);
      }
#endif

      void _GenArray(Unique128Bit* V, unsigned int n, CvFuncType Cv) {
        assert(n>=N64);
        unsigned int i,j;
        Unique128Bit lung;
        lung.Copy(s[N]);
        for(i=0;i<N-Pos;++i) _Recursion(s[i],s[i+Pos],v[i],lung);
        for(;i<N;++i) _Recursion(s[i],V[i+Pos-N],V[i],lung);
        for(;i+N<n;++i) {
          _Recursion(V[i-N],V[i+Pos-N],V[i],lung);
          Cv(V[i-N]);
        }
        for(j=0;j+n<DualN;++j)  s[j].Copy(V[j+n-N]);
        for(;i<n;++i,++j) {
          _Recursion(V[i-N],V[i+Pos-N],V[i],lung);
          s[j].Copy(V[i]);
          Cv(V[i-N]);
        }
        for(i=n-N;i<n;++i)  Cv(V[i]);
        s[N].Copy(lung);
      }
      void _GenArrayDouble(ArrayData<double>& V, CvFuncType Cv) {
        assert(V.IsValid());
        assert((V.Size()&1)==0);
        _GenArray(reinterpret_cast<Unique128Bit*>(V.Head()),n>>1,Cv);
      }

  };

  template <unsigned int Fac>
  void Clear(MersenneTwisterDSFMT<Fac>& R) {
    Clear(R.s);
    R.idx=0;
    typedef typename MersenneTwisterDSFMT<Fac>::ParentType PType;
    Clear(static_cast<PType&>(R));
  }

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::N=(Fac-128)/104+1;

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::DualN=
    MersenneTwisterDSFMT<Fac>::N*2;

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::NStatus=
    MersenneTwisterDSFMT<Fac>::N+1;

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::NStatusU32=
    MersenneTwisterDSFMT<Fac>::NStatus*4;

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::NStatusU32m1=
    MersenneTwisterDSFMT<Fac>::NStatusU32-1;

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::NStatusByte=
    MersenneTwisterDSFMT<Fac>::NStatus*16;

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::Lag=
    (MersenneTwisterDSFMT<Fac>::NStatusU32>623?11:
    (MersenneTwisterDSFMT<Fac>::NStatusU32>68? 7:
    (MersenneTwisterDSFMT<Fac>::NStatusU32>39? 5:3)));

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::Mid=
    (MersenneTwisterDSFMT<Fac>::NStatusU32-MersenneTwisterDSFMT<Fac>::Lag)/2;

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::LagMid=
    MersenneTwisterDSFMT<Fac>::Lag+MersenneTwisterDSFMT<Fac>::Mid;

  template <unsigned int Fac>
  const unsigned int MersenneTwisterDSFMT<Fac>::N64=
    MersenneTwisterDSFMT<Fac>::DualN;

  template <unsigned int Fac>
  const unsigned long long MersenneTwisterDSFMT<Fac>::Low=
    0x000FFFFFFFFFFFFFULL;

  template <unsigned int Fac>
  const unsigned long long MersenneTwisterDSFMT<Fac>::Upp=
    0x3FF0000000000000ULL;

#ifdef _HAVE_SSE2_

  template <unsigned int Fac>
  const Unique128Bit MersenneTwisterDSFMT<Fac>::SSE2DoubleTwo(2.,2.);

  template <unsigned int Fac>
  const Unique128Bit MersenneTwisterDSFMT<Fac>::SSE2DoubleNOne(-1.,-1.);

  template <unsigned int Fac>
  const Unique128Bit MersenneTwisterDSFMT<Fac>::SSE2UIntOne(1ULL,1ULL);

#endif

}

#endif

