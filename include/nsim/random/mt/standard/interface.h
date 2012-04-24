
#ifndef _Random_MT_Standard_Interface_H_
#define _Random_MT_Standard_Interface_H_

#include "random/mt/interface.h"
#include "random/base/interface.h"
#include "unique/64bit/interface.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <unsigned int Fac>
  struct MersenneTwister<StandardMT,Fac> : public RandomBase {

    public:

      typedef MersenneTwister<StandardMT,Fac>   Type;
      typedef RandomBase  ParentType;

      static const unsigned int N;
      static const unsigned int M;
      static const unsigned int dNM;
      static const unsigned int NmOne;
      static const unsigned int MmOne;
      static const unsigned int Upp;
      static const unsigned int Low;
      static const Unique64Bit  Mag;
      static const unsigned int Mask32Bit;

      Array1D<unsigned int> s;
      unsigned int sloc;

      MersenneTwister() : ParentType(), s(), sloc(0) { assert(Fac==0); }
      ~MersenneTwister() { Clear(*this); }

      bool IsValid() const { return s.IsValid(); }

      void Allocate() { Clear(*this); s.Allocate(N); sloc=0; }

      virtual void Init(unsigned int seed) {
        BlasFill(s,0U,N);
        s[0]=seed&Mask32Bit;
        unsigned int r=s[0];
        for(sloc=1;sloc<N;) {
          r=(1812433253UL*(r^(r>>30))+sloc)&Mask32Bit;
          s[sloc++]=r;
        }
        sloc=1;
      }

      void Init(const Array1D<unsigned int>& V,unsigned int n) {
        assert(n<=V.Size());
        Init(19650218UL);
        unsigned int i,j,k,r;
        i=1; j=0; k=(n<N?N:n);
        r=s[0];
        for(;k;--k) {
          r=((s[i]^((r^(r>>30))*1664525UL))+V[j]+(j++))&Mask32Bit;
          s[i++]=r;
          if(i>=N)  { s[0]=r; i=1; }
          if(j>=n)  j=0;  
        }
        for(k=NmOne;k;--k) {
          r=((s[i]^((r^(r>>30))*1566083941UL))-i)&Mask32Bit;
          s[i++]=r;
          if(i>=N)  { s[0]=r; i=1; }
        }
        s[0]=Upp;
        sloc=1;
      }

      virtual unsigned int UInt() {
        unsigned int u;
        if(sloc>=N) {
          unsigned int k;
          for(k=0;k<dNM;++k) {
            u=(s[k]&Upp)|(s[k+1]&Low);
            s[k]=s[k+M]^(u>>1)^Mag.uv[u&0x1UL];
          }
          for(;k<NmOne;++k) {
            u=(s[k]&Upp)|(s[k+1]&Low);
            s[k]=s[k-dNM]^(u>>1)^Mag.uv[u&0x1UL];
          }
          u=(s[NmOne]&Upp)|(s[0]&Low);
          s[NmOne]=s[MmOne]^(u>>1)^Mag.uv[u&0x1UL];
          sloc=0;
        }
        u=s[sloc++];
        u^=(u>>11);
        u^=(u<<7)&0x9D2C5680UL;
        u^=(u<<15)&0xEFC60000UL;
        u^=(u>>18);
        return u;
      }
      virtual double Double() {
        long x,y;
        x=static_cast<long>(UInt()>>5);
        y=static_cast<long>(UInt()>>6);
        return (x*67108864.+y)*(1./9007199254740992.);
      }

      double DoubleClose0Close1() {
        int i=static_cast<int>(UInt());
        return static_cast<double>(i)*(1./4294967295.)+(0.5+0.5/4294967295.);
      }
      double DoubleClose0Open1() {
        int i=static_cast<int>(UInt());
        return static_cast<double>(i)*(1./4294967296.)+0.5;
      }
      double DoubleOpen0Open1() {
        int i=static_cast<int>(UInt());
        return static_cast<double>(i)*(1./4294967296.)+(0.5+0.5/4294967296.);
      }
      double Double53BitSlow() {
        unsigned int x,y;
        x=UInt();
        y=UInt();
        return (static_cast<double>(x)*67108864.+static_cast<double>(y))*
               (1./9007199254740992.);
      }
      long double Double63BitSlow() {
        unsigned int x,y;
        x=UInt();
        y=UInt();
        return
          static_cast<long double>(x|static_cast<unsigned long long>(y)<<32)*
          (1./18446744073709551616.0L);
      }

    private:

      MersenneTwister(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <unsigned int Fac>
  void Clear(MersenneTwister<StandardMT,Fac>& R) { Clear(R.s); R.sloc=0; }

  template <unsigned int Fac>
  const unsigned int MersenneTwister<StandardMT,Fac>::N=624;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<StandardMT,Fac>::M=397;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<StandardMT,Fac>::dNM=
    MersenneTwister<StandardMT,Fac>::N-MersenneTwister<StandardMT,Fac>::M;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<StandardMT,Fac>::NmOne=
    MersenneTwister<StandardMT,Fac>::N-1;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<StandardMT,Fac>::MmOne=
    MersenneTwister<StandardMT,Fac>::M-1;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<StandardMT,Fac>::Upp=0x80000000UL;

  template <unsigned int Fac>
  const unsigned int MersenneTwister<StandardMT,Fac>::Low=0x7FFFFFFFUL;

  template <unsigned int Fac>
  const Unique64Bit MersenneTwister<StandardMT,Fac>::Mag(0x000000009908B0DFULL);

  template <unsigned int Fac>
  const unsigned int MersenneTwister<StandardMT,Fac>::Mask32Bit=0xfFFFFFFFUL;

}

#endif

