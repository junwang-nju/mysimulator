
#ifndef _Random_Generator_MT_SFMT_H_
#define _Random_Generator_MT_SFMT_H_

#include "ref-vector.h"
#include <cstring>

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

  union W128_SFMT {

#ifdef HAVE_SSE2

    __m128i   si;

#endif

    unsigned int u[4];

  };

  ostream& operator<<(ostream& os, const W128_SFMT& W) {
    os<<W.u[0];
    for(unsigned int i=1;i<4;++i)
      os<<"\t"<<W.u[i];
    return os;
  }

  istream& operator>>(istream& is, W128_SFMT& W) {
    for(unsigned int i=0;i<4;++i)
      is>>W.u[i];
    return is;
  }

  template <unsigned int LoopFac=19937>
  class SFMT {

    private:

      static const unsigned int MExp;

      static const unsigned int N;

      static const unsigned int N32;

      static const unsigned int N64;

      static const unsigned int Pos1;

      static const unsigned int SL1;

      static const unsigned int SL2;

      static const unsigned int SR1;

      static const unsigned int SR2;

      static const unsigned int Msk1;

      static const unsigned int Msk2;

      static const unsigned int Msk3;

      static const unsigned int Msk4;
      
      static const unsigned int Parity1;

      static const unsigned int Parity2;

      static const unsigned int Parity3;

      static const unsigned int Parity4;

      static const unsigned int Parity[4];
      
      static const char* IDStr;

      W128_SFMT sfmt[LoopFac/128+1];
      
      unsigned int *psfmt32;
      
      unsigned long long int *psfmt64;
      
      unsigned int idx;
      
      int initialized;
      
      unsigned int oui32;
      
      unsigned long long int oui64;
      
      double od;
      
      long double old;
      
#ifdef HAVE_SSE2

      __m128i mm_recursion(const __m128i& a, const __m128i& b,
                           const __m128i& c, const __m128i& d,
                           const __m128i& mask) {
        __m128i v,x,y,z;
        x=_mm_load_si128(&a);
        y=_mm_srli_epi32(b,SR1);
        z=_mm_srli_si128(c,SR2);
        v=_mm_slli_epi32(d,SL1);
        z=_mm_xor_si128(z,x);
        z=_mm_xor_si128(z,v);
        x=_mm_slli_si128(x,SL2);
        y=_mm_and_si128(y,mask);
        z=_mm_xor_si128(z,x);
        z=_mm_xor_si128(z,y);
        return z;
      }

      void GenRandAll() {
        unsigned int i;
        __m128i  r,r1,r2,mask;
        mask=_mm_set_epi32(Msk4,Msk3,Msk2,Msk1);
        r1=_mm_load_si128(&(sfmt[N-2].si));
        r2=_mm_load_si128(&(sfmt[N-1].si));
        for(i=0;i<N-Pos1;++i) {
          r=mm_recursion(sfmt[i].si,sfmt[i+Pos1].si,r1,r2,mask);
          _mm_store_si128(&(sfmt[i].si),r);
          r1=r2;
          r2=r;
        }
        for(;i<N;++i) {
          r=mm_recursion(sfmt[i].si,sfmt[i+Pos1-N].si,r1,r2,mask);
          _mm_store_si128(&(sfmt[i].si),r);
          r1=r2;
          r2=r;
        }
      }

      void GenRandArray(W128_SFMT* Array, unsigned int Size) {
        unsigned int i,j;
        __m128i r,r1,r2,mask;
        mask=_mm_set_epi32(Msk4,Msk3,Msk2,Msk1);
        r1=_mm_load_si128(&(sfmt[N-2].si));
        r2=_mm_load_si128(&(sfmt[N-1].si));
        for(i=0;i<N-Pos1;++i) {
          r=mm_recursion(sfmt[i].si,sfmt[i+Pos1].si,r1,r2,mask);
          _mm_store_si128(&(Array[i].si),r);
          r1=r2;
          r2=r;
        }
        for(;i<N;++i) {
          r=mm_recursion(sfmt[i].si,Array[i+Pos1-N].si,r1,r2,mask);
          _mm_store_si128(&(Array[i].si),r);
          r1=r2;
          r2=r;
        }
        for(;i<Size-N;++i) {
          r=mm_recursion(Array[i-N].si,Array[i+Pos1-N].si,r1,r2,mask);
          _mm_store_si128(&(Array[i].si),r);
          r1=r2;
          r2=r;
        }
        for(j=0;j<N+N-Size;++j) {
          r=_mm_load_si128(&(Array[j+Size-N].si));
          _mm_store_si128(&(sfmt[j].si),r);
        }
        for(;i<Size;++i) {
          r=mm_recursion(Array[i-N].si,Array[i+Pos1-N].si,r1,r1,mask);
          _mm_store_si128(&(Array[i].si),r);
          _mm_store_si128(&(sfmt[j++].si),r);
          r1=r2;
          r2=r;
        }
      }

#else

      void DoRecursion(W128_SFMT& r, const W128_SFMT& a, const W128_SFMT& b,
                                     const W128_SFMT& c, const W128_SFMT& d) {
        W128_SFMT x,y;
        lshift128(x,a,SL2);
        rshift128(y,c,SR2);
        r.u[0]=a.u[0]^x.u[0]^((b.u[0]>>SR1)&Msk1)^y.u[0]^(d.u[0]<<SL1);
        r.u[1]=a.u[1]^x.u[1]^((b.u[1]>>SR1)&Msk1)^y.u[1]^(d.u[1]<<SL1);
        r.u[2]=a.u[2]^x.u[2]^((b.u[2]>>SR1)&Msk1)^y.u[2]^(d.u[2]<<SL1);
        r.u[3]=a.u[3]^x.u[3]^((b.u[3]>>SR1)&Msk1)^y.u[3]^(d.u[3]<<SL1);
      }

      void GenRandAll() {
        unsigned int i;
        W128_SFMT *r1=&sfmt[N-2], *r2=&sfmt[N-1];
        for(i=0;i<N-Pos1;++i) {
          DoRecursion(sfmt[i],sfmt[i],sfmt[i+Pos1],*r1,*r2);
          r1=r2;
          r2=&sfmt[i];
        }
        for(;i<N;++i) {
          DoRecursion(sfmt[i],sfmt[i],sfmt[i+Pos1-N],*r1,*r2);
          r1=r2;
          r2=&sfmt[i];
        }
      }

      void GenRandArray(W128_SFMT* Array, const unsigned int& Size) {
        unsigned int i,j;
        W128_SFMT *r1=&sfmt[N-2], *r2=&sfmt[N-1];
        for(i=0;i<N-Pos1;++i) {
          DoRecursion(Array[i],sfmt[i],sfmt[i+Pos1],*r1,*r2);
          r1=r2;
          r2=&Array[i];
        }
        for(;i<N;++i) {
          DoRecursion(Array[i],sfmt[i],sfmt[i+Pos1-N],*r1,*r2);
          r1=r2;
          r2=&Array[i];
        }
        for(;i<Size-N;++i) {
          DoRecursion(Array[i],Array[i-N],Array[i+Pos1-N],*r1,*r2);
          r1=r2;
          r2=&Array[i];
        }
        for(j=0;j<N+N-Size;++j) sfmt[j]=Array[j+Size-N];
        for(;j<Size;++i,++j) {
          DoRecursion(Array[i],Array[i-N],Array[i+Pos1-N],*r1,*r2);
          r1=r2;
          r2=&Array[i];
          sfmt[j]=Array[i];
        }
      }

#endif

      unsigned int idxof(const unsigned int& i) { return i; }

      void rshift128(W128_SFMT& out, const W128_SFMT& in, const int& shift) {
        unsigned long long int th,tl,oh,ol;
        th=(static_cast<unsigned long long int>(in.u[3])<<32) |
           (static_cast<unsigned long long int>(in.u[2]));
        tl=(static_cast<unsigned long long int>(in.u[1])<<32) |
           (static_cast<unsigned long long int>(in.u[0]));
        oh=th>>(shift*8);
        ol=tl>>(shift*8);
        ol|=th<<(64-shift*8);
        out.u[1]=static_cast<unsigned int>(ol>>32);
        out.u[0]=static_cast<unsigned int>(ol);
        out.u[3]=static_cast<unsigned int>(oh>>32);
        out.u[2]=static_cast<unsigned int>(oh);
      }

      void lshift128(W128_SFMT& out, const W128_SFMT& in, const int& shift) {
        unsigned long long int th,tl,oh,ol;
        th=(static_cast<unsigned long long int>(in.u[3])<<32) |
           (static_cast<unsigned long long int>(in.u[2]));
        tl=(static_cast<unsigned long long int>(in.u[1])<<32) |
           (static_cast<unsigned long long int>(in.u[0]));
        oh=th<<(shift*8);
        ol=tl<<(shift*8);
        ol|=th>>(64-shift*8);
        out.u[1]=static_cast<unsigned int>(ol>>32);
        out.u[0]=static_cast<unsigned int>(ol);
        out.u[3]=static_cast<unsigned int>(oh>>32);
        out.u[2]=static_cast<unsigned int>(oh);
      }

      unsigned int func1(const unsigned int& x) {
        return (x^(x>>27))*static_cast<unsigned int>(1664525UL);
      }

      unsigned int func2(const unsigned int& x) {
        return (x^(x>>27))&static_cast<unsigned int>(1566083941UL);
      }

      void PeriodCertification() {
        unsigned int inner=0;
        unsigned int i,j;
        for(i=0;i<4;++i)    inner^=psfmt32[idxof(i)]&Parity[i];
        for(i=16;i>0;i>>=1) inner^=inner>>i;
        inner&=1;
        if(inner==1)    return;
        unsigned int work;
        for(i=0;i<4;++i) {
          work=1;
          for(j=0;i<32;++j) {
            if((work&Parity[i])!=0) {
              psfmt32[idxof(i)]^=work;
              return;
            }
            work=work<<1;
          }
        }
      }

    public:

      typedef SFMT<LoopFac>   Type;

      SFMT() { assert(false); }

      SFMT(const Type& R) { assert(false); }

      SFMT(const unsigned int& seed) { assert(false); }

      const char* IDString() const { return IDStr; }

      const unsigned int& GetMinArraySize32() const { return N32; }

      const unsigned int& GetMinArraySize64() const { return N64; }

      const unsigned int StatusPtr() const {
        return reinterpret_cast<unsigned int>(sfmt);
      }

      const unsigned int& GenRandUint32() {
        assert(initialized);
        if(static_cast<unsigned int>(idx)>=N32) {
          GenRandAll();
          idx=0;
        }
        oui32=psfmt32[idx++];
        return oui32;
      }

      const unsigned long long int& GenRandUint64() {
        assert(initialized);
        assert((idx&1)==0);
        if(static_cast<unsigned int>(idx)>=N32) {
          GenRandAll();
          idx=0;
        }
        oui64=psfmt64[idx>>1];
        idx+=2;
        return oui64;
      }

      void FillArrayUint32(unsigned int* Array, const unsigned int Size) {
        assert(initialized);
        assert(idx==N32);
        assert(Size%4==0);
        assert(Size>=N32);
        GenRandArray(reinterpret_cast<W128_SFMT*>(Array),Size>>2);
        idx=N32;
      }

      void FillArrayUint32(VectorBase<unsigned int>& Array) {
        FillArrayUint32(Array.data(),Array.size());
      }

      void FillArrayUint64(unsigned long long int* Array,
                           const unsigned int Size) {
        assert(initialized);
        assert(idx==N32);
        assert(Size%2==0);
        assert(Size>=N64);
        GenRandArray(reinterpret_cast<W128_SFMT*>(Array),Size>>1);
        idx=N32;
      }

      void FillArrayUint64(VectorBase<unsigned long long int>& Array) {
        FillArrayUint64(Array.data(),Array.size());
      }

      bool IsReadyFill() { return idx==N32; }

      void Init(const unsigned int& seed) {
        unsigned int work;
        psfmt32[idxof(0)]=seed;
        for(unsigned int i=1;i<N32;++i) {
          work=psfmt32[idxof(i-1)];
          psfmt32[idxof(i)]=1812433253UL*(work^(work>>30))+i;
        }
        idx=N32;
        PeriodCertification();
        initialized=1;
      }

      void Init(const unsigned int* init_key, const unsigned int key_length) {
        unsigned int i,j,count;
        unsigned int r;
        unsigned int lag,mid,size=N*4,tmid;
        if(size>=263)       lag=11;
        else if(size>=68)   lag=7;
        else if(size>=39)   lag=5;
        else                lag=3;
        mid=(size-lag)>>1;
        memset(sfmt,0x8B,sizeof(sfmt));
        if(key_length+1>N32)    count=key_length+1;
        else                    count=N32;
        r=func1(psfmt32[idxof(0)]^psfmt32[idxof(mid)]^
                psfmt32[idxof(N32-1)]);
        psfmt32[idxof(mid)]+=r;
        r+=key_length;
        psfmt32[idxof(mid+lag)]+=r;
        psfmt32[idxof(0)]=r;
        --count;
        for(i=1,j=0;(j<count)&&(j<key_length);++j) {
          tmid=(i+mid)%N32;
          r=func1(psfmt32[idxof(i)]^psfmt32[idxof(tmid)]^
                  psfmt32[idxof((i+N32-1)%N32)]);
          psfmt32[idxof(tmid)]+=r;
          r+=init_key[j]+i;
          psfmt32[idxof((i+mid+lag)%N32)]+=r;
          psfmt32[idxof(i)]=r;
          i=(i+1)%N32;
        }
        for(;j<count;++j) {
          tmid=(i+mid)%N32;
          r=func1(psfmt32[idxof(i)]^psfmt32[idxof(tmid)]^
              psfmt32[idxof((i+N32-1)%N32)]);
          psfmt32[idxof(tmid)]+=r;
          r+=i;
          psfmt32[idxof((i+mid+lag)%N32)]+=r;
          psfmt32[idxof(i)]=r;
          i=(i+1)%N32;
        }
        for(j=0;j<N32;++j) {
          tmid=(i+mid)%N32;
          r=func2(psfmt32[idxof(i)]^psfmt32[idxof(tmid)]^
                  psfmt32[idxof((i+N32-1)%N32)]);
          psfmt32[idxof(tmid)]^=r;
          r-=i;
          psfmt32[idxof((i+mid+lag)%N32)]^=r;
          psfmt32[idxof(i)]=r;
          i=(i+1)%N32;
        }
        idx=N32;
        PeriodCertification();
        initialized=1;
      }

      void Init(const VectorBase<unsigned int>& Key) {
        Init(Key.data(),Key.size());
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
        od=(x*67108864.0+y)*(1.0/90071992544740992.0);
        return od;
      }

      const double& GenRand53Mix_Close0Open1_Slow() {
        unsigned int x,y;
        x=GenRandUint32()>>5;
        y=GenRandUint32()>>6;
        od=(static_cast<double>(x)*67108864.0+y)*(1.0/90071992544740992.0);
        return od;
      }

      const long double& GenRand63Mix_Close0Open1() {
        old=static_cast<long double>(static_cast<long long>(GenRandUint64()))*
            (1.0/18446744073709551616.0L)+0.5;
        return old;
      }

      const long double& GenRand63Mix_Close0Open1_Slow() {
        unsigned int x,y;
        x=GenRandUint32();
        y=GenRandUint32();
        old=(x|(static_cast<unsigned long long int>(y)<<32))*(1.0/18446744073709551616.0L);
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

      const unsigned long long int& Default(const unsigned long long int&) {
        return GenRandUint64();
      }

      void saveStatus(ostream& os) {
        for(unsigned int i=0;i<N;++i) os<<sfmt[i]<<"\t";
        os<<idx<<"\t"<<initialized;
      }

      void loadStatus(istream& is) {
        for(unsigned int i=0;i<N;++i) is>>sfmt[i];
        is>>idx>>initialized;
        psfmt32=&sfmt[0].u[0];
        psfmt64=reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0]);
      }
                      
  };

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::MExp=LoopFac;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N=MExp/128+1;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N32=N*4;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::N64=N*2;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Pos1=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::SL1=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::SL2=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::SR1=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::SR2=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Msk1=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Msk2=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Msk3=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Msk4=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Parity1=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Parity2=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Parity3=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Parity4=0;

  template <unsigned int LoopFac>
  const unsigned int SFMT<LoopFac>::Parity[4]={Parity1,Parity2,Parity3,Parity4};

  template <unsigned int LoopFac>
  const char* SFMT<LoopFac>::IDStr=" ";

  template <>
  const unsigned int SFMT<607>::Pos1=2;

  template <>
  const unsigned int SFMT<607>::SL1=15;

  template <>
  const unsigned int SFMT<607>::SL2=3;

  template <>
  const unsigned int SFMT<607>::SR1=13;

  template <>
  const unsigned int SFMT<607>::SR2=3;

  template <>
  const unsigned int SFMT<607>::Msk1=0xFDFF37FFU;

  template <>
  const unsigned int SFMT<607>::Msk2=0xEF7F3F7DU;

  template <>
  const unsigned int SFMT<607>::Msk3=0xFF777B7DU;

  template <>
  const unsigned int SFMT<607>::Msk4=0x7FF7FB2FU;

  template <>
  const unsigned int SFMT<607>::Parity1=0x00000001U;

  template <>
  const unsigned int SFMT<607>::Parity2=0x00000000U;

  template <>
  const unsigned int SFMT<607>::Parity3=0x00000000U;

  template <>
  const unsigned int SFMT<607>::Parity4=0x5986F054U;

  template <>
  const char* SFMT<607>::IDStr=
      "SFMT-607:2-15-3-13-3:FDFF37FF-EF7F3F7D-FF777B7D-7FF7FB2F";

  template <>
  SFMT<607>::SFMT() : psfmt32(&sfmt[0].u[0]),
                      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                      initialized(0) {
  }

  template <>
  SFMT<607>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<1279>::Pos1=7;

  template <>
  const unsigned int SFMT<1279>::SL1=14;

  template <>
  const unsigned int SFMT<1279>::SL2=3;

  template <>
  const unsigned int SFMT<1279>::SR1=5;

  template <>
  const unsigned int SFMT<1279>::SR2=1;

  template <>
  const unsigned int SFMT<1279>::Msk1=0xF7FEFFFDU;

  template <>
  const unsigned int SFMT<1279>::Msk2=0x7FEFCFFFU;

  template <>
  const unsigned int SFMT<1279>::Msk3=0xAFF3EF3FU;

  template <>
  const unsigned int SFMT<1279>::Msk4=0xB5FFFF7FU;

  template <>
  const unsigned int SFMT<1279>::Parity1=0x00000001U;

  template <>
  const unsigned int SFMT<1279>::Parity2=0x00000000U;

  template <>
  const unsigned int SFMT<1279>::Parity3=0x00000000U;

  template <>
  const unsigned int SFMT<1279>::Parity4=0x20000000U;

  template <>
  const char* SFMT<1279>::IDStr=
      " ";

  template <>
  SFMT<1279>::SFMT() : psfmt32(&sfmt[0].u[0]),
                       psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                       initialized(0) {}

  template <>
  SFMT<1279>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<11213>::Pos1=68;

  template <>
  const unsigned int SFMT<11213>::SL1=14;

  template <>
  const unsigned int SFMT<11213>::SL2=3;

  template <>
  const unsigned int SFMT<11213>::SR1=7;

  template <>
  const unsigned int SFMT<11213>::SR2=3;

  template <>
  const unsigned int SFMT<11213>::Msk1=0xEFFFF7F8U;

  template <>
  const unsigned int SFMT<11213>::Msk2=0xFFFFFFEFU;

  template <>
  const unsigned int SFMT<11213>::Msk3=0xDFDFBFFFU;

  template <>
  const unsigned int SFMT<11213>::Msk4=0x7FFFDBFDU;

  template <>
  const unsigned int SFMT<11213>::Parity1=0x00000001U;

  template <>
  const unsigned int SFMT<11213>::Parity2=0x00000000U;

  template <>
  const unsigned int SFMT<11213>::Parity3=0xE8148000U;

  template <>
  const unsigned int SFMT<11213>::Parity4=0xD0C7AFA3U;

  template <>
  const char* SFMT<11213>::IDStr=
      " ";

  template <>
  SFMT<11213>::SFMT() : psfmt32(&sfmt[0].u[0]),
                        psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                        initialized(0) {
  }

  template <>
  SFMT<11213>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<132049>::Pos1=110;

  template <>
  const unsigned int SFMT<132049>::SL1=19;

  template <>
  const unsigned int SFMT<132049>::SL2=1;

  template <>
  const unsigned int SFMT<132049>::SR1=21;

  template <>
  const unsigned int SFMT<132049>::SR2=1;

  template <>
  const unsigned int SFMT<132049>::Msk1=0xFFFFBB5FU;

  template <>
  const unsigned int SFMT<132049>::Msk2=0xFB6EBF95U;

  template <>
  const unsigned int SFMT<132049>::Msk3=0xFFFEFFFAU;

  template <>
  const unsigned int SFMT<132049>::Msk4=0xCFF77FFFU;

  template <>
  const unsigned int SFMT<132049>::Parity1=0x00000001U;

  template <>
  const unsigned int SFMT<132049>::Parity2=0x00000000U;

  template <>
  const unsigned int SFMT<132049>::Parity3=0xCB520000U;

  template <>
  const unsigned int SFMT<132049>::Parity4=0xC7E91C7DU;

  template <>
  const char* SFMT<132049>::IDStr=
      " ";

  template <>
  SFMT<132049>::SFMT() : psfmt32(&sfmt[0].u[0]),
                         psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                         initialized(0) {
  }

  template <>
  SFMT<132049>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<19937>::Pos1=122;

  template <>
  const unsigned int SFMT<19937>::SL1=18;

  template <>
  const unsigned int SFMT<19937>::SL2=1;

  template <>
  const unsigned int SFMT<19937>::SR1=11;

  template <>
  const unsigned int SFMT<19937>::SR2=1;

  template <>
  const unsigned int SFMT<19937>::Msk1=0xDFFFFFEFU;

  template <>
  const unsigned int SFMT<19937>::Msk2=0xDDFECB7FU;

  template <>
  const unsigned int SFMT<19937>::Msk3=0xBFFAFFFFU;

  template <>
  const unsigned int SFMT<19937>::Msk4=0xBFFFFFF6U;

  template <>
  const unsigned int SFMT<19937>::Parity1=0x00000001U;

  template <>
  const unsigned int SFMT<19937>::Parity2=0x00000000U;

  template <>
  const unsigned int SFMT<19937>::Parity3=0x00000000U;

  template <>
  const unsigned int SFMT<19937>::Parity4=0x13C9E684U;

  template <>
  const char* SFMT<19937>::IDStr=
      " ";

  template <>
  SFMT<19937>::SFMT() : psfmt32(&sfmt[0].u[0]),
                        psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                        initialized(0) {
  }

  template <>
  SFMT<19937>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<216091>::Pos1=627;

  template <>
  const unsigned int SFMT<216091>::SL1=11;

  template <>
  const unsigned int SFMT<216091>::SL2=3;

  template <>
  const unsigned int SFMT<216091>::SR1=10;

  template <>
  const unsigned int SFMT<216091>::SR2=1;

  template <>
  const unsigned int SFMT<216091>::Msk1=0xBFF7BFF7U;

  template <>
  const unsigned int SFMT<216091>::Msk2=0xBFFFFFFFU;

  template <>
  const unsigned int SFMT<216091>::Msk3=0xBFFFFA7FU;

  template <>
  const unsigned int SFMT<216091>::Msk4=0xFFDDFBFBU;

  template <>
  const unsigned int SFMT<216091>::Parity1=0xF8000001U;

  template <>
  const unsigned int SFMT<216091>::Parity2=0x89E80709U;

  template <>
  const unsigned int SFMT<216091>::Parity3=0x3BD2B64BU;

  template <>
  const unsigned int SFMT<216091>::Parity4=0x0C64B1E4U;

  template <>
  const char* SFMT<216091>::IDStr=
      "";

  template <>
  SFMT<216091>::SFMT() : psfmt32(&sfmt[0].u[0]),
                         psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                         initialized(0) {
  }

  template <>
  SFMT<216091>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<2281>::Pos1=12;

  template <>
  const unsigned int SFMT<2281>::SL1=19;

  template <>
  const unsigned int SFMT<2281>::SL2=1;

  template <>
  const unsigned int SFMT<2281>::SR1=5;

  template <>
  const unsigned int SFMT<2281>::SR2=1;

  template <>
  const unsigned int SFMT<2281>::Msk1=0xBFF7FFBFU;

  template <>
  const unsigned int SFMT<2281>::Msk2=0xFDFFFFFEU;

  template <>
  const unsigned int SFMT<2281>::Msk3=0xF7FFEF7FU;

  template <>
  const unsigned int SFMT<2281>::Msk4=0xF2F7CBBFU;

  template <>
  const unsigned int SFMT<2281>::Parity1=0x00000001U;

  template <>
  const unsigned int SFMT<2281>::Parity2=0x00000000U;

  template <>
  const unsigned int SFMT<2281>::Parity3=0x00000000U;

  template <>
  const unsigned int SFMT<2281>::Parity4=0x41DFA600U;

  template <>
  const char* SFMT<2281>::IDStr=
      "";

  template <>
  SFMT<2281>::SFMT() : psfmt32(&sfmt[0].u[0]),
                       psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                       initialized(0) {
  }

  template <>
  SFMT<2281>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<4253>::Pos1=17;

  template <>
  const unsigned int SFMT<4253>::SL1=20;

  template <>
  const unsigned int SFMT<4253>::SL2=1;

  template <>
  const unsigned int SFMT<4253>::SR1=7;

  template <>
  const unsigned int SFMT<4253>::SR2=1;

  template <>
  const unsigned int SFMT<4253>::Msk1=0x9F7BFFFFU;

  template <>
  const unsigned int SFMT<4253>::Msk2=0x9FFFFF5FU;

  template <>
  const unsigned int SFMT<4253>::Msk3=0x3EFFFFFBU;

  template <>
  const unsigned int SFMT<4253>::Msk4=0xFFFFF7BBU;

  template <>
  const unsigned int SFMT<4253>::Parity1=0xA8000001U;

  template <>
  const unsigned int SFMT<4253>::Parity2=0xAF5390A3U;

  template <>
  const unsigned int SFMT<4253>::Parity3=0xB740B3F8U;

  template <>
  const unsigned int SFMT<4253>::Parity4=0x6C11486DU;

  template <>
  const char* SFMT<4253>::IDStr=
      " ";

  template <>
  SFMT<4253>::SFMT() : psfmt32(&sfmt[0].u[0]),
                       psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                       initialized(0) {
  }

  template <>
  SFMT<4253>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<44497>::Pos1=330;

  template <>
  const unsigned int SFMT<44497>::SL1=5;

  template <>
  const unsigned int SFMT<44497>::SL2=3;

  template <>
  const unsigned int SFMT<44497>::SR1=9;

  template <>
  const unsigned int SFMT<44497>::SR2=3;

  template <>
  const unsigned int SFMT<44497>::Msk1=0xEFFFFFFBU;

  template <>
  const unsigned int SFMT<44497>::Msk2=0xDFBEBFFFU;

  template <>
  const unsigned int SFMT<44497>::Msk3=0xBFBF7BEFU;

  template <>
  const unsigned int SFMT<44497>::Msk4=0x9FFD7BFFU;

  template <>
  const unsigned int SFMT<44497>::Parity1=0x00000001U;

  template <>
  const unsigned int SFMT<44497>::Parity2=0x00000000U;

  template <>
  const unsigned int SFMT<44497>::Parity3=0xA3AC4000U;

  template <>
  const unsigned int SFMT<44497>::Parity4=0xECC1327AU;

  template <>
  const char* SFMT<44497>::IDStr=
      " ";

  template <>
  SFMT<44497>::SFMT() : psfmt32(&sfmt[0].u[0]),
                        psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                        initialized(0) {
  }

  template <>
  SFMT<44497>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <>
  const unsigned int SFMT<86243>::Pos1=366;

  template <>
  const unsigned int SFMT<86243>::SL1=6;

  template <>
  const unsigned int SFMT<86243>::SL2=7;

  template <>
  const unsigned int SFMT<86243>::SR1=19;

  template <>
  const unsigned int SFMT<86243>::SR2=1;

  template <>
  const unsigned int SFMT<86243>::Msk1=0xFDBFFBFFU;

  template <>
  const unsigned int SFMT<86243>::Msk2=0xBFF7FF3FU;

  template <>
  const unsigned int SFMT<86243>::Msk3=0xFD77EFFFU;

  template <>
  const unsigned int SFMT<86243>::Msk4=0xBF9FF3FFU;

  template <>
  const unsigned int SFMT<86243>::Parity1=0x00000001U;

  template <>
  const unsigned int SFMT<86243>::Parity2=0x00000000U;

  template <>
  const unsigned int SFMT<86243>::Parity3=0x00000000U;

  template <>
  const unsigned int SFMT<86243>::Parity4=0xE9528D85U;

  template <>
  const char* SFMT<86243>::IDStr=
      " ";

  template <>
  SFMT<86243>::SFMT() : psfmt32(&sfmt[0].u[0]),
                        psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
                        initialized(0) {
  }

  template <>
  SFMT<86243>::SFMT(const unsigned int& seed)
    : psfmt32(&sfmt[0].u[0]),
      psfmt64(reinterpret_cast<unsigned long long int*>(&sfmt[0].u[0])),
      initialized(0) {
    Init(seed);
  }

  template <unsigned int LoopFac>
  void BuildRationalVector(const SFMT<LoopFac>& rg,
                           const VectorBase<unsigned int>& iV,
                           refVector<unsigned int>& rV) {
    unsigned int fg;
    if((reinterpret_cast<unsigned int>(iV.data())&0xF)==(rg.StatusPtr()&0xF)) {
      fg=(iV.size()&3);
      rV.refer(iV,0,iV.size()-fg);
    } else {
      fg=((iV.size()-2)&3);
      rV.refer(iV,2,iV.size()-2-fg);
    }
  }

  template <unsigned int LoopFac>
  void BuildRationalVector(const SFMT<LoopFac>& rg,
                           const VectorBase<unsigned long long int>& iV,
                           refVector<unsigned long long int>& rV) {
    unsigned int fg;
    if((reinterpret_cast<unsigned int>(iV.data())&0xF)==(rg.StatusPtr()&0xF)) {
      fg=(iV.size()&1);
      rV.refer(iV,0,iV.size()-fg);
    } else {
      fg=((iV.size()-1)&1);
      rV.refer(iV,1,iV.size()-1-fg);
    }
  }

}

#endif

