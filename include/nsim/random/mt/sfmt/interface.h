
#ifndef _Random_MT_SFMT_Interface_H_
#define _Random_MT_SFMT_Interface_H_

#include "random/mt/interface.h"
#include "random/base/interface.h"
#include "random/mt/sfmt/module/init-func.h"
#include "unique/128bit/fill.h"

namespace mysimulator {

  template <unsigned int Fac>
  struct MersenneTwister<SFMT,Fac> : public RandomBase {

    public:

      typedef MersenneTwister<SFMT,Fac>   Type;
      typedef RandomBase  ParentType;

      static const unsigned int N;
      static const unsigned int NByte;
      static const unsigned int N32;
      static const unsigned int N32m1;
      static const unsigned int N64;
      static const unsigned int Lag;
      static const unsigned int Mid;
      static const unsigned int LagMid;
      static const unsigned int Pos;
      static const unsigned int NmPos;
      static const unsigned int SL1;
      static const unsigned int SL2;
      static const unsigned int SR1;
      static const unsigned int SR2;
      static const Unique128Bit Msk;
      static const Unique128Bit Pty;

      Array1D<Unique128Bit> s;
      unsigned int idx;
      Unique128Bit _u;

      MersenneTwister() : ParentType(), s(), idx(0), _u() {}
      ~MersenneTwister() { Clear(*this); }

      bool IsValid() const { return s.IsValid(); }

      void Allocate() {
        Clear(*this);
        s.Allocate(N);
        idx=0;

      void _PeriodCertification() {
        unsigned int inner=0;
        unsigned int *p=reinterpret_cast<unsigned int*>(s._data);
        inner^=p[0]&Pty.uv[0];
        inner^=p[1]&Pty.uv[1];
        inner^=p[2]&Pty.uv[2];
        inner^=p[3]&Pty.uv[3];
        for(unsigned int i=16;i>0;i>>=1)  inner^=inner>>i;
        inner&=1;
        if(inner==1)  return;
        for(unsigned int i=0,work=1;i<4;++i)
        for(unsigned int j=0;j<32;++j) {
          if((work&Pty.uv[i])!=0) { p[i]^=work; return; }
          work<<=1;
        }
      }

      void _RShift(Unique128Bit& out,const Unique128Bit& in,int shift) {
        unsigned int shift8=(shift<<3);
        out.ullv[1]=in.ullv[1]>>shift8;
        out.ullv[0]=in.ullv[0]>>shift8;
        out.ullv[0]|=in.ullv[0]<<(64-shift8);
      }
      void _LShift(Unique128Bit& out,const Unique128Bit& in,int shift) {
        unsigned int shift8=(shift<<3);
        out.ullv[1]=in.ullv[1]<<shift8;
        out.ullv[0]=in.ullv[0]<<shift8;
        out.ullv[0]|=in.ullv[0]>>(64-shift8);
      }

      const Unique128Bit&
      _Recursion(const Unique128Bit& a,const Unique128Bit& b,
                 const Unique128Bit& c,const Unique128Bit& d) {
        Unique128Bit x,y;
#ifdef _HAVE_SSE2
        Unique128Bit v,u;
        y.si=_mm_srli_epi32(_mm_loadu_si128(&(b.si)),SR1);
        u.si=_mm_srli_si128(_mm_loadu_si128(&(c.si)),SR2);
        v.si=_mm_slli_epi32(_mm_loadu_si128(&(d.si)),SL1);
        x.si=_mm_slli_si128(_mm_loadu_si128(&(a.si)),SL2);
        u.si=_mm_xor_si128(u.si,_mm_loadu_si128(&(a.si)));
        y.si=_mm_and_si128(y.si,_mm_loadu_si128(&(Msk.si)));
        u.si=_mm_xor_si128(u.si,x.si);
        u.si=_mm_xor_si128(u.si,y.si);
        Copy(_u,u);
#else
        _LShift(x,a,SL2);
        _RShift(y,c,SR2);
        _u.uv[0]
          =a.uv[0]^x.uv[0]^((b.u[0]>>SR1)&Msk.uv[0])^y.uv[0]^(d.uv[0]<<SL1);
        _u.uv[1]
          =a.uv[1]^x.uv[1]^((b.u[1]>>SR1)&Msk.uv[1])^y.uv[1]^(d.uv[1]<<SL1);
        _u.uv[2]
          =a.uv[2]^x.uv[2]^((b.u[2]>>SR1)&Msk.uv[2])^y.uv[2]^(d.uv[2]<<SL1);
        _u.uv[3]
          =a.uv[3]^x.uv[3]^((b.u[3]>>SR1)&Msk.uv[3])^y.uv[3]^(d.uv[3]<<SL1);
#endif
        return _u;
      }

      virtual void Init(unsigned int seed) {
        unsigned int *p=reinterpret_cast<unsigned int*>(s._data);
        unsigned int work;
        p[0]=seed;
        work=*p;
        for(unsigned int i=1;i<N32;++i) {
          work=1812433253UL*(work^(work>>30))+i;
          p[i]=work;
        }
        idx=N32;
        _PeriodCertification();
      }

      void Init(const Array1D<unsigned int>& Key,unsigned int len) {
        unsigned int i,j,r,count,tmid;
        unsigned int *p=reinterpret_cast<unsigned int*>(s._data);
        memset(s._data,0x8B,NByte);
        count=(len>N32m1?len+1:N32);
        r=_SFMTInitFuncA(p[0]^p[Mid]^p[N32m1]);
        p[Mid]+=r;
        r+=len;
        p[LagMid]+=r;
        p[0]=r;
        --count;
        for(i=1,j=0;j<len;++j) {
          tmid=(i+Mid)%N32;
          r=_SFMTInitFuncA(p[i]^p[tmid]^p[(i+N32m1)%N32]);
          p[tmid]+=r;
          r+=key[j]+i;
          p[(i+LagMid)%N32]+=r;
          p[i]=r;
          ++i;
          if(i>=N32)  i-=N32;
        }
        for(;j<count;++j) {
          tmid=(i+Mid)%N32;
          r=_SFMTInitFuncA(p[i]^p[tmid]^p[(i+N32m1)%N32]);
          p[tmid]+=r;
          r+=i;
          p[(i+LagMid)%N32]+=r;
          p[i]=r;
          ++i;
          if(i>=N32)  i-=N32;
        }
        for(j=0;j<N32;++j) {
          tmid=(i+Mid)%N32;
          r=_SFMTInitFuncB(p[i]+p[tmid]+p[(i+N32m1)%N32]);
          p[tmid]^=r;
          r-=i;
          p[(i+LagMid)%N32]^=r;
          p[i]=r;
          ++i;
          if(i>=N32)  i-=N32;
        }
        idx=N32;
        _PeriodCertification();
      }

      void _GenAll() {
        unsigned int i;
        Unique128Bit r1,r2;
        Copy(r1,s[N-2]);
        Copy(r2,s[N-1]);
        for(i=0;i<N-POs;++i) {
          Copy(s[i],_Recursion(s[i],s[i+Pos],r1,r2));
          Copy(r1,r2);
          Copy(r2,s[i]);
        }
        for(;i<N;++i) {
          Copy(s[i],_Recursion(s[i],s[i-NmPos],r1,r2));
          Copy(r1,r2);
          Copy(r2,s[i]);
        }
        idx=0;
      }
      void _GenArray(Array1D<Unique128Bit>& array,unsigned int size) {
        assert(idx==N32);
        assert(size>=N);
        unsigned int i,j;
        Unique128Bit r1,r2;
        Copy(r1,s[N-2]);
        Copy(r2,s[N-1]);
        for(unsigned int i=0;i<Pos;++i) {
          Copy(array[i],_Recursion(s[i],s[i+Pos],r1,r2));
          Copy(r1,r2);
          Copy(r2,array[i]);
        }
        for(;i<N;++i) {
          Copy(array[i],_Recursion(s[i],array[i-NmPos],r1,r2));
          Copy(r1,r2);
          Copy(r2,array[i]);
        }
        for(;i+N<size;++i) {
          Copy(array[i],_Recursion(array[i-N],array[i-NmPos],r1,r2));
          Copy(r1,r2);
          Copy(r2,array[i]);
        }
        for(j=0;j+size<N+N;++j)   Copy(s[j],array[j+size-N]);
        for(;i<size;++i) {
          Copy(array[i],_Recursion(array[i-N],array[i-NmPos],r1,r2));
          Copy(s[j++],array[i]);
          Copy(r1,r2);
          Copy(r2,array[i]);
        }
        idx=N32;
      }

      virtual unsigned int UInt() {
        if(idx>=N32)  _GenAll();
        return *(reinterpret_cast<unsigned int*>(s._data)+(idx++));
      }
      unsigned long long ULLInt() {
        assert((idx&1)==0);
        if(idx>=N32)  _GenAll();
        unsigned long long ll;
        ll=*(reinterpret_cast<unsigned long long*>(s._data)+(idx>>1));
        idx+=2;
        return ll;
      }
      virtual double Double() {
        long x=static_cast<long>(UInt()>>5);
        long y=static_cast<long>(UInt()>>6);
        return (x*67108864.0+y)*(1./9007199254740992.0);
      }
      long double LDouble() {
        return static_cast<long double>(static_cast<long long>(ULLInt()))*
               (1./18446744073709551616.0L)+0.5;
      }

      double DoubleClose0Close1() {
        return static_cast<double>(static_cast<int>(UInt()))*
               (1./4294967295.0)+(0.5+0.5/4294967295.0);
      }
      double DoubleClose0Open1() {
        return static_cast<double>(static_cast<int>(UInt()))*
               (1./4294967296.0)+0.5;
      }
      double DoubleOpen0Open1() {
        return static_cast<double>(static_cast<int>(UInt()))*
               (1./4294967296.0)+(0.5+0.5/4294967296.0);
      }

      double Double53BitSlow() {
        return (UInt()*67108864.0+y)/(1./9007199254740992.0);
      }
      long double LDouble63BitSlow() {
        return (UInt()|(static_cast<unsigned long long>(UInt())<<32))*
               (1./18446744073709551616.0L);
      }

      void FastFill(Array1D<unsigned int>& array,unsigned int size) {
        assert(size%4==0);
        assert(size>=N32);
        _GenArray(reinterpret_cast<Unique128Bit*>(array._data),size>>2);
      }

    private:

      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <unsigned int Fac>
  void Clear(MersenneTwister<SFMT,Fac>& R) {
    Clear(R.s); R.idx=0; Fill(R._u,0);
  }

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::N=Fac/128+1;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::NByte=
      MersenneTwister<SFMT,Fac>::N*16;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::N32=
      MersenneTwister<SFMT,Fac>::N*4;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::N32m1=
      MersenneTwister<SFMT,Fac>::N32-1;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::N64=
      MersenneTwister<SFMT,Fac>::N*2;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::Lag=
      (MersenneTwister<SFMT,Fac>::N32>=623?11:
      (MersenneTwister<SFMT,Fac>::N32>=68?7:
      (MersenneTwister<SFMT,Fac>::N32>=39?5:3)));

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::Mid=
      (MersenneTwister<SFMT,Fac>::N-MersenneTwister<SFMT,Fac>::Lag)/2;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::LagMid=
      MersenneTwister<SFMT,Fac>::Lag+MersenneTwister<SFMT,Fac>::Mid;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::Pos=0;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::SL1=0;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::SL2=0;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::SR1=0;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::SR2=0;

  template <unsigned int Fac>
  const Unique128Bit MersenneTwister<SFMT,Fac>::Msk(0ULL,0ULL);

  template <unsigned int Fac>
  const Unique128Bit MersenneTwister<SFMT,Fac>::Pty(0ULL,0ULL);

  template <unsigned int Fac>
  const unsigned int MersenneTwister<SFMT,Fac>::NmPos=
      MersenneTwister<SFMT,Fac>::N-MersenneTwister<SFMT,Fac>::Pos;

  template <> const unsigned int MersenneTwister<SFMT,607>::Pos=2;
  template <> const unsigned int MersenneTwister<SFMT,607>::SL1=15;
  template <> const unsigned int MersenneTwister<SFMT,607>::SL2=3;
  template <> const unsigned int MersenneTwister<SFMT,607>::SR1=13;
  template <> const unsigned int MersenneTwister<SFMT,607>::SR2=3;
  template <> const Unique128Bit
  MersenneTwister<SFMT,607>::Msk(0xFDFF37FFEF7F3F7DULL,0xFF777B7D7FF7FB2FULL);
  template <> const Unique128Bit
  MersenneTwister<SFMT,607>::Pty(0x0000000100000000ULL,0x000000005986F054ULL);

  template <> const unsigned int MersenneTwister<SFMT,1279>::Pos=7;
  template <> const unsigned int MersenneTwister<SFMT,1279>::SL1=14;
  template <> const unsigned int MersenneTwister<SFMT,1279>::SL2=3;
  template <> const unsigned int MersenneTwister<SFMT,1279>::SR1=5;
  template <> const unsigned int MersenneTwister<SFMT,1279>::SR2=1;
  template <> const Unique128Bit
  MersenneTwister<SFMT,1279>::Msk(0xF7FFEF7F7FEFCFFFULL,0xAFF3EF3FB5FFFF7FULL);
  template <> const Unique128Bit
  MersenneTwister<SFMT,1279>::Pty(0x0000000100000000ULL,0x0000000020000000ULL);

  template <> const unsigned int MersenneTwister<SFMT,11213>::Pos=68;
  template <> const unsigned int MersenneTwister<SFMT,11213>::SL1=14;
  template <> const unsigned int MersenneTwister<SFMT,11213>::SL2=3;
  template <> const unsigned int MersenneTwister<SFMT,11213>::SR1=7;
  template <> const unsigned int MersenneTwister<SFMT,11213>::SR2=3;
  template <> const Unique128Bit
  MersenneTwister<SFMT,11213>::Msk(0xEFFFF7F8FFFFFFEFULL,0xDFDFBFFF7FFFDBFDULL);
  template <> const Unique128Bit
  MersenneTwister<SFMT,11213>::Pty(0x0000000100000000ULL,0xE8148000D0C7AFA3ULL);

  template <> const unsigned int MersenneTwister<SFMT,19937>::Pos=122;
  template <> const unsigned int MersenneTwister<SFMT,19937>::SL1=18;
  template <> const unsigned int MersenneTwister<SFMT,19937>::SL2=1;
  template <> const unsigned int MersenneTwister<SFMT,19937>::SR1=11;
  template <> const unsigned int MersenneTwister<SFMT,19937>::SR2=1;
  template <> const Unique128Bit
  MersenneTwister<SFMT,19937>::Msk(0xDFFFFFEFDDFECB7FULL,0xBFFAFFFFBFFFFFF6ULL);
  template <> const Unique128Bit
  MersenneTwister<SFMT,19937>::Pty(0x0000000100000000ULL,0x0000000013C9E684ULL);

  template <> const unsigned int MersenneTwister<SFMT,132049>::Pos=110;
  template <> const unsigned int MersenneTwister<SFMT,132049>::SL1=19;
  template <> const unsigned int MersenneTwister<SFMT,132049>::SL2=1;
  template <> const unsigned int MersenneTwister<SFMT,132049>::SR1=21;
  template <> const unsigned int MersenneTwister<SFMT,132049>::SR2=1;
  template <> const Unique128Bit MersenneTwister<SFMT,132049>::Msk(
      0xFFFFBB5FFB6EBF95ULL,0xFFFEFFFACFF77FFFULL);
  template <> const Unique128Bit MersenneTwister<SFMT,132049>::Pty(
      0x0000000100000000ULL,0xCB520000C7E91C7DULL);

  template <> const unsigned int MersenneTwister<SFMT,216091>::Pos=627;
  template <> const unsigned int MersenneTwister<SFMT,216091>::SL1=11;
  template <> const unsigned int MersenneTwister<SFMT,216091>::SL2=3;
  template <> const unsigned int MersenneTwister<SFMT,216091>::SR1=10;
  template <> const unsigned int MersenneTwister<SFMT,216091>::SR2=1;
  template <> const Unique128Bit MersenneTwister<SFMT,216091>::Msk(
      0xBFF7BFF7BFFFFFFFULL,0xBFFFFA7FFFDDFBFBULL);
  template <> const Unique128Bit MersenneTwister<SFMT,216091>::Pty(
      0xF800000189E80709ULL,0x3BD2B64B0C64B1E4ULL);

  template <> const unsigned int MersenneTwister<SFMT,2281>::Pos=12;
  template <> const unsigned int MersenneTwister<SFMT,2281>::SL1=19;
  template <> const unsigned int MersenneTwister<SFMT,2281>::SL2=1;
  template <> const unsigned int MersenneTwister<SFMT,2281>::SR1=5;
  template <> const unsigned int MersenneTwister<SFMT,2281>::SR2=1;
  template <> const Unique128Bit
  MersenneTwister<SFMT,2281>::Msk(0xBFF7FFBFFDFFFFFEULL,0xF7FFEF7FF2F7CBBFULL);
  template <> const Unique128Bit
  MersenneTwister<SFMT,2281>::Pty(0x0000000100000000ULL,0x0000000041DFA600ULL);

  template <> const unsigned int MersenneTwister<SFMT,4253>::Pos=17;
  template <> const unsigned int MersenneTwister<SFMT,4253>::SL1=20;
  template <> const unsigned int MersenneTwister<SFMT,4253>::SL2=1;
  template <> const unsigned int MersenneTwister<SFMT,4253>::SR1=7;
  template <> const unsigned int MersenneTwister<SFMT,4253>::SR2=1;
  template <> const Unique128Bit
  MersenneTwister<SFMT,4253>::Msk(0x9F7BFFFF9FFFFF5FULL,0x3EFFFFFBFFFFF7BBULL);
  template <> const Unique128Bit
  MersenneTwister<SFMT,4253>::Pty(0x00000001AF5390A3ULL,0xB740B3F86C11486DULL);

  template <> const unsigned int MersenneTwister<SFMT,44497>::Pos=330;
  template <> const unsigned int MersenneTwister<SFMT,44497>::SL1=5;
  template <> const unsigned int MersenneTwister<SFMT,44497>::SL2=3;
  template <> const unsigned int MersenneTwister<SFMT,44497>::SR1=9;
  template <> const unsigned int MersenneTwister<SFMT,44497>::SR2=3;
  template <> const Unique128Bit
  MersenneTwister<SFMT,44497>::Msk(0xEFFFFFFBDFBEBFFFULL,0xBFBF7BEF9FFD7BFFULL);
  template <> const Unique128Bit
  MersenneTwister<SFMT,44497>::Pty(0x0000000100000000ULL,0xA3AC4000ECC1327AULL);

  template <> const unsigned int MersenneTwister<SFMT,86243>::Pos=366;
  template <> const unsigned int MersenneTwister<SFMT,86243>::SL1=6;
  template <> const unsigned int MersenneTwister<SFMT,86243>::SL2=7;
  template <> const unsigned int MersenneTwister<SFMT,86243>::SR1=19;
  template <> const unsigned int MersenneTwister<SFMT,86243>::SR2=1;
  template <> const Unique128Bit
  MersenneTwister<SFMT,86243>::Msk(0xFDBFFBFFBFF7FF3FULL,0xFD77EFFFBF9FF3FFULL);
  template <> const Unique128Bit
  MersenneTwister<SFMT,86243>::Pty(0x0000000100000000ULL,0x00000000E9528D85ULL);

}

#endif

