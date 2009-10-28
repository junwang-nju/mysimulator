
#ifndef _Random_Generator_MT_Standard_H_
#define _Random_Generator_MT_Standard_H_

#include "type.h"

namespace std {

  class MT_Standard {

    private:

      static const uint32_t N;

      static const uint32_t M;

      static const uint32_t MatrixA;

      static const uint32_t UppMask;

      static const uint32_t LowMask;

      static const uint32_t mag01[2];

      uint32_t mt[624];

      int mti, kk;

      uint32_t oui;

      int oi;

      double od;

      long double old;

    public:

      MT_Standard() {}

      MT_Standard(const uint32_t& seed) : mti(N+1) { Init(seed); }

      MT_Standard(const MT_Standard& rng) { assert(false); }

      void Init(const uint32_t& seed) {
        mt[0]=seed&0xFFFFFFFFUL;
        for(mti=1;mti<static_cast<int>(N);++mti) {
          mt[mti]=1812433253UL*(mt[mti-1]^(mt[mti-1]>>30))+mti;
          mt[mti]&=0xFFFFFFFFUL;
        }
      }

      void Init(const uint32_t* init_key, const uint32_t& key_length) {
        int i,j,k;
        Init(19650218UL);
        i=1; j=0;
        k=(N>key_length?N:key_length);
        for(;k;--k) {
          mt[i]=(mt[i]^((mt[i-1]^(mt[i-1]>>30))*1664525UL))+init_key[j]+j;
          mt[i]&=0xFFFFFFFFUL;
          ++i;  ++j;
          if(static_cast<uint32_t>(i)>=N) { mt[0]=mt[N-1];  i=1; }
          if(static_cast<uint32_t>(j)>=key_length)    j=0;
        }
        for(k=N-1;k;--k) {
          mt[i]=(mt[i]^((mt[i-1]^(mt[i-1]>>30))*1566083941UL))-i;
          mt[i]&=0xFFFFFFFFUL;
          ++i;
          if(static_cast<uint32_t>(i)>=N) { mt[0]=mt[N-1];  i=1; }
        }
        mt[0]=0x80000000UL;
      }

      const uint32_t& GenRandUint32() {
        static const int dNM=static_cast<int>(N-M);
        if(static_cast<uint32_t>(mti)>=N) {
          if(static_cast<uint32_t>(mti)==N+1)   Init(5489UL);
          for(kk=0;kk<dNM;++kk) {
            oui=(mt[kk]&UppMask)|(mt[kk+1]&LowMask);
            mt[kk]=mt[kk+M]^(oui>>1)^mag01[oui&0x1UL];
          }
          for(;kk<static_cast<int>(N-1);++kk) {
            oui=(mt[kk]&UppMask)|(mt[kk+1]&LowMask);
            mt[kk]=mt[kk-dNM]^(oui>>1)^mag01[oui&0x1UL];
          }
          oui=(mt[N-1]&UppMask)|(mt[0]&LowMask);
          mt[N-1]=mt[M-1]^(oui>>1)^mag01[oui&0x1UL];
          mti=0;
        }
        oui=mt[mti++];
        oui^=(oui>>11);
        oui^=(oui<<7)&0x9D2C5680UL;
        oui^=(oui<<15)&0xEFC60000UL;
        oui^=(oui>>18);
        return oui;
      }

      const int& GenRandInt31() {
        oi=static_cast<int>(GenRandUint32()>>1);
        return oi;
      }

      const double& GenRand_Close0Close1() {
        od=static_cast<double>(static_cast<int>(GenRandUint32()))*
           (1.0/4294967295.0)+(0.5+0.5/4294967295.0);
        return od;
      }

      const double& GenRand_Close0Open1() {
        od=static_cast<double>(static_cast<int>(GenRandUint32()))*
           (1.0/4294967296.0)+0.5;
        return od;
      }

      const double& GenRand_Open0Close0() {
        od=static_cast<double>(static_cast<int>(GenRandUint32()))*
           (1.0/4294967296.0)+(0.5+0.5/4294967296.0);
        return od;
      }

      const double& GenRand53Mix_Close0Open1() {
        long x,y;
        x=static_cast<long>(GenRandUint32()>>5);
        y=static_cast<long>(GenRandUint32()>>6);
        od=(x*67108864.0+y)*(1.0/9007199254740992.0);
        return od;
      }

      const double& GenRand53Mix_Close0Open1_Slow() {
        uint32_t x,y;
        x=GenRandUint32()>>5;
        y=GenRandUint32()>>6;
        od=(static_cast<double>(x)*67108864.0+y)*(1.0/9007199254740992.0);
        return od;
      }

      const long double& GenRand63Mix_CLose0Open1() {
        long x,y;
        x=static_cast<long>(GenRandUint32());
        y=static_cast<long>(GenRandUint32());
        old=static_cast<long double>(x*(1.0/4294967296.0))+
            static_cast<long double>(y*(1.0/18446744073709551616.0L))+
            (0.5+0.5/4294967296.0);
        return old;
      }

      const long double& GenRand63Mix_CLose0Open1_Slow() {
        uint32_t x,y;
        x=GenRandUint32();
        y=GenRandUint32();
        old=(x|(static_cast<uint64_t>(y)<<32))*(1.0/18446744073709551616.0L);
        return old;
      }

      const double& Default(const double&) {
        return GenRand53Mix_Close0Open1();
      }

      const long double& Default(const long double&) {
        return GenRand63Mix_CLose0Open1();
      }

      const uint32_t& Default(const uint32_t&) { return GenRandUint32(); }

  };

  const uint32_t MT_Standard::N=624;

  const uint32_t MT_Standard::M=397;

  const uint32_t MT_Standard::MatrixA=0x9908B0DFUL;

  const uint32_t MT_Standard::UppMask=0x80000000UL;

  const uint32_t MT_Standard::LowMask=0x7FFFFFFFUL;

  const uint32_t MT_Standard::mag01[2]={0x0UL,MatrixA};

}

#endif

