
#ifndef _Array_ShortDataArray_Interface_H_
#define _Array_ShortDataArray_Interface_H_

#include "array/data-array-interface.h"

#ifndef _HAVE_SSE2
#error "SSE2 is suggested for Short Data Array! try -msse2 -D_HAVE_SSE2"
#endif

#include <emmintrin.h>

namespace mysimulator {

  template <typename T>
  class Array<T,ArrayFormat::ShortDataArray> : public DataArray<T> {

    public:

      typedef Array<T,ArrayFormat::ShortDataArray>   Type;
      typedef DataArray<T>  ParentType;

    private:

      unsigned int _n128;

    public:

      Array() : ParentType(), _n128(0) {}
      Array(unsigned int size) : Array() { allocate(size); }
      Array(const Type&) = delete;
      virtual ~Array() { ParentType::~DataArray(); }

      Type& operator=(const Type& A) {
        assert((bool)(*this));
        assert((bool)A);
        assert(this->size()<=A.size());
        __m128i* p=reinterpret_cast<__m128i*>(this->head());
        __m128i* q=reinterpret_cast<__m128i*>(A.head());
        const __m128i* e=p+_n128;
        for(;p!=e;) _mm_store_si128(p++,*(q++));
        return *this;
      }

      Type& operator=(const T& D) { return ParentType::operator=(D); }

      virtual void allocate(unsigned int size) override {
        unsigned int byte_size=size*sizeof(T);
        assert(byte_size<=ShortThresholdByte);
        ParentType::allocate(size);
        _n128=(byte_size>>4);
      }

  };

  template <>
  Array<int,ArrayFormat::ShortDataArray>&
  Array<int,ArrayFormat::ShortDataArray>::operator=(const int& D) {
    assert((bool)(*this));
    __m128i* p=reinterpret_cast<__m128i*>(this->head());
    const __m128i* e=p+_n128;
    for(;p!=e;) *(p++)=_mm_set1_epi32(D);
    return *this;
  }

  template <>
  Array<double,ArrayFormat::ShortDataArray>&
  Array<double,ArrayFormat::ShortDataArray>::operator=(const double& D) {
    assert((bool)(*this));
    __m128d* p=reinterpret_cast<__m128d*>(this->head());
    const __m128d* e=p+_n128;
    for(;p!=e;)   *(p++)=_mm_set1_pd(D);
    return *this;
  }

}

#endif

