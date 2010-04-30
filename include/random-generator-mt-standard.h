
#ifndef _Random_Generator_MT_Standard_H_
#define _Random_Generator_MT_Standard_H_

#include "unique-parameter-128bit.h"
#include "storage-state-name.h"
#include "vector-impl.h"

namespace std {

  struct MT_Standard;

  void assign(MT_Standard&,const MT_Standard&);
  void release(MT_Standard&);
  void init(MT_Standard&, const unsigned int);
  void init(MT_Standard&, const unsigned int*, const unsigned int);

  struct MT_Standard {

    static const unsigned int N;
    static const unsigned int M;
    static const unsigned int MatrixA;
    static const unsigned int UppMask;
    static const unsigned int LowMask;
    static const unsigned int Mag01[2];
    static const unsigned int Mask32b;
    unsigned int *mt;
    int *mti;
    UniqueParameter128b *output;
    unsigned int state;

    typedef MT_Standard Type;

    MT_Standard() : mt(NULL), mti(NULL), output(NULL), state(Unused) {}
    MT_Standard(const Type&) { myError("Cannot create from MT Standard"); }
    Type& operator=(const Type& MS) { assign(*this,MS); return *this; }
    ~MT_Standard() { release(*this); }

    void init(const unsigned int seed) { std::init(*this,seed); }
    void init(const unsigned int* key, const unsigned int len) {
      std::init(*this,key,len);
    }

    const unsigned int& Uint32() {
      static const int dNM=static_cast<int>(N-M);
      int& ri=*mti;
      unsigned int& u=output->u[0];
      int kk;
      if(static_cast<unsigned int>(ri)>=MT_Standard::N) {
        if(static_cast<unsigned int>(ri)==MT_Standard::N+1) init(5489UL);
        for(kk=0;kk<dNM;++kk) {
          u=(mt[kk]&UppMask)|(mt[kk+1]&LowMask);
          mt[kk]=mt[kk+M]^(u>>1)^Mag01[u&0x1UL];
        }
        for(;kk<static_cast<int>(N-1);++kk) {
          u=(mt[kk]&UppMask)|(mt[kk+1]&LowMask);
          mt[kk]=mt[kk-dNM]^(u>>1)^Mag01[u&0x1UL];
        }
        u=(mt[N-1]&UppMask)|(mt[0]&LowMask);
        mt[N-1]=mt[M-1]^(u>>1)^Mag01[u&0x1UL];
        ri=0;
      }
      u=mt[ri++];
      u^=(u>>11);
      u^=(u<<7)&0x9D2C5680UL;
      u^=(u<<15)&0xEFC60000UL;
      u^=(u>>18);
      return u;
    }

  };

  const unsigned int MT_Standard::N=624;
  const unsigned int MT_Standard::M=397;
  const unsigned int MT_Standard::MatrixA=0x9908B0DFUL;
  const unsigned int MT_Standard::UppMask=0x80000000UL;
  const unsigned int MT_Standard::LowMask=0x7FFFFFFFUL;
  const unsigned int MT_Standard::Mag01[2]={0x0UL,MatrixA};
  const unsigned int MT_Standard::Mask32b=0xFFFFFFFFUL;

  bool IsAvailable(const MT_Standard& MS) { return IsAvailable(MS.mt); }
  bool IsRandomGenerator(const MT_Standard&) { return true; }

  void assign(MT_Standard& dest, const MT_Standard& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(dest.mt,src.mt,MT_Standard::N);
    *(dest.mti)=*(src.mti);
    *(dest.output)=*(src.output);
  }

  void release(MT_Standard& MS) {
    if(MS.state==Allocated) {
      safe_delete_array(MS.mt);
      safe_delete(MS.mti);
      safe_delete(MS.output);
    } else {
      MS.mt=NULL;
      MS.mti=NULL;
      MS.output=NULL;
    }
    MS.state=Unused;
  }

  void allocate(MT_Standard& MS) {
    release(MS);
    MS.mt=new unsigned int[MT_Standard::N];
    MS.mti=new int;
    MS.output=new UniqueParameter128b;
    MS.state=Allocated;
  }

  void refer(MT_Standard& dest, const MT_Standard& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.mt=src.mt;
    dest.mti=src.mti;
    dest.output=src.output;
    dest.state=Reference;
  }

  void init(MT_Standard& MS, const unsigned int seed) {
    int& ri=*(MS.mti);
    MS.mt[0]=seed&MT_Standard::Mask32b;
    for(ri=1;ri<static_cast<int>(MT_Standard::N);++ri) {
      MS.mt[ri]=1812433253UL*(MS.mt[ri-1]^(MS.mt[ri-1]>>30))+ri;
      MS.mt[ri]&=MT_Standard::Mask32b;
    }
  }

  void init(MT_Standard& MS, const unsigned int *key, const unsigned int len) {
    int i,j,k;
    init(MS,19650218UL);
    i=1;    j=0;
    k=(MT_Standard::N>len?MT_Standard::N:len);
    for(;k;--k) {
      MS.mt[i]=(MS.mt[i]^((MS.mt[i-1]^(MS.mt[i-1]>>30))*1664525UL))+key[j]+j;
      MS.mt[i]&=MT_Standard::Mask32b;
      ++i;    ++j;
      if(static_cast<unsigned int>(i)>=MT_Standard::N) {
        MS.mt[0]=MS.mt[MT_Standard::N-1]; i=1;
      }
      if(static_cast<unsigned int>(j)>=len) j=0;
    }
    for(k=MT_Standard::N-1;k;--k) {
      MS.mt[i]=(MS.mt[i]^((MS.mt[i-1]^(MS.mt[i-1]>>30))*1566083941UL))-i;
      MS.mt[i]&=MT_Standard::Mask32b;
      ++i;
      if(static_cast<unsigned int>(i)>=MT_Standard::N) {
        MS.mt[0]=MS.mt[MT_Standard::N-1]; i=1;
      }
    }
    MS.mt[0]=MT_Standard::UppMask;
  }

}

#endif

