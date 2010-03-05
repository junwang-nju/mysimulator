
#ifndef _Random_Generator_MT_DSFMT_H_
#define _Random_Generator_MT_DSFMT_H_

#include "vector-base.h"
#include <cstdio>
#include <cstring>

#ifdef HAVE_SSE2
#include <emmintrin.h>
#endif

namespace std {

  union W128_DSFMT {

#ifdef HAVE_SSE2

    __m128i   si;

    __m128d   sd;

#endif

    unsigned long long int  u[2];

    unsigned int  u32[4];

    double    d[2];

  };

  ostream& operator<<(ostream& os, const W128_DSFMT& W) {
    os<<W.u32[0];
    for(unsigned int i=1;i<4;++i)
      os<<"\t"<<W.u32[i];
    return os;
  }

  istream& operator>>(istream& is, W128_DSFMT& W) {
    for(unsigned int i=0;i<4;++i)
      is>>W.u32[i];
    return is;
  }

  void Convert_Close1Open2(W128_DSFMT& w) {}

#ifdef HAVE_SSE2

  __m128i   SSE2_ParamMask;

  __m128i   SSE2_IntOne;

  __m128d   SSE2_DoubleTwo;

  __m128d   SSE2_DoubleMOne;

  void Convert_Close0Open1(W128_DSFMT& w) {
    w.sd=_mm_add_pd(w.sd,SSE2_DoubleMOne);
  }

  void Convert_Open0Close1(W128_DSFMT& w) {
    w.sd=_mm_sub_pd(SSE2_DoubleTwo,w.sd);
  }

  void Convert_Open0Open1(W128_DSFMT& w) {
    w.si=_mm_or_si128(w.si,SSE2_IntOne);
    w.sd=_mm_add_pd(w.sd,SSE2_DoubleMOne);
  }

#else

  void Convert_Close0Open1(W128_DSFMT& w) {
    w.d[0]-=1.0;
    w.d[1]-=1.0;
  }

  void Convert_Open0Close1(W128_DSFMT& w) {
    w.d[0]=2.0-w.d[0];
    w.d[1]=2.0-w.d[1];
  }

  void Convert_Open0Open1(W128_DSFMT& w) {
    w.u[0]|=1;
    w.u[1]|=1;
    w.d[0]-=1.0;
    w.d[1]-=1.0;
  }

#endif

  template <unsigned int LoopFac=19937>
  class dSFMT {

    private:

      static const unsigned int MExp;

      static const unsigned int N;

      static const unsigned int N32;

      static const unsigned int N64;

      static const unsigned long long int LowMask;

      static const unsigned long long int HighConst;

      static const unsigned int SR;

#ifdef HAVE_SSE2

      static const unsigned int SSE2_Shuff;

#endif

      static const unsigned int Pos1;

      static const unsigned int SL1;

      static const unsigned long long int Msk1;

      static const unsigned long long int Msk2;

      static const unsigned int Msk32_1;

      static const unsigned int Msk32_2;

      static const unsigned int Msk32_3;

      static const unsigned int Msk32_4;

      static const unsigned long long int Fix1;

      static const unsigned long long int Fix2;

      static const unsigned long long int Pcv1;

      static const unsigned long long int Pcv2;

      static const char* IDStr;

      W128_DSFMT  status[(LoopFac-128)/104+2];    /// namely N+1

      unsigned int idx;

      unsigned int  oui;

      double    od;

      const unsigned int& idxof(const unsigned int& I) { return I; }

#ifdef HAVE_SSE2

      void SetupConst() {
        static int first=1;
        if(!first)  return;
        SSE2_ParamMask=_mm_set_epi32(Msk32_3,Msk32_4,Msk32_1,Msk32_2);
        SSE2_IntOne=_mm_set_epi32(0,1,0,1);
        SSE2_DoubleTwo=_mm_set_pd(2.0,2.0);
        SSE2_DoubleMOne=_mm_set_pd(-1.0,-1.0);
        first=0;
      }

      void DoRecursion(const W128_DSFMT& a, const W128_DSFMT& b,
                       W128_DSFMT& r, W128_DSFMT& u){
        __m128i v,w,x,y,z,ra,rb,ru;
        ra=a.si;
        cout<<"***************** 1"<<endl;
        cout<<&rb<<"\t"<<&(b.si)<<endl;
        rb=_mm_loadu_si128(&(b.si));
        cout<<"***************** 2"<<endl;
        ru=u.si;
        x=ra;
        z=_mm_slli_epi64(x,SL1);
        y=_mm_shuffle_epi32(ru,SSE2_Shuff);
        z=_mm_xor_si128(z,rb);
        y=_mm_xor_si128(y,z);
        v=_mm_srli_epi64(y,SR);
        w=_mm_and_si128(y,SSE2_ParamMask);
        v=_mm_xor_si128(v,x);
        v=_mm_xor_si128(v,w);
        cout<<"***************** 3"<<endl;
        r.si=v;
        cout<<"***************** 4"<<endl;
        u.si=y;
      }

#else

      void DoRecursion(const W128_DSFMT& a, const W128_DSFMT& b,
                       W128_DSFMT& r, W128_DSFMT& lung) {
        unsigned long long int t0,t1,L0,L1;
        t0=a.u[0];
        t1=a.u[1];
        L0=lung.u[0];
        L1=lung.u[1];
        lung.u[0]=(t0<<SL1)^(L1>>32)^(L1<<32)^b.u[0];
        lung.u[1]=(t1<<SL1)^(L0>>32)^(L0<<32)^b.u[1];
        r.u[0]=(lung.u[0]>>SR)^(lung.u[0]&Msk1)^t0;
        r.u[1]=(lung.u[1]>>SR)^(lung.u[1]&Msk2)^t1;
      }

#endif

      typedef void (*ConvertFuncType)(W128_DSFMT&);

      void GenRandArrayImpl(W128_DSFMT* Array, unsigned int Size,
                            const ConvertFuncType& cfunc) {
        unsigned int i,j;
        W128_DSFMT lung;
        lung=status[N];
        cout<<((Array-&lung)&0xF)<<endl;
        assert(((Array-&lung)&0xF)==0);
        cout<<Array<<"\t"<<(&lung)<<"\t"<<status<<endl; getchar();
        cout<<"=============0================"<<endl;
        DoRecursion(status[0],status[Pos1],Array[0],lung);
        for(i=0;i<N-Pos1;++i) {
          cout<<Array[i]<<endl;
          DoRecursion(status[i],status[i+Pos1],Array[i],lung);
        }
        cout<<"=============a================"<<endl;
        cout<<i<<"----------- "<<N<<"\t"<<Size<<endl;
        for(;i<N;++i) { cout<<i+Pos1-N<<endl;
          cout<<status[i]<<endl;
          cout<<Array[i+Pos1-N]<<endl;
          cout<<lung<<endl;
          DoRecursion(status[i],Array[i+Pos1-N],Array[i],lung);
          cout<<"\t"<<i<<endl; }
        cout<<"=============b================"<<endl;
        for(;i+N<Size;++i) {
          DoRecursion(Array[i-N],Array[i+Pos1-N],Array[i],lung);
          cfunc(Array[i-N]);
        }
        cout<<"=============1================"<<endl;
        for(j=0;j+Size<N+N;++j) status[j]=Array[j+Size-N];
        for(;i<Size;++i,++j) {
          DoRecursion(Array[i-N],Array[i+Pos1-N],Array[i],lung);
          status[j]=Array[i];
          cfunc(Array[i-N]);
        }
        cout<<"=============2================"<<endl;
        for(i=Size-N;i<Size;++i)  cfunc(Array[i]);
        status[N]=lung;
      }

      unsigned int init_func1(const unsigned int& x) {
        return (x^(x>>27))*static_cast<unsigned int>(1664525UL);
      }

      unsigned int init_func2(const unsigned int& x) {
        return (x^(x>>27))*static_cast<unsigned int>(1566083941UL);
      }

      void init_mask() {
        unsigned long long int *pSFMT;
        pSFMT=&(status[0].u[0]);
        for(unsigned int i=0;i<N+N;++i) pSFMT[i]=(pSFMT[i]&LowMask)|HighConst;
      }

      void PeriodCertification() {
        unsigned long long int pcv[2]={Pcv1,Pcv2};
        unsigned long long int tmp[2];
        unsigned long long int inner;
        int i;
        tmp[0]=status[N].u[0]^Fix1;
        tmp[1]=status[N].u[1]^Fix2;
        inner=tmp[0]&pcv[0];
        inner^=tmp[1]&pcv[1];
        for(i=32;i>0;i>>=1)   inner^=inner>>i;
        inner&=1;
        if(inner==1)    return;
        status[N].u[1]^=1;
        return;
      } // Here assuming Pcv2&1==1

      void GenRandAll() {
        unsigned int i;
        W128_DSFMT lung;
        DoRecursion(status[0],status[Pos1],status[0],lung);
        for(i=1;i<N-Pos1;++i)
          DoRecursion(status[i],status[i+Pos1],status[i],lung);
        for(;i<N;++i)
          DoRecursion(status[i],status[i+Pos1-N],status[i],lung);
        status[N]=lung;
      }

      void FillArrayImpl(double *Array, unsigned int Size,
                         const ConvertFuncType& cfunc) {
        assert((Size&1)==0);
        assert(Size>=N64);
        GenRandArrayImpl(reinterpret_cast<W128_DSFMT*>(Array),Size>>1,cfunc);
      }

    public:

      typedef dSFMT<LoopFac>    Type;

      dSFMT() { myError("Not Implemented"); }

      dSFMT(const Type& DR) {
        myError("Cannot create from dSFMT random generator");
      }

      dSFMT(const unsigned int& seed) { myError("Not Implemented"); }

      const char* IDString() { return IDStr; }

      int GetMinArraySize() { return N64; }

      void FillArray_Close1Open2(double* Array, const unsigned int Sz) {
        FillArrayImpl(Array,Sz,Convert_Close1Open2);
      }

      void FillArray_Close0Open1(double* Array, const unsigned int Sz) {
        FillArrayImpl(Array,Sz,Convert_Close0Open1);
      }

      void FillArray_Open0Close1(double* Array, const unsigned int Sz) {
        FillArrayImpl(Array,Sz,Convert_Open0Close1);
      }

      void FillArray_Open0Open1(double* Array, const unsigned int Sz) {
        FillArrayImpl(Array,Sz,Convert_Open0Open1);
      }

      void FillArray_Close1Open2(VectorBase<double>& V) {
        FillArray_Close1Open2(V.data(),V.size());
      }

      void FillArray_Close0Open1(VectorBase<double>& V) {
        FillArray_Close0Open1(V.data(),V.size());
      }

      void FillArray_Open0Close1(VectorBase<double>& V) {
        FillArray_Open0Close1(V.data(),V.size());
      }

      void FillArray_Open0Open1(VectorBase<double>& V) {
        FillArray_Open0Open1(V.data(),V.size());
      }

      void Init(const unsigned int& seed) {
        unsigned int *pSFMT;
        pSFMT=&status[0].u32[0];
        pSFMT[idxof(0)]=seed;
        unsigned int sz=(N+1)*4;
        for(unsigned int i=1;i<sz;++i)
          pSFMT[idxof(i)]=
            1812433253UL*(pSFMT[idxof(i-1)]^(pSFMT[idxof(i-1)]>>30))+i;
        init_mask();
        PeriodCertification();
        idx=N64;
#ifdef HAVE_SSE2
        SetupConst();
#endif
      }

      void Init(const unsigned int* init_key, int key_length) {
        unsigned int r, *pSFMT32;
        int i,j,count,lag,mid,tmid;
        int size=(N+1)*4;
        if(size>=623)         lag=11;
        else if(size>=68)     lag=7;
        else if(size>=39)     lag=5;
        else                  lag=3;
        mid=(size-lag)/2;
        pSFMT32=&status[0].u32[0];
        memset(status,0x8B,sizeof(status));
        count=(key_length+1>size?key_length+1:size);
        tmid=mid%size;
        r=init_func1(pSFMT32[idxof(0)]^pSFMT32[idxof(tmid)]
                     ^pSFMT32[idxof(size-1)]);
        pSFMT32[idxof(tmid)]+=r;
        r+=key_length;
        pSFMT32[idxof((mid+lag)%size)]+=r;
        pSFMT32[idxof(0)]=r;
        --count;
        for(i=1,j=0;(j<count)&&(j<key_length);++j) {
          tmid=(i+mid)%size;
          r=init_func1(pSFMT32[idxof(i)]^pSFMT32[idxof(tmid)]
                       ^pSFMT32[idxof((i+size-1)%size)]);
          pSFMT32[idxof(tmid)]+=r;
          r+=init_key[j]+i;
          pSFMT32[idxof((i+mid+lag)%size)]+=r;
          pSFMT32[idxof(i)]=r;
          i=(i+1)%size;
        }
        for(;j<count;++j) {
          tmid=(i+mid)%size;
          r=init_func1(pSFMT32[idxof(i)]^pSFMT32[idxof(tmid)]
                       ^pSFMT32[idxof((i+size-1)%size)]);
          pSFMT32[idxof(tmid)]+=r;
          r+=i;
          pSFMT32[idxof((i+mid+lag)%size)]+=r;
          pSFMT32[idxof(i)]=r;
          i=(i+1)%size;
        }
        for(j=0;j<size;++j) {
          tmid=(i+mid)%size;
          r=init_func2(pSFMT32[idxof(i)]+pSFMT32[idxof(tmid)]
                       +pSFMT32[idxof((i+size-1)%size)]);
          pSFMT32[idxof(tmid)]^=r;
          r-=i;
          pSFMT32[idxof((i+mid+lag)%size)]^=r;
          pSFMT32[idxof(i)]=r;
          i=(i+1)%size;
        }
        init_mask();
        PeriodCertification();
        idx=N64;
#ifdef HAVE_SSE2
        SetupConst();
#endif
      }

      void Init(const VectorBase<unsigned int>& Key) {
        Init(Key.data(),Key.size());
      }

      const unsigned int& GenRandUint32() {
        unsigned long long int *pSFMT64=&status[0].u[0];
        if(idx>=N64) {
          GenRandAll();
          idx=0;
        }
        oui=pSFMT64[idx++]&0xFFFFFFFFUL;
        return oui;
      }

      const double& GenRand_Close1Open2() {
        double *pSFMT64=&status[0].d[0];
        if(idx>=N64) {
          GenRandAll();
          idx=0;
        }
        od=pSFMT64[idx++];
        return od;
      }

      const double& GenRand_Close0Open1() {
        od=GenRand_Close1Open2()-1.0;
        return od;
      }

      const double& GenRand_Open0Close1() {
        od=2.0-GenRand_Close1Open2();
        return od;
      }

      const double& GenRand_Open0Open1() {
        double *dSFMT64=&status[0].d[0];
        union {
          double d;
          unsigned long long int u;
        } r;
        if(idx>=N64) {
          GenRandAll();
          idx=0;
        }
        r.d=dSFMT64[idx++];
        r.u|=1;
        od=r.d-1.0;
        return od;
      }

      const double& Default(const double&) { return GenRand_Close0Open1(); }

      const unsigned int& Default(const unsigned int&) {
        return GenRandUint32();
      }

      void saveStatus(ostream& os) {
        for(unsigned int i=0;i<=N;++i) os<<status[i]<<"\t";
        os<<idx;
      }

      void loadStatus(istream& is) {
        for(unsigned int i=0;i<=N;++i) is>>status[i];
        is>>idx;
      }

  };

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::MExp=LoopFac;

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N=((MExp-128)/104+1);

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N32=N*4;

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::N64=N*2;

  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::LowMask=0x000FFFFFFFFFFFFFULL;

  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::HighConst=0x3FF0000000000000ULL;

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SR=12;

#ifdef HAVE_SSE2

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SSE2_Shuff=0x1BU;

#endif

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Pos1=0U;

  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::SL1=0U;

  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Msk1=0ULL;

  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Msk2=0ULL;
  
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_1=0U;
  
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_3=0U;
  
  template <unsigned int LoopFac>
  const unsigned int dSFMT<LoopFac>::Msk32_4=0U;
  
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Fix1=0ULL;
  
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Fix2=0ULL;
  
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Pcv1=0ULL;
  
  template <unsigned int LoopFac>
  const unsigned long long int dSFMT<LoopFac>::Pcv2=0ULL;
  
  template <unsigned int LoopFac>
  const char* dSFMT<LoopFac>::IDStr="";
  
  template <>
  const unsigned int dSFMT<521>::Pos1=3;
  
  template <>
  const unsigned int dSFMT<521>::SL1=25;

  template <>
  const unsigned long long int dSFMT<521>::Msk1=0x000FBFEFFF77EFFFULL;
  
  template <>
  const unsigned long long int dSFMT<521>::Msk2=0x000FFEEBFBDFBFDFULL;
  
  template <>
  const unsigned int dSFMT<521>::Msk32_1=0x000FBFEFU;
  
  template <>
  const unsigned int dSFMT<521>::Msk32_2=0xFF77EFFFU;
  
  template <>
  const unsigned int dSFMT<521>::Msk32_3=0x000FFEEBU;
  
  template <>
  const unsigned int dSFMT<521>::Msk32_4=0xFBDFBFDFU;
  
  template <>
  const unsigned long long int dSFMT<521>::Fix1=0xCFB393D661638469ULL;
  
  template <>
  const unsigned long long int dSFMT<521>::Fix2=0xC166867883AE2ADBULL;
  
  template <>
  const unsigned long long int dSFMT<521>::Pcv1=0xCCAA588000000000ULL;

  template <>
  const unsigned long long int dSFMT<521>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<521>::IDStr=
    "dSFMT2-521:3-25:FBFEFFF77EFFF-FFEEBFBDFBFDF";

  template <>
  dSFMT<521>::dSFMT() {}
  
  template <>
  dSFMT<521>::dSFMT(const unsigned int& seed) { Init(seed); }

  template <>
  const unsigned int dSFMT<1279>::Pos1=9;
  
  template <>
  const unsigned int dSFMT<1279>::SL1=19;
  
  template <>
  const unsigned long long int dSFMT<1279>::Msk1=0x000EFFF7FFDDFFEEULL;
  
  template <>
  const unsigned long long int dSFMT<1279>::Msk2=0x000FBFFFFFF77FFFULL;
  
  template <>
  const unsigned int dSFMT<1279>::Msk32_1=0x000EFFF7U;
  
  template <>
  const unsigned int dSFMT<1279>::Msk32_2=0xFFDDFFEEU;
  
  template <>
  const unsigned int dSFMT<1279>::Msk32_3=0x000FBFFFU;
  
  template <>
  const unsigned int dSFMT<1279>::Msk32_4=0xFFF77FFFU;
  
  template <>
  const unsigned long long int dSFMT<1279>::Fix1=0xB66627623D1A31BEULL;
  
  template <>
  const unsigned long long int dSFMT<1279>::Fix2=0x04B6C51147B6109BULL;
  
  template <>
  const unsigned long long int dSFMT<1279>::Pcv1=0x7049F2DA382A6AEBULL;
  
  template <>
  const unsigned long long int dSFMT<1279>::Pcv2=0xDE4CA84A40000001ULL;

  template <>
  const char* dSFMT<1279>::IDStr=
    "dSFMT2-1279:9-19:EFFF7FFDDFFEE-FBFFFFFF77FFF";

  template <>
  dSFMT<1279>::dSFMT() {}
  
  template <>
  dSFMT<1279>::dSFMT(const unsigned int& seed) { Init(seed); }

  template <>
  const unsigned int dSFMT<2203>::Pos1=7;

  template <>
  const unsigned int dSFMT<2203>::SL1=19;

  template <>
  const unsigned long long int dSFMT<2203>::Msk1=0x000FDFFFF5EDBFFFULL;
  
  template <>
  const unsigned long long int dSFMT<2203>::Msk2=0x000F77FFFFFFFBFEULL;

  template <>
  const unsigned int dSFMT<2203>::Msk32_1=0x000FDFFFU;
  
  template <>
  const unsigned int dSFMT<2203>::Msk32_2=0xF5EDBFFFU;
  
  template <>
  const unsigned int dSFMT<2203>::Msk32_3=0x000F77FFU;
  
  template <>
  const unsigned int dSFMT<2203>::Msk32_4=0xFFFFFBFEU;
  
  template <>
  const unsigned long long int dSFMT<2203>::Fix1=0xB14E907A39338485ULL;
  
  template <>
  const unsigned long long int dSFMT<2203>::Fix2=0xF98F0735C637EF90ULL;
  
  template <>
  const unsigned long long int dSFMT<2203>::Pcv1=0x8000000000000000ULL;
  
  template <>
  const unsigned long long int dSFMT<2203>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<2203>::IDStr=
    "dSFMT2-2203:7-19:FDFFFF5EDBFFF-F77FFFFFFFBFE";

  template <>
  dSFMT<2203>::dSFMT() {}
  
  template <>
  dSFMT<2203>::dSFMT(const unsigned int& seed) { Init(seed); }

  template <>
  const unsigned int dSFMT<4253>::Pos1=19;
  
  template <>
  const unsigned int dSFMT<4253>::SL1=19;
  
  template <>
  const unsigned long long int dSFMT<4253>::Msk1=0x0007B7FFFEF5FEFFULL;
  
  template <>
  const unsigned long long int dSFMT<4253>::Msk2=0x000FFDFFEFFEFBFCULL;
  
  template <>
  const unsigned int dSFMT<4253>::Msk32_1=0x0007B7FFU;
  
  template <>
  const unsigned int dSFMT<4253>::Msk32_2=0xFEF5FEFFU;
  
  template <>
  const unsigned int dSFMT<4253>::Msk32_3=0x000FFDFFU;
  
  template <>
  const unsigned int dSFMT<4253>::Msk32_4=0xEFFEFBFCU;

  template <>
  const unsigned long long int dSFMT<4253>::Fix1=0x80901B5FD7A11C65ULL;
  
  template <>
  const unsigned long long int dSFMT<4253>::Fix2=0x5A63FF0E7CB0BA74ULL;
  
  template <>
  const unsigned long long int dSFMT<4253>::Pcv1=0x1AD277BE12000000ULL;
  
  template <>
  const unsigned long long int dSFMT<4253>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<4253>::IDStr=
    "dSFMT2-4253:19-19:7B7FFFEF5FEFF-FFDFFEFFEFBFC";

  template <>
  dSFMT<4253>::dSFMT() {}
  
  template <>
  dSFMT<4253>::dSFMT(const unsigned int& seed) { Init(seed); }

  template <>
  const unsigned int dSFMT<11213>::Pos1=37;
  
  template <>
  const unsigned int dSFMT<11213>::SL1=19;
  
  template <>
  const unsigned long long int dSFMT<11213>::Msk1=0x000FFFFFFDF7FFFDULL;
  
  template <>
  const unsigned long long int dSFMT<11213>::Msk2=0x000DFFFFFFF6BFFFULL;
  
  template <>
  const unsigned int dSFMT<11213>::Msk32_1=0x000FFFFFU;
  
  template <>
  const unsigned int dSFMT<11213>::Msk32_2=0xFDF7FFFDU;
  
  template <>
  const unsigned int dSFMT<11213>::Msk32_3=0x000DFFFFU;
  
  template <>
  const unsigned int dSFMT<11213>::Msk32_4=0xFFF6BFFFU;
  
  template <>
  const unsigned long long int dSFMT<11213>::Fix1=0xD0EF7B7C75B06793ULL;

  template <>
  const unsigned long long int dSFMT<11213>::Fix2=0x9C50FF4CAAE0A641ULL;
  
  template <>
  const unsigned long long int dSFMT<11213>::Pcv1=0x8234C51207C80000ULL;
  
  template <>
  const unsigned long long int dSFMT<11213>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<11213>::IDStr=
    "dSFMT2-11213:37-19:FFFFFFDF7FFFD-DFFFFFFF6BFFF";
    
  template <>
  dSFMT<11213>::dSFMT() {}
  
  template <>
  dSFMT<11213>::dSFMT(const unsigned int& seed) { Init(seed); }
  
  template <>
  const unsigned int dSFMT<19937>::Pos1=117;
  
  template <>
  const unsigned int dSFMT<19937>::SL1=19;
  
  template <>
  const unsigned long long int dSFMT<19937>::Msk1=0x000FFAFFFFFFFB3FULL;
  
  template <>
  const unsigned long long int dSFMT<19937>::Msk2=0x000FFDFFFC90FFFDULL;
  
  template <>
  const unsigned int dSFMT<19937>::Msk32_1=0x000FFAFFU;
  
  template <>
  const unsigned int dSFMT<19937>::Msk32_2=0xFFFFFB3FU;
  
  template <>
  const unsigned int dSFMT<19937>::Msk32_3=0x000FFDFFU;
  
  template <>
  const unsigned int dSFMT<19937>::Msk32_4=0xFC90FFFDU;
  
  template <>
  const unsigned long long int dSFMT<19937>::Fix1=0x90014964B32F4329ULL;
  
  template <>
  const unsigned long long int dSFMT<19937>::Fix2=0x3B8D12AC548A7C7AULL;
  
  template <>
  const unsigned long long int dSFMT<19937>::Pcv1=0x3D84E1AC0DC82880ULL;
  
  template <>
  const unsigned long long int dSFMT<19937>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<19937>::IDStr=
    "dSFMT2-19937:117-19:FFAFFFFFFFB3F-FFDFFFC90FFFD";
    
  template <>
  dSFMT<19937>::dSFMT() {}
  
  template <>
  dSFMT<19937>::dSFMT(const unsigned int& seed) { Init(seed); } 

  template <>
  const unsigned int dSFMT<44497>::Pos1=304;
  
  template <>
  const unsigned int dSFMT<44497>::SL1=19;
  
  template <>
  const unsigned long long int dSFMT<44497>::Msk1=0x000FF6DFFFFFFFEFULL;
  
  template <>
  const unsigned long long int dSFMT<44497>::Msk2=0x0007FFDDDEEFFF6FULL;
  
  template <>
  const unsigned int dSFMT<44497>::Msk32_1=0x000FF6DFU;
  
  template <>
  const unsigned int dSFMT<44497>::Msk32_2=0xFFFFFFEFU;
  
  template <>
  const unsigned int dSFMT<44497>::Msk32_3=0x0007FFDDU;
  
  template <>
  const unsigned int dSFMT<44497>::Msk32_4=0xDEEFFF6FU;
  
  template <>
  const unsigned long long int dSFMT<44497>::Fix1=0x75D910F235F6E10EULL;
  
  template <>
  const unsigned long long int dSFMT<44497>::Fix2=0x7B32158AEDC8E969ULL;
  
  template <>
  const unsigned long long int dSFMT<44497>::Pcv1=0x4C3356B2A0000000ULL;
  
  template <>
  const unsigned long long int dSFMT<44497>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<44497>::IDStr=
    "dSFMT2-44497:304-19:FF6DFFFFFFFEF-7FFDDDEEFFF6F";
    
  template <>
  dSFMT<44497>::dSFMT() {}
  
  template <>
  dSFMT<44497>::dSFMT(const unsigned int& seed) { Init(seed); }

  template <>
  const unsigned int dSFMT<86243>::Pos1=231;
  
  template <>
  const unsigned int dSFMT<86243>::SL1=13;
  
  template <>
  const unsigned long long int dSFMT<86243>::Msk1=0x000FFEDFF6FFFFDFULL;
  
  template <>
  const unsigned long long int dSFMT<86243>::Msk2=0x000FFFF7FDFFFF7EULL;
  
  template <>
  const unsigned int dSFMT<86243>::Msk32_1=0x000FFEDFU;
  
  template <>
  const unsigned int dSFMT<86243>::Msk32_2=0xF6FFFFDFU;
  
  template <>
  const unsigned int dSFMT<86243>::Msk32_3=0x000FFFF7U;
  
  template <>
  const unsigned int dSFMT<86243>::Msk32_4=0xFDFFFF7EU;
  
  template <>
  const unsigned long long int dSFMT<86243>::Fix1=0x1D553E776B975E68ULL;
  
  template <>
  const unsigned long long int dSFMT<86243>::Fix2=0x648FAADF1416BF91ULL;
  
  template <>
  const unsigned long long int dSFMT<86243>::Pcv1=0x5F2CD03E2758A373ULL;
  
  template <>
  const unsigned long long int dSFMT<86243>::Pcv2=0xC0B7EB8410000001ULL;
  
  template <>
  const char* dSFMT<86243>::IDStr=
    "dSFMT2-86243:231-13:FFEDFF6FFFFDF-FFFF7FDFFFF7E";
    
  template <>
  dSFMT<86243>::dSFMT() {}
  
  template <>
  dSFMT<86243>::dSFMT(const unsigned int& seed) { Init(seed); }

  template <>
  const unsigned int dSFMT<132049>::Pos1=371;
  
  template <>
  const unsigned int dSFMT<132049>::SL1=23;
  
  template <>
  const unsigned long long int dSFMT<132049>::Msk1=0x000FB9F4EFF4BF77ULL;
  
  template <>
  const unsigned long long int dSFMT<132049>::Msk2=0x000FFFFFBFEFFF37ULL;
  
  template <>
  const unsigned int dSFMT<132049>::Msk32_1=0x000FB9F4U;
  
  template <>
  const unsigned int dSFMT<132049>::Msk32_2=0xEFF4BF77U;
  
  template <>
  const unsigned int dSFMT<132049>::Msk32_3=0x000FFFFFU;
  
  template <>
  const unsigned int dSFMT<132049>::Msk32_4=0xBFEFFF37U;
  
  template <>
  const unsigned long long int dSFMT<132049>::Fix1=0x4CE24C0E4E234F3BULL;
  
  template <>
  const unsigned long long int dSFMT<132049>::Fix2=0x62612409B5665C2DULL;
  
  template <>
  const unsigned long long int dSFMT<132049>::Pcv1=0x181232889145D000ULL;
  
  template <>
  const unsigned long long int dSFMT<132049>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<132049>::IDStr=
    "dSFMT2-132049:371-23:FB9F4EFF4BF77-FFFFFBFEFFF37";
    
  template <>
  dSFMT<132049>::dSFMT() {}
  
  template <>
  dSFMT<132049>::dSFMT(const unsigned int& seed) { Init(seed); }

  template <>
  const unsigned int dSFMT<216091>::Pos1=1890;
  
  template <>
  const unsigned int dSFMT<216091>::SL1=23;
  
  template <>
  const unsigned long long int dSFMT<216091>::Msk1=0x000BF7DF7FEFCFFFULL;
  
  template <>
  const unsigned long long int dSFMT<216091>::Msk2=0x000E7FFFFEF737FFULL;
  
  template <>
  const unsigned int dSFMT<216091>::Msk32_1=0x000BF7DFU;
  
  template <>
  const unsigned int dSFMT<216091>::Msk32_2=0x7FEFCFFFU;
  
  template <>
  const unsigned int dSFMT<216091>::Msk32_3=0x000E7FFFU;
  
  template <>
  const unsigned int dSFMT<216091>::Msk32_4=0xFEF737FFU;
  
  template <>
  const unsigned long long int dSFMT<216091>::Fix1=0xD7F95A04764C27D7ULL;
  
  template <>
  const unsigned long long int dSFMT<216091>::Fix2=0x6A483861810BEBC2ULL;
  
  template <>
  const unsigned long long int dSFMT<216091>::Pcv1=0x3AF0A8F3D5600000ULL;
  
  template <>
  const unsigned long long int dSFMT<216091>::Pcv2=0x0000000000000001ULL;
  
  template <>
  const char* dSFMT<216091>::IDStr=
    "dSFMT2-216091:1890-23:BF7DF7FEFCFFF-E7FFFFEF737FF";
    
  template <>
  dSFMT<216091>::dSFMT() {}
  
  template <>
  dSFMT<216091>::dSFMT(const unsigned int& seed) { Init(seed); }

}

#endif

