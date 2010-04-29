
#ifndef _Random_Generator_MT_Standard_H_
#define _Random_Generator_MT_Standard_H_

#include "fix-vector.h"
#include "ref-vector.h"

namespace std {

  class MT_Standard {

    private:

      static const unsigned int N;

      static const unsigned int M;

      static const unsigned int MatrixA;

      static const unsigned int UppMask;

      static const unsigned int LowMask;

      static const unsigned int mag01[2];

      fixVector<unsigned int,624> mt;

      int mti, kk;

      unsigned int oui;

      int oi;

      double od;

      long double old;

    public:

      MT_Standard() {}

      MT_Standard(const unsigned int& seed) : mti(N+1) { Init(seed); }

      MT_Standard(const MT_Standard& rng) { assert(false); }

      void Init(const unsigned int& seed) {
        mt[0]=seed&0xFFFFFFFFUL;
        for(mti=1;mti<static_cast<int>(N);++mti) {
          mt[mti]=1812433253UL*(mt[mti-1]^(mt[mti-1]>>30))+mti;
          mt[mti]&=0xFFFFFFFFUL;
        }
      }

      void Init(const unsigned int* init_key, const unsigned int& key_length) {
        int i,j,k;
        Init(19650218UL);
        i=1; j=0;
        k=(N>key_length?N:key_length);
        for(;k;--k) {
          mt[i]=(mt[i]^((mt[i-1]^(mt[i-1]>>30))*1664525UL))+init_key[j]+j;
          mt[i]&=0xFFFFFFFFUL;
          ++i;  ++j;
          if(static_cast<unsigned int>(i)>=N) { mt[0]=mt[N-1];  i=1; }
          if(static_cast<unsigned int>(j)>=key_length)    j=0;
        }
        for(k=N-1;k;--k) {
          mt[i]=(mt[i]^((mt[i-1]^(mt[i-1]>>30))*1566083941UL))-i;
          mt[i]&=0xFFFFFFFFUL;
          ++i;
          if(static_cast<unsigned int>(i)>=N) { mt[0]=mt[N-1];  i=1; }
        }
        mt[0]=0x80000000UL;
      }

      void Init(const VectorBase<unsigned int>& key) {
        Init(key.data(),key.size());
      }

      const unsigned int& GenRandUint32() {
        static const int dNM=static_cast<int>(N-M);
        if(static_cast<unsigned int>(mti)>=N) {
          if(static_cast<unsigned int>(mti)==N+1)   Init(5489UL);
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

      const double& GenRand_Open0Open1() {
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
        unsigned int x,y;
        x=GenRandUint32()>>5;
        y=GenRandUint32()>>6;
        od=(static_cast<double>(x)*67108864.0+y)*(1.0/9007199254740992.0);
        return od;
      }

      const long double& GenRand63Mix_Close0Open1() {
        long x,y;
        x=static_cast<long>(GenRandUint32());
        y=static_cast<long>(GenRandUint32());
        old=static_cast<long double>(x*(1.0/4294967296.0))+
            static_cast<long double>(y*(1.0/18446744073709551616.0L))+
            (0.5+0.5/4294967296.0);
        return old;
      }

      const long double& GenRand63Mix_Close0Open1_Slow() {
        unsigned int x,y;
        x=GenRandUint32();
        y=GenRandUint32();
        old=(x|(static_cast<unsigned long long int>(y)<<32))*
            (1.0/18446744073709551616.0L);
        return old;
      }

      const double& Default(const double&) {
        return GenRand53Mix_Close0Open1();
      }

      const long double& Default(const long double&) {
        return GenRand63Mix_Close0Open1();
      }

      const unsigned int& Default(const unsigned int&) {
        return GenRandUint32();
      }

      void saveStatus(ostream& os) {
        for(unsigned int i=0;i<624;++i) os<<mt[i]<<"\t";
        os<<mti<<"\t"<<kk;
      }

      void loadStatus(istream& is) {
        for(unsigned int i=0;i<624;++i) is>>mt[i];
        is>>mti>>kk;
      }

  };

  const unsigned int MT_Standard::N=624;

  const unsigned int MT_Standard::M=397;

  const unsigned int MT_Standard::MatrixA=0x9908B0DFUL;

  const unsigned int MT_Standard::UppMask=0x80000000UL;

  const unsigned int MT_Standard::LowMask=0x7FFFFFFFUL;

  const unsigned int MT_Standard::mag01[2]={0x0UL,MatrixA};

  template <typename T>
  void BuildRationalVector(const MT_Standard& rg, const VectorBase<T>& iV,
                           refVector<T>& rV) {
    rV.refer(iV);
  }

}

#endif

