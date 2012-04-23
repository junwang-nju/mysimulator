
#ifndef _Unique_128Bit_Copy_H_
#define _Unique_128Bit_Copy_H_

#include "unique/128bit/interface.h"

#if !(defined(_COPY_V2U)||defined(_COPY_U2V)||defined(_COPY))
#define _COPY_V2U(T) \
  void Copy(Unique128Bit& U,const T& Val) { Value<T>(U)=Val; }
#define _COPY_U2V(T) \
  void Copy(T& Val,const Unique128Bit& U) { Val=Value<T>(U); }
#define _COPY(T) \
  _COPY_V2U(T) \
  _COPY_U2V(T)
#else
#error "Duplicate Definition for Macro _COPY_V2U,_COPY_U2V,_COPY"
#endif

namespace mysimulator {

  _COPY(long double)
  _COPY(double)
  _COPY(float)
  _COPY(unsigned long long)
  _COPY(long long)
  _COPY(unsigned int)
  _COPY(int)
  _COPY(unsigned long)
  _COPY(long)
  _COPY(unsigned short)
  _COPY(short)
  _COPY(unsigned char)
  _COPY(char)

}

#if defined(_COPY_V2U)||defined(_COPY_U2V)||defined(_COPY)
#undef _COPY
#undef _COPY_U2V
#undef _COPY_V2U
#endif

namespace mysimulator {

#ifdef _HAVE_SSE2
  void Copy(Unique128Bit& U,const __m128i& i) {
    _mm_storeu_si128(&(U.si),_mm_loadu_si128(&i));
  }
  void Copy(__m128i& i, const Unique128Bit& U) {
    _mm_storeu_si128(&i,_mm_loadu_si128(&(U.si)));
  }
  void Copy(Unique128Bit& U,const __m128d& d) {
    _mm_storeu_pd(U.dv,_mm_loadu_pd(reinterpret_cast<const double*>(&d)));
  }
  void Copy(__m128d& d,const Unique128Bit& U) {
    _mm_storeu_pd(reinterpret_cast<double*>(&d),_mm_loadu_pd(U.dv));
  }
  void Copy(Unique128Bit& U,const Unique128Bit& U2) { Copy(U,cU.si); }
#else
  void Copy(Unique128Bit& U,const Unique128Bit& U2) {
    U.ullv[0]=U2.ullv[0]; U.ullv[1]=U2.ullv[1];
  }
#endif

  void Copy(Unique128Bit& U,const void* const& p) {
    U.ptr=const_cast<void*>(p);
  }
  void Copy(void*& p,const Unique128Bit& U) { p=const_cast<void*>(U.ptr); }

  template <typename T>
  void Copy(Unique128Bit& U,const T* const& p) {
    Pointer<T>(U)=const_cast<T*>(p);
  }
  template <typename T>
  void Copy(T*& p,const Unique128Bit& U) { p=const_cast<T*>(Pointer<T>(U)); }

}

#include "array/1d/interface.h"

namespace mysimulator {

  void Copy(Array1D<Unique128Bit>& V,const Array1D<Unique128Bit>& V2,
            unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i)   Copy(V[i],V2[i]);
  }

  void BlasCopy(Array1D<Unique128Bit>& V,const Array1D<Unique128Bit>& V2,
                unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    long m=n, two=2;
    double* p=reinterpret_cast<double*>(V._data);
    double* q=reinterpret_cast<double*>(const_cast<Unique128Bit*>(V2._data));
    BLAS<double>::Copy(&m,q,&two,p,&two);
    BLAS<double>::Copy(&m,q+1,&two,p+1,&two);
  }

  template <typename T>
  void Copy(Array1D<Unique128Bit>& V,const Array1D<T>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i)   Copy(V[i],V2[i]);
  }

  template <typename T>
  void Copy(Array1D<T>& V,const Array1D<Unique128Bit>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i)   Copy(V[i],V2[i]);
  }

}

#if !(defined(_ArrayCOPY_V2U)||defined(_ArrayCOPY_U2V)||defined(_ArrayCOPY))
#define _ArrayCOPY_V2U(T,ET) \
  void BlasCopy(Array1D<Unique128Bit>& V,const Array1D<T>& V2,unsigned int n) {\
    assert(sizeof(T)==sizeof(ET)); \
    assert((n<=V.Size())&&(n<=V2.Size())); \
    long m=n, one=1, delta=sizeof(Unique128Bit)/sizeof(T); \
    BLAS<ET>::Copy(&m,reinterpret_cast<ET*>(const_cast<T*>(V2._data)),&one,\
                   reinterpret_cast<ET*>(V._data),&delta); \
  }
#define _ArrayCOPY_U2V(T,ET) \
  void BlasCopy(Array1D<T>& V,const Array1D<Unique128Bit>& V2,unsigned int n) {\
    assert(sizeof(T)==sizeof(ET)); \
    assert((n<=V.Size())&&(n<=V2.Size())); \
    long m=n, one=1, delta=sizeof(Unique128Bit)/sizeof(T); \
    BLAS<ET>::Copy(\
        &m,reinterpret_cast<ET*>(const_cast<Unique128Bit*>(V2._data)),&delta,\
           reinterpret_cast<ET*>(V._data),&one);\
  }
#define _ArrayCOPY(T,ET) \
  _ArrayCOPY_V2U(T,ET) \
  _ArrayCOPY_U2V(T,ET)
#else
#error "Duplicate Definition for Macro _ArrayCOPY_V2U,_ArrayCOPY_U2V,_ArrayCOPY"
#endif

namespace mysimulator {

  _ArrayCOPY(double,double)
  _ArrayCOPY(unsigned long long,double)
  _ArrayCOPY(long long,double)
  _ArrayCOPY(float,float)
  _ArrayCOPY(int,float)
  _ArrayCOPY(unsigned int,float)
  _ArrayCOPY(long,float)
  _ArrayCOPY(unsigned long,float)

}

#if defined(_ArrayCOPY_V2U)||defined(_ArrayCOPY_U2V)||defined(_ArrayCOPY)
#undef _ArrayCOPY
#undef _ArrayCOPY_U2V
#undef _ArrayCOPY_V2U
#endif

namespace mysimulator {

  void BlasCopy(Array1D<Unique128Bit>& V,const Array1D<long double>& V2,
                unsigned int n) {
    assert(sizeof(long double)==3*sizeof(float));
    assert((n<=V.Size())&&(n<=V2.Size()));
    float* p=reinterpret_cast<float*>(V._data);
    float* q=reinterpret_cast<float*>(const_cast<long double*>(V2._data));
    long m=n,three=3,delta=sizeof(Unique128Bit)/sizeof(float);
    BLAS<float>::Copy(&m,q,  &three,p,  &delta);
    BLAS<float>::Copy(&m,q+1,&three,p+1,&delta);
    BLAS<float>::Copy(&m,q+2,&three,p+2,&delta);
  }

  void BlasCopy(Array1D<long double>& V,Array1D<Unique128Bit>& V2,
                unsigned int n) {
    assert(sizeof(long double)==3*sizeof(float));
    assert((n<=V.Size())&&(n<=V2.Size()));
    float* p=reinterpret_cast<float*>(V._data);
    float* q=reinterpret_cast<float*>(const_cast<Unique128Bit*>(V2._data));
    long m=n,three=3,delta=sizeof(Unique128Bit)/sizeof(float);
    BLAS<float>::Copy(&m,q,  &delta,p,  &three);
    BLAS<float>::Copy(&m,q+1,&delta,p+1,&three);
    BLAS<float>::Copy(&m,q+2,&delta,p+2,&three);
  }

}

#endif

