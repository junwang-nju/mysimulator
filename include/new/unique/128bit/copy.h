
#ifndef _Unique_128Bit_Copy_H_
#define _Unique_128Bit_Copy_H_

#include "unique/128bit/interface.h"
#include "intrinsic-type/copy.h"

#define _COPYV(type) \
  void copy(Unique128Bit& U, const type& val) { copy(U.value<type>(),val); }
#define _COPYU(type) \
  void copy(type& val, const Unique128Bit& U) { copy(val,U.value<type>()); }

#define _COPY(type) \
  _COPYV(type)\
  _COPYU(type)

namespace mysimulator {

  _COPY(long double)
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

#undef _COPY
#undef _COPYU
#undef _COPYV

namespace mysimulator {

#ifdef _Have_SSE2

  void copy(Unique128Bit& U, const __m128i& i) { _mm_storeu_si128(&(U.si),i); }
  void copy(__m128i& i, const Unique128Bit& U) { _mm_storeu_si128(&i,U.si); }

  void copy(Unique128Bit& U, const __m128d& d) { _mm_storeu_pd(U.d,d); }
  void copy(__m128d& d, const Unique128Bit& U) { d=_mm_loadu_pd(U.d); }

  void copy(Unique128Bit& U, const Unique128Bit& cU) {
    _mm_storeu_si128(&(U.si),cU.si);
  }

#else

  void copy(Unique128Bit& U, const Unique128Bit& cU) {
    U.ull[0]=cU.ull[0]; U.ull[1]=cU.ull[1];
  }

#endif

}

#include "array/1d/content/copy.h"

#define _TYPE(type,a) reinterpret_cast<type*>(a)

namespace mysimulator {

  void _copy(Unique128Bit* p, Unique128Bit* q, const unsigned int& n,
             const unsigned int& del, const unsigned int& cdel) {
    _copy_blas(_TYPE(double,p),_TYPE(double,q),n,del+del,cdel+cdel);
    _copy_blas(_TYPE(double,p)+1,_TYPE(double,q)+1,n,del+del,cdel+cdel);
  }

  void _copy(Unique128Bit* p, Unique128Bit* q, const unsigned int& n) {
    _copy_blas(_TYPE(double,p),_TYPE(double,q),n+n);
  }

  void _copy(Unique128Bit* p, long double* q, const unsigned int& n,
             const unsigned int& del, const unsigned int& cdel) {
    static const unsigned int n1=2*sizeof(double)/sizeof(float);
    static const unsigned int n2=sizeof(long double)/sizeof(float);
    _copy_blas(_TYPE(float,p),_TYPE(float,q),n,del*n1,cdel*n2);
    _copy_blas(_TYPE(float,p)+1,_TYPE(float,q)+1,n,del*n1,cdel*n2);
    _copy_blas(_TYPE(float,p)+2,_TYPE(float,q)+2,n,del*n1,cdel*n2);
  }

  void _copy(Unique128Bit* p, long double* q, const unsigned int& n) {
    static const unsigned int n1=2*sizeof(double)/sizeof(float);
    static const unsigned int n2=sizeof(long double)/sizeof(float);
    _copy_blas(_TYPE(float,p),_TYPE(float,q),n,n1,n2);
    _copy_blas(_TYPE(float,p)+1,_TYPE(float,q)+1,n,n1,n2);
    _copy_blas(_TYPE(float,p)+2,_TYPE(float,q)+2,n,n1,n2);
  }

  void _copy(long double* p, Unique128Bit* q, const unsigned int& n,
      const unsigned int& del, const unsigned int& cdel) {
    static const unsigned int n1=2*sizeof(double)/sizeof(float);
    static const unsigned int n2=sizeof(long double)/sizeof(float);
    _copy_blas(_TYPE(float,p),_TYPE(float,q),n,del*n2,cdel*n1);
    _copy_blas(_TYPE(float,p)+1,_TYPE(float,q)+1,n,del*n2,cdel*n1);
    _copy_blas(_TYPE(float,p)+2,_TYPE(float,q)+2,n,del*n2,cdel*n1);
  }

  void _copy(long double* p, Unique128Bit* q, const unsigned int& n) {
    static const unsigned int n1=2*sizeof(double)/sizeof(float);
    static const unsigned int n2=sizeof(long double)/sizeof(float);
    _copy_blas(_TYPE(float,p),_TYPE(float,q),n,n2,n1);
    _copy_blas(_TYPE(float,p)+1,_TYPE(float,q)+1,n,n2,n1);
    _copy_blas(_TYPE(float,p)+2,_TYPE(float,q)+2,n,n2,n1);
  }

}

#define _COPYU_WithDel(type) \
  void _copy(Unique128Bit* p, type* q, const unsigned int& n,\
             const unsigned int& del, const unsigned int& cdel) {\
    _copy_blas(_TYPE(type,p),q,n,del*sizeof(double)/sizeof(type)*2,cdel);\
  }

#define _COPYV_WithDel(type) \
  void _copy(type* p, Unique128Bit* q, const unsigned int& n,\
             const unsigned int& del, const unsigned int& cdel) {\
    _copy_blas(p,_TYPE(type,q),n,del,cdel*2*sizeof(double)/sizeof(type));\
  }

#define _COPYU(type) \
  void _copy(Unique128Bit* p, type* q, const unsigned int& n) {\
    _copy_blas(_TYPE(type,p),q,n,2*sizeof(double)/sizeof(type),uOne);\
  }

#define _COPYV(type) \
  void _copy(type* p, Unique128Bit* q, const unsigned int& n) {\
    _copy_blas(p,_TYPE(type,q),n,uOne,2*sizeof(double)/sizeof(type));\
  }

#define _COPY(type) \
  _COPYU_WithDel(type)\
  _COPYV_WithDel(type)\
  _COPYU(type)\
  _COPYV(type)

namespace mysimulator {

  _COPY(double)
  _COPY(float)
  _COPY(long long)
  _COPY(unsigned long long)
  _COPY(int)
  _COPY(unsigned int)
  _COPY(long)
  _COPY(unsigned long)

}

#undef _COPY
#undef _COPYV
#undef _COPYU
#undef _COPYV_WithDel
#undef _COPYU_WithDel
#undef _TYPE

#endif

