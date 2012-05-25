
#ifndef _Random_MT_Standard_Interface_H_
#define _Random_MT_Standard_Interface_H_

#include "unique/64bit/interface.h"
#include "array/interface.h"

namespace mysimulator {

  class MersenneTwisterStandard {

    public:

      typedef MersenneTwisterStandard  Type;
      friend void Clear(MersenneTwisterStandard&);

      static const unsigned int N;
      static const unsigned int M;
      static const unsigned int dMN;
      static const unsigned int NmOne;
      static const unsigned int MmOne;
      static const unsigned int Upp;
      static const unsigned int Low;
      static const Unique64Bit  Mag;
      static const unsigned int Mask32;
      static const double dDouble53;
      static const long double dLDouble63;
      static const double dUInt32;
      static const double dUInt32M1;
      static const double dHalfUInt32;
      static const double dHalfUInt32M1;

      MersenneTwisterStandard() : s(), sloc(0) {}
      ~MersenneTwisterStandard() { Clear(*this); }

      bool IsValid() const { return s.IsValid(); }
      void Allocate() { if(!IsValid()) s.Allocate(N); sloc=0; }

      void Init(unsigned int seed) {
        s[0]=seed;
        unsigned int r=s[0]&Mask32;
        for(sloc=1;sloc<N;) {
          r=(1812433253UL*(r^(r>>30))+sloc)&Mask32;
          s[sloc++]=r;
        }
        sloc=1;
      }
      void Init(const ArrayData<unsigned int>& v) {
        Init(19650218UL);
        unsigned int i,j,k,r;
        i=1;  j=0;  k=(v.Size()<N?N:v.Size());
        r=s[0];
        for(;k;--k) {
          r=((s[i]^((r^(r>>30))*1664525UL))+v[j]+(j++))&Mask32;
          s[i++]=r;
          if(i==N)  i=1;
          if(j==N)  j=0;
        }
        for(k=NmOne;k;--k) {
          r=((s[i]^((r^(r>>30))*1566083941UL))-i)&Mask32;
          s[i++]=r;
          if(i==N)  i=1;
        }
        s[0]=Upp;
        sloc=1;
      }

      unsigned int UInt() {
        unsigned int u;
        if(sloc>=N) {
          unsigned int k;
          for(k=0;k<dMN;++k) {
            u=(s[k]&Upp)|(s[k+1]&Low);
            s[k]=s[k+M]^(u>>1)^Value<unsigned int>(Mag,u&1);
          }
          for(;k<NmOne;++k) {
            u=(s[k]&Upp)|(s[k+1]&Low);
            s[k]=s[k-dMN]^(u>>1)^Value<unsigned int>(Mag,u&1);
          }
          u=(s[NmOne]&Upp)|(s[0]&Low);
          s[NmOne]=s[MmOne]^(u>>1)^Value<unsigned int>(Mag.u&1);
          sloc=0;
        }
        u=s[sloc++];
        u^=(u>>11);
        u^=(u<<7)&0x9D2C5680UL;
        u^=(u<<15)&0xEFC60000UL;
        u^=(u>>18);
        return u;
      }
      double Double() {
        long x=(UInt()>>5);
        long y=(UInt()>>6);
        return (x*67108864.+y)*dDouble53;
      }

      double DoubleClose0Close1() {
        return static_cast<int>(UInt())*dUInt32M1+dHalfUInt32M1;
      }
      double DoubleClose0Open1() {
        return static_cast<int>(UInt())*dUInt32+0.5;
      }
      double DoubleOpen0Open1() {
        return static_cast<int>(UInt())*dUInt32+dHalfUInt32;
      }
      long double LDouble63Bit() {
        return (x|static_cast<unsigned long long>(y)<<32)*dLDouble63;
      }

    protected:

      array<unsigned int> s;
      unsigned int sloc;

    private:

      MersenneTwisterStandard(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  const unsigned int MersenneTwisterStandard::N=624;
  const unsigned int MersenneTwisterStandard::M=397;
  const unsigned int MersenneTwisterStandard::dMN=
    MersenneTwisterStandard::N-MersenneTwisterStandard::M;
  const unsigned int MersenneTwisterStandard::NmOne=
    MersenneTwisterStandard::N-1;
  const unsigned int MersenneTwisterStandard::MmOne=
    MersenneTwisterStandard::M-1;
  const unsigned int MersenneTwisterStandard::Upp=0x80000000UL;
  const unsigned int MersenneTwisterStandard::Low=0x7FFFFFFFUL;
  const unsigned int MersenneTwisterStandard::Mag(0x000000009908B0DFULL);
  const unsigned int MersenneTwisterStandard::Mask32=0xFFFFFFFFUL;
  const double MersenneTwisterStandard::dDouble53=1./9007199254740992.;
  const long double MersenneTwisterStandard::dLDouble63=
    1./18446744073709551616.0L;
  const double MersenneTwisterStandard::dUInt32=1./4294967296.;
  const double MersenneTwisterStandard::dUInt32M1=1./4294967295.;
  const double MersenneTwisterStandard::dHalfUInt32=
    0.5+0.5*MersenneTwisterStandard::dUInt32;
  const double MersenneTwisterStandard::dHalfUInt32M1=
    0.5+0.5*MersenneTwisterStandard::dUInt32M1;

  void Clear(MersenneTwisterStandard& R) { Clear(R.s); R.sloc=0; }

}

#endif

