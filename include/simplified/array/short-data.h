
#ifndef _Array_ShortData_H_
#define _Array_ShortData_H_

#include "array/interface.h"
#include "array/expression.h"

#ifndef _HAVE_SSE2
#error "\nSSE2 is required for ShortData Array! Try -msse2 -D_HAVE_SSE2\n"
#endif

#include <emmintrin.h>

namespace mysimulator {

  template <typename T>
  class Array<T,ArrayFormat::ShortData>
      : public ArrayExpression<Array<T,ArrayFormat::ShortData>,T>,
        public ArrayContainer<T,ArrayFormat::ShortData> {

    public:

      typedef Array<T,ArrayFormat::ShortData>           Type;
      typedef ArrayExpression<Type,T>                   ParentTypeA;
      typedef ArrayContainer<T,ArrayFormat::ShortData>  ParentTypeB;
      typedef unsigned int size_type;
      typedef T& reference;
      typedef const T& const_reference;

    private:

      unsigned int _n128;

    public:

      Array() : ParentTypeA(), ParentTypeB(), _n128(0U) {}
      Array(size_type size) : ParentTypeA(), ParentTypeB(size),
                              _n128((size*sizeof(T))>>4) {}
      Array(const Type& A) : Array(A.size()) { operator=(A); }
      ~Array() { ParentTypeB::reset(); }

      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET>& EA) : Array(EA.size()) {
        operator=(EA);
      }
      template <typename E,typename ET>
      Array(const ArrayExpression<E,ET>&& EA) : Array(EA.size()) {
        operator=(EA);
      }

      operator bool() const { return ParentTypeB::operator bool(); }
      size_type size() const { return ParentTypeB::size(); }
      reference operator[](size_type i) { return ParentTypeB::operator[](i); }
      const_reference operator[](size_type i) const {
        return ParentTypeB::operator[](i);
      }
      void allocate(size_type size) {
        ParentTypeB::allocate(size);
        _n128=(size*sizeof(T))>>4;
      }

      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator=(const ArrayExpression<E,ET>&& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]=EA[i];
        return *this;
      }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(size()<=A.size());
        __m128i* p=reinterpret_cast<__m128i*>(this->head());
        __m128i* q=reinterpret_cast<__m128i*>(A.head());
        const __m128i* e=p+_n128;
        for(;p!=e;) _mm_store_si128(p++,*(q++));
        return *this;
      }
      Type& operator=(const T& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]=D;
        return *this;
      }

      template <typename E,typename ET>
      Type& operator+=(const ArrayExpression<E,ET>& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]+=EA[i];
        return *this;
      }
      template <typename E,typename ET>
      Type& operator+=(const ArrayExpression<E,ET>&& EA) {
        assert((bool)(*this));
        assert((bool)EA);
        assert(size()<=EA.size());
        for(size_type i=0;i<size();++i)   (*this)[i]+=EA[i];
        return *this;
      }
      Type& operator+=(const T& D) {
        assert((bool)(*this));
        for(size_type i=0;i<size();++i)   (*this)[i]+=D;
        return *this;
      }

  };

  typedef Array<int,ArrayFormat::ShortData>     ItShortDataArray;
  typedef Array<float,ArrayFormat::ShortData>   FtShortDataArray;
  typedef Array<double,ArrayFormat::ShortData>  DbShortDataArray;

  template <>
  ItShortDataArray& ItShortDataArray::operator=(const int& D) {
    assert((bool)(*this));
    __m128i *p=reinterpret_cast<__m128i*>(this->head());
    const __m128i *e=p+_n128;
    for(;p!=e;)   *(p++)=_mm_set1_epi32(D);
    return *this;
  }

  template <>
  FtShortDataArray& FtShortDataArray::operator=(const float& D) {
    assert((bool)(*this));
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    const __m128 *e=p+_n128;
    for(;p!=e;)   *(p++)=_mm_set1_ps(D);
    return *this;
  }

  template <>
  DbShortDataArray& DbShortDataArray::operator=(const double& D) {
    assert((bool)(*this));
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    for(;p!=e;)   *(p++)=_mm_set1_pd(D);
    return *this;
  }

}

#include "array/expression-sum.h"

namespace mysimulator {

  template <>
  template <>
  FtShortDataArray& FtShortDataArray::operator=(
      const ArrayExpression<ArraySum<FtShortDataArray,FtShortDataArray>,
                            float>&& EA) {
    typedef ArraySum<FtShortDataArray,FtShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128 *p=reinterpret_cast<__m128*>(this->head());
    __m128 *q=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).first());
    __m128 *r=reinterpret_cast<__m128*>(
                               static_cast<const SType&>(EA).second());
    const __m128 *e=p+_n128;
    for(;p!=e;) *(p++)=_mm_add_ps(*(q++),*(r++));
    return *this;
  }

  template <>
  template <>
  DbShortDataArray& DbShortDataArray::operator=(
      const ArrayExpression<ArraySum<DbShortDataArray,DbShortDataArray>,
                            double>&& EA) {
    typedef ArraySum<DbShortDataArray,DbShortDataArray> SType;
    assert((bool)(*this));
    assert((bool)EA);
    assert(size()<=EA.size());
    __m128d *p=reinterpret_cast<__m128d*>(this->head());
    const __m128d *e=p+_n128;
    __m128d *q=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).first());
    __m128d *r=reinterpret_cast<__m128d*>(
                                static_cast<const SType&>(EA).second());
    for(;p!=e;) *(p++)=_mm_add_pd(*(q++),*(r++));
    return *this;
  }

}

#endif

