
/**
 * @file unique/128bit/interface.h
 * @brief the object with 128 bits and various data formats
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Unique_128Bit_Interface_H_
#define _Unique_128Bit_Interface_H_

#include "unique/64bit/interface.h"

#ifdef _HAVE_SSE2_
#include <emmintrin.h>
#endif

namespace mysimulator {

  union Unique128Bit;
  void Clear(Unique128Bit&);

  union Unique128Bit {

    public:

      typedef Unique128Bit  Type;
      friend void Clear(Type&);
      template <typename T> friend T& Value(Unique128Bit&);
      template <typename T> friend const T& Value(const Unique128Bit&);
      template <typename T> friend T& Value(Unique128Bit&,unsigned int);
      template <typename T>
      friend const T& Value(const Unique128Bit&,unsigned int);
      template <typename T> friend T*& Pointer(Unique128Bit&);
      template <typename T> friend const T* const& Pointer(const Unique128Bit&);

      Unique128Bit() { ullv[0]=0; ullv[1]=0; }
      Unique128Bit(const unsigned long long& l1,const unsigned long long& l2) {
        ullv[0]=l1; ullv[1]=l2;
      }
      Unique128Bit(const double& d1, const double& d2) {
        ullv[0]=*reinterpret_cast<const unsigned long long*>(&d1);
        ullv[1]=*reinterpret_cast<const unsigned long long*>(&d2);
      }
      ~Unique128Bit() { Clear(*this); }

      bool IsValid() const { return true; }

      void Imprint(const Unique128Bit&) {}
      template <typename T>
      void Copy(const T& v) {
        typedef typename IsCopyable<Unique128Bit,T>::Type CopyCheck;
        Value<T>(*this)=v;
      }
#ifdef _HAVE_SSE2_
      void Copy(const __m128i& m) { _mm_storeu_si128(&si,_mm_loadu_si128(&m)); }
      void Copy(const __m128d& m) {
        _mm_storeu_pd(dv,_mm_loadu_pd(reinterpret_cast<const double*>(&m)));
      }
      void Copy(const Unique128Bit& U) { Copy(U.si); }
#else
      void Copy(const Unique128Bit& U) { ullv[0]=U.ullv[0]; ullv[1]=U.ullv[1]; }
#endif
      void Copy(const Unique64Bit& U) { Copy(Value<unsigned long long>(U)); }
      template <typename T>
      void Fill(const T& v) {
        typedef typename IsFillable<Unique128Bit,T>::Type FillCheck;
        unsigned int n=sizeof(Unique128Bit)/sizeof(T);
        for(unsigned int i=0;i<n;++i) Value<T>(*this,i)=v;
      }
#ifdef _HAVE_SSE2_
      void Fill(const __m128i& m) { Copy(m); }
      void Fill(const __m128d& m) { Copy(m); }
      void Fill(const double& m) { sd=_mm_set1_pd(d); }
      void Fill(const unsigned long long& m) {
        Fill(*reinterpret_cast<const double*>(&m));
      }
      void Fill(const long long& m) {
        Fill(*reinterpret_cast<const double*>(&m));
      }
      void Fill(const float& m) { sm=_mm_set1_ps(m); }
      void Fill(const unsigned int& m) { si=_mm_set1_epi32(m); }
      void Fill(const int& m) { si=_mm_set1_epi32(m); }
      void Fill(const unsigned long& m) { si=_mm_set1_epi32(m); }
      void Fill(const long& m) { si=_mm_set1_epi32(m); }
      void Fill(const unsigned short& m) { si=_mm_set1_epi16(m); }
      void Fill(const short& m) { si=_mm_set1_epi16(m); }
      void Fill(const unsigned char& m) { si=_mm_set1_epi8(m); }
      void Fill(const char& m) { si=_mm_set1_epi8(m); }
#endif
      void Fill(const Unique64Bit& U) { Fill(Value<unsigned long long>(U)); }

    protected:

#ifdef _HAVE_SSE2_
      __m128    sm;
      __m128i   si;
      __m128d   sd;
#endif
      long double ld;
      long double ldv[1];
      double d;
      double dv[2];
      float  f;
      float  fv[4];
      unsigned long long ull;
      unsigned long long ullv[2];
      long long ll;
      long long llv[2];
      unsigned int u;
      unsigned int uv[4];
      int i;
      int iv[4];
      unsigned long ul;
      unsigned long ulv[4];
      long l;
      long lv[4];
      unsigned short us;
      unsigned short usv[8];
      short s;
      short sv[8];
      unsigned char uc;
      unsigned char ucv[16];
      char c;
      char cv[16];
      void* ptr;

    private:

      Unique128Bit(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(Unique128Bit& U) { U.ullv[0]=0; U.ullv[1]=0; }

  void _Imprint(Unique128Bit&, const Unique128Bit&) {}
  template <typename T>
  void _Copy(Unique128Bit& U,const T& v) { U.Copy(v); }
  template <typename T>
  void _Copy(T& v,const Unique128Bit& U) { 
    typedef typename IsCopyable<T,Unique128Bit>::Type CopyCheck;
    v=Value<T>(U);
  }
#ifdef _HAVE_SSE2_
  void _Copy(__m128i& v, const Unique128Bit& U) {
    _mm_storeu_si128(&v,_mm_loadu_si128(&Value<__m128i>(U)));
  }
  void _Copy(__m128d& v, const Unique128Bit& U) {
    _mm_storeu_pd(reinterpret_cast<double*>(&v),
                  _mm_loadu_pd(reinterpret_cast<const double*>(&U)));
  }
#endif
  template <typename T>
  void _Fill(Unique128Bit& U,const T& v) { U.Fill(v); }

  template <typename T>
  T& Value(Unique128Bit& P) {
    fprintf(stderr,"Unknown Type for Unique128Bit!\n");
    return static_cast<T&>(P.d);
  }
  template <typename T>
  const T& Value(const Unique128Bit& P) {
    fprintf(stderr,"Unknown Type for Unique128Bit!\n");
    return static_cast<const T&>(P.d);
  }

}

#ifndef _VValueDEF_
#define _VValueDEF_(T,v) \
  template <> T& Value<T>(Unique128Bit& P) { return P.v; }
#else
#error "Duplicate _VValueDEF_"
#endif

#ifndef _CValueDEF_
#define _CValueDEF_(T,v) \
  template <> const T& Value<T>(const Unique128Bit& P) { return P.v; }
#else
#error "Duplicate _CValueDEF_"
#endif

#ifndef _ValueDEF_
#define _ValueDEF_(T,v) \
  _VValueDEF_(T,v) \
  _CValueDEF_(T,v)
#else
#error "Duplicate _ValueDEF_"
#endif

namespace mysimulator {

#ifdef _HAVE_SSE2_
  _ValueDEF_(__m128i,si)
  _ValueDEF_(__m128d,sd)
#endif
  _ValueDEF_(long double,ld)
  _ValueDEF_(double,d)
  _ValueDEF_(float,f)
  _ValueDEF_(unsigned long long,ull)
  _ValueDEF_(long long,ll)
  _ValueDEF_(unsigned int,u)
  _ValueDEF_(int,i)
  _ValueDEF_(unsigned long,ul)
  _ValueDEF_(long,l)
  _ValueDEF_(unsigned short,us)
  _ValueDEF_(short,s)
  _ValueDEF_(unsigned char,uc)
  _ValueDEF_(char,c)

}

#ifdef _ValueDEF_
#undef _ValueDEF_
#endif

#ifdef _CValueDEF_
#undef _CValueDEF_
#endif

#ifdef _VValueDEF_
#undef _VValueDEF_
#endif

namespace mysimulator {

  template <typename T>
  T& Value(Unique128Bit& U,unsigned int i) {
    fprintf(stderr,"Unknown Type for Unique128Bit!\n");
    return static_cast<T&>(U.d);
  }
  template <typename T>
  const T& Value(const Unique128Bit& U,unsigned int i) {
    fprintf(stderr,"Unknown Type for Unique128Bit!\n");
    return static_cast<const T&>(U.d);
  }

}

#ifndef _VValueDEF_
#define _VValueDEF_(T,v) \
  template <> T& Value<T>(Unique128Bit& U,unsigned int i) { \
    assert(i<sizeof(Unique128Bit)/sizeof(T)); \
    return U.v[i]; \
  }
#else
#error "Duplicate _VValueDEF_"
#endif

#ifndef _CValueDEF_
#define _CValueDEF_(T,v) \
  template <> const T& Value<T>(const Unique128Bit& U,unsigned int i) { \
    assert(i<sizeof(Unique128Bit)/sizeof(T)); \
    return U.v[i]; \
  }
#else
#error "Duplicate _CValueDEF_"
#endif

#ifndef _ValueDEF_
#define _ValueDEF_(T,v) \
  _VValueDEF_(T,v) \
  _CValueDEF_(T,v)
#else
#error "Duplicate _ValueDEF_"
#endif

namespace mysimulator {

  _ValueDEF_(long double,ldv)
  _ValueDEF_(double,dv)
  _ValueDEF_(float,fv)
  _ValueDEF_(unsigned long long,ullv)
  _ValueDEF_(long long,llv)
  _ValueDEF_(unsigned int,uv)
  _ValueDEF_(int,iv)
  _ValueDEF_(unsigned long,ulv)
  _ValueDEF_(long,lv)
  _ValueDEF_(unsigned short,usv)
  _ValueDEF_(short,sv)
  _ValueDEF_(unsigned char,ucv)
  _ValueDEF_(char,cv)

}

#ifdef _ValueDEF_
#undef _ValueDEF_
#endif

#ifdef _CValueDEF_
#undef _CValueDEF_
#endif

#ifdef _VValueDEF_
#undef _VValueDEF_
#endif

namespace mysimulator {

  template <typename T>
  T*& Pointer(Unique128Bit& U) { return reinterpret_cast<T*&>(U.ptr); }

  template <typename T>
  const T* const& Pointer(const Unique128Bit& U) {
    return reinterpret_cast<const T* const&>(U.ptr);
  }

}

#include "array-numeric/interface.h"

namespace mysimulator {

  typedef ArrayNumeric<Unique128Bit> AUnique128Bit;

  template <>
  void ArrayNumeric<Unique128Bit>::BlasCopy(const AUnique128Bit& A) {
    assert(this->IsValid());
    assert(A.IsValid());
    assert(this->Size()==A.Size());
    long m=this->Size(), two=2;
    double *p=reinterpret_cast<double*>(A.Head());
    double *q=reinterpret_cast<double*>(this->Head());
    BLAS<double>::Copy(&m,p,  &two,q,  &two);
    BLAS<double>::Copy(&m,p+1,&two,q+1,&two);
  }

  template <>
  void ArrayNumeric<Unique128Bit>::BlasFill(const Unique128Bit& U) {
    assert(this->IsValid());
    long m=this->Size(), zero=0, two=2;
    double *p=reinterpret_cast<double*>(const_cast<Unique128Bit*>(&U));
    double *q=reinterpret_cast<double*>(this->Head());
    BLAS<double>::Copy(&m,p,  &zero,q,  &two);
    BLAS<double>::Copy(&m,p+1,&zero,q+1,&two);
  }

}

#endif

