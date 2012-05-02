
#ifndef _Unique_64Bit_Copy_H_
#define _Unique_64Bit_Copy_H_

#include "unique/64bit/interface.h"

namespace mysimulator {

  void Copy(Unique64Bit& U,const Unique64Bit& U2) { U.ull=U2.ull; }

}

#if !(defined(_COPY_V2U)||defined(_COPY_U2V)||defined(_COPY))
#define _COPY_V2U(T) \
  void Copy(Unique64Bit& U,const T& Val) { Value<T>(U)=Val; }
#define _COPY_U2V(T) \
  void Copy(T& Val,const Unique64Bit& U) { Val=Value<T>(U); }
#define _COPY(T) \
  _COPY_V2U(T) \
  _COPY_U2V(T)
#else
#error "Duplicate Definition for Macro _COPY_V2U,_COPY_U2V,_COPY"
#endif

namespace mysimulator {

  _COPY(double)
  _COPY(float)
  _COPY(long long)
  _COPY(unsigned long long)
  _COPY(int)
  _COPY(unsigned int)
  _COPY(long)
  _COPY(unsigned long)
  _COPY(short)
  _COPY(unsigned short)
  _COPY(char)
  _COPY(unsigned char)

}

#if defined(_COPY_V2U)||defined(_COPY_U2V)||defined(_COPY)
#undef _COPY
#undef _COPY_U2V
#undef _COPY_V2U
#endif

namespace mysimulator {

  void Copy(Unique64Bit& U,const void* const& p) { U.ptr=const_cast<void*>(p); }
  void Copy(void*& p,const Unique64Bit& U) { p=const_cast<void*>(U.ptr); }

  template <typename T>
  void Copy(Unique64Bit& U,const T* const& p) {Pointer<T>(U)=const_cast<T*>(p);}
  template <typename T>
  void Copy(T*& p, const Unique64Bit& U) { p=const_cast<T*>(Pointer<T>(U)); }

}

#include "array/1d/copy.h"

namespace mysimulator {

  void Copy(Array1D<Unique64Bit>& V,const Array1D<Unique64Bit>& V2,
            unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i) Copy(V[i],V2[i]);
  }

  void BlasCopy(Array1D<Unique64Bit>& V,const Array1D<Unique64Bit>& V2,
                unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    long m=n, one=1;
    BLAS<double>::Copy(
        &m,reinterpret_cast<double*>(const_cast<Unique64Bit*>(V2._data)),&one,
           reinterpret_cast<double*>(V._data),&one);
  }

  template <typename T>
  void Copy(Array1D<Unique64Bit>& V,const Array1D<T>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i) Copy(V[i],V2[i]);
  }

  template <typename T>
  void Copy(Array1D<T>& V,const Array1D<Unique64Bit>& V2,unsigned int n) {
    assert((n<=V.Size())&&(n<=V2.Size()));
    for(unsigned int i=0;i<n;++i) Copy(V[i],V2[i]);
  }

}

#if !(defined(_ArrayCOPY_V2U)||defined(_ArrayCOPY_U2V)||defined(_ArrayCOPY))
#define _ArrayCOPY_V2U(T,ET) \
  void BlasCopy(Array1D<Unique64Bit>& V,const Array1D<T>& V2,unsigned int n) { \
    assert(sizeof(T)==sizeof(ET)); \
    assert((n<=V.Size())&&(n<=V2.Size())); \
    long m=n, one=1, delta=sizeof(double)/sizeof(T); \
    BLAS<ET>::Copy(&m,reinterpret_cast<ET*>(const_cast<T*>(V2._data)),&one,\
                      reinterpret_cast<ET*>(V._data),&delta); \
  }
#define _ArrayCOPY_U2V(T,ET) \
  void BlasCopy(Array1D<T>& V,const Array1D<Unique64Bit>& V2,unsigned int n) { \
    assert(sizeof(T)==sizeof(ET)); \
    assert((n<=V.Size())&&(n<=V2.Size())); \
    long m=n, one=1, delta=sizeof(double)/sizeof(T); \
    BLAS<ET>::Copy(\
        &m,reinterpret_cast<ET*>(const_cast<Unique64Bit*>(V2._data)),&delta,\
           reinterpret_cast<ET*>(V._data),&one); \
  }
#define _ArrayCOPY(T,ET) \
  _ArrayCOPY_V2U(T,ET) \
  _ArrayCOPY_U2V(T,ET)
#else
#error "Duplicate Definition for Macro _ArrayCOPY_V2U,_ArrayCOPY_U2V,_ArrayCOPY"
#endif

namespace mysimulator {

  _ArrayCOPY(double,double)
  _ArrayCOPY(long long,double)
  _ArrayCOPY(unsigned long long,double)
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

#endif

