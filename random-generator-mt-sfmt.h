
#ifndef _Random_Generator_MT_SFMT_H_
#define _Random_Generator_MT_SFMT_H_

#include <cstdlib>
#include <cassert>
#include <tr1/csdtint>

namespace std {

  union W128_T {

#ifdef HAVE_SSE2

    __m128i   si;

#endif

    uint32_t u[4];

  };

  template <uint LoopFac=19937>
  class SFMT {

    private:

      static const uint32_t MExp;

      static const uint32_t N;

      static const uint32_t N32;

      static const uint32_t N64;

      static const uint32_t Pos1;

      static const uint32_t SL1;

      static const uint32_t SL2;

      static const uint32_t SR1;

      static const uint32_t SR2;

      static const uint32_t Msk1;

      static const uint32_t Msk2;

      static const uint32_t Msk3;

      static const uint32_t Msk4;
      
      static const uint32_t Parity1;

      static const uint32_t Parity2;

      static const uint32_t Parity3;

      static const uint32_t Parity4;

      static const uint32_t Parity[4];
      
      static const char* IDStr;

      W128_T sfmt[LoopFac/128+1];
      
      uint32_t *psfmt32;
      
      uint64_t *psfmt64;
      
      int idx;
      
      int initialized;
      
      uint32_t oui32;
      
      uint64_t oui64;
      
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
        y=_mm_and_si128(u,mask);
        z=_mm_xor_si128(z,x);
        z=_mm_xor_si128(z,y);
        return z;
      }

      void GenRandAll() {
        uint32_t i;
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
          r=mm_recursion(sfmt[i].si,sfmt[i+Po1-N].si,r1,r2,mask);
          _mm_store_si128(&(sfmt[i].si),r);
          r1=r2;
          r2=r;
        }
      }

      void GenRandArray(W128_T* Array, int Size) {
        uint32_t i,j;
        __m128i r,r1,r2,mask;
        mask=_mm_set_epi32(Msk4,Msk3,Msk2,Msk1);
        r1=_mm_load_si128(&(sfmt[N-2].si));
        r2=_mm_load_si128(&(sfmt[N-1].si));
        for(i=0;i<N-Po1;++i) {
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
          r=mm_recursion(Array[i-N].si,Array[i+Po1-N].si,r1,r1,mask);
          _mm_store_si128(&(Array[i].si),r);
          _mm_store_si128(&(sfmt[j++].si),r);
          r1=r2;
          r2=r;
        }
      }

#else

      void DoRecursion(W128_T& r, const W128_T& a, const W128_T& b,
                                  const W128_T& c, const W128_T& d) {
        W128_T x,y;
        lshift128(x,a,SL2);
        rshift128(y,c,SR2);
        r.u[0]=a.u[0]^x.u[0]^((b.u[0]>>SR1)&Msk1)^y.u[0]^(d.u[0]<<SL1);
        r.u[1]=a.u[1]^x.u[1]^((b.u[1]>>SR1)&Msk1)^y.u[1]^(d.u[1]<<SL1);
        r.u[2]=a.u[2]^x.u[2]^((b.u[2]>>SR1)&Msk1)^y.u[2]^(d.u[2]<<SL1);
        r.u[3]=a.u[3]^x.u[3]^((b.u[3]>>SR1)&Msk1)^y.u[3]^(d.u[3]<<SL1);
      }

      void GenRandAll() {
        uint i;
        W128_T *r1=&sfmt[N-2], *r2=&sfmt[N-1];
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

      void GenRandArray(W128_T* Array, const uint& Size) {
        uint i,j;
        W128_T *r1=&sfmt[N-2], *r2=&sfmt[N-1];
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

      uint idxof(const uint& i) { return i; }

      void rshift128(W128_T& out, const W128_T& in, const int& shift) {
        uint64_t th,tl,oh,ol;
        th=(static_cast<uint64_t>(in.u[3])<<32) |
           (static_cast<uint64_t>(in.u[2]));
        tl=(static_cast<uint64_t>(in.u[1])<<32) |
           (static_cast<uint64_t>(in.u[0]));
        oh=th>>(shift*8);
        ol=tl>>(shift*8);
        ol|=th<<(64-shift*8);
        out.u[1]=static_cast<uint32_t>(ol>>32);
        out.u[0]=static_cast<uint32_t>(ol);
        out.u[3]=static_cast<uint32_t>(oh>>32);
        out.u[2]=static_cast<uint32_t>(oh);
      }

      void lshift128(W128_T& out, const W128_T& in, const int& shift) {
        uint64_t th,tl,oh,ol;
        th=(static_cast<uint64_t>(in.u[3])<<32) |
           (static_cast<uint64_t>(in.u[2]));
        tl=(static_cast<uint64_t>(in.u[1])<<32) |
           (static_cast<uint64_t>(in.u[0]));
        oh=th<<(shift*8);
        ol=tl<<(shift*8);
        ol|=th>>(64-shift*8);
        out.u[1]=static_cast<uint32_t>(ol>>32);
        out.u[0]=static_cast<uint32_t>(ol);
        out.u[3]=static_cast<uint32_t>(oh>>32);
        out.u[2]=static_cast<uint32_t>(oh);
      }

      uint32_t func1(const uint32_t& x) {
        return (x^(x>>27))*static_cast<uint32_t>(1664525UL);
      }

      uint32_t func2(const uint32_t& x) {
        return (x^(x>>27))&static_cast<uint32_t>(1566083941UL);
      }

      void PeriodCertification() {
        uint inner=0;
        uint i,j;
        for(i=0;i<4;++i)    inner^psfmt32[idxof(i)]&Parity[i];
        for(i=16;i>0;i>>1)  inner^=inner>>i;
        inner&=1;
        if(inner==1)    return;
        uint32_t work;
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

      SFMT(const uint32_t& seed) { assert(false); }

      const char* IDString() const { return IDStr; }

      const uint32_t& GetMinArraySize32() const { return N32; }

      const uint32_t& GetMinArraySize64() const { return N64; }

      const uint32_t& GenRandUint32() {
        assert(initialized);
        if(static_cast<uint32_t>(idx)>=N32) {
          GenRandAll();
          idx=0;
        }
        oui32=psfmt32[idx++];
        return oui32;
      }

      const uint32_t& GenRandUint64() {
        assert(initialized);
        assert((idx&1)==0);
        if(static_cast<uint32_t>(idx)>=N32) {
          GenRandAll();
          idx=0;
        }
        oui64=psfmt64[idx>>1];
        idx+=2;
        return oui64;
      }

      void FillArrayUint32(uint32_t* Array, const uint& Size) {
        assert(initialized);
        assert(idx==N32);
        assert(Size%4==0);
        assert(Size>=N32);
        GenRandArray(reinterpret_cast<W128_T*>(Array),Size>>2);
        idx=N32;
      }

      void FillArrayUint64(uint64_t* Array, const uint& Size) {
        assert(initialized);
        assert(idx==N32);
        assert(Size%2==0);
        assert(Size>=N64);
        GenRandArray(reinterpret_cast<W128_T*>(Array),Size>>1);
        idx=N32;
      }

      void Init(const uint32_t& seed) {
        uint32_t work;
        psfmt32[idxof(i)]=seed;
        for(uint i=1;i<N32;++i) {
          work=psfmt32[idxof(i-1)];
          psfmt32[idxof(i)]=1812433253UL*(work^(work>>30))+i;
        }
        idx=N32;
        PeriodCertification();
        initialized=1;
      }

  };

}

#endif

