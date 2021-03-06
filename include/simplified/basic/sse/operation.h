
#ifndef _Basic_SSE_Operation_H_
#define _Basic_SSE_Operation_H_

#include "basic/sse/value-type.h"
#include <cassert>

namespace mysimulator {

  template <typename T>
  typename __sse_value<T>::Type
  Set128(const T& D) {
    assert("This Operation is Not available!\n");
    return (typename __sse_value<T>::Type)0;
  }

  template <>
  __m128i Set128<int>(const int& D) { return _mm_set1_epi32(D); }

  template <>
  __m128i Set128<long>(const long& D) { return _mm_set1_epi32(D); }

  template <>
  __m128 Set128<float>(const float& D) { return _mm_set1_ps(D); }

  template <>
  __m128d Set128<double>(const double& D) { return _mm_set1_pd(D); }

  template <typename T>
  typename __sse_value<T>::Type
  Sum128(typename __sse_value<T>::Type const& a,
         typename __sse_value<T>::Type const& b) {
    assert("This Operation is Not available!\n");
    return (typename __sse_value<T>::Type)0;
  }

  template <>
  __m128i Sum128<int>(__m128i const& a, __m128i const& b) {
    return _mm_add_epi32(a,b);
  }

  template <>
  __m128i Sum128<long>(__m128i const& a, __m128i const& b) {
    return _mm_add_epi32(a,b);
  }

  template <>
  __m128 Sum128<float>(__m128 const& a, __m128 const& b) {
    return _mm_add_ps(a,b);
  }

  template <>
  __m128d Sum128<double>(__m128d const& a, __m128d const& b) {
    return _mm_add_pd(a,b);
  }

  template <typename T>
  typename __sse_value<T>::Type
  Sub128(typename __sse_value<T>::Type const& a,
         typename __sse_value<T>::Type const& b) {
    assert("This Operation is Not available!\n");
    return (typename __sse_value<T>::Type)0;
  }

  template <>
  __m128i Sub128<int>(__m128i const& a, __m128i const& b) {
    return _mm_sub_epi32(a,b);
  }

  template <>
  __m128i Sub128<long>(__m128i const& a, __m128i const& b) {
    return _mm_sub_epi32(a,b);
  }

  template <>
  __m128 Sub128<float>(__m128 const& a, __m128 const& b) {
    return _mm_sub_ps(a,b);
  }

  template <>
  __m128d Sub128<double>(__m128d const& a, __m128d const& b) {
    return _mm_sub_pd(a,b);
  }

  template <typename T>
  typename __sse_value<T>::Type
  Mul128(typename __sse_value<T>::Type const& a,
         typename __sse_value<T>::Type const& b) {
    assert("This Operation is Not available!\n");
    return (typename __sse_value<T>::Type)0;
  }

  template <>
  __m128i Mul128<int>(__m128i const& a, __m128i const& b) {
    return _mm_mullo_epi32(a,b);
  }

  template <>
  __m128i Mul128<long>(__m128i const& a, __m128i const& b) {
    return _mm_mullo_epi32(a,b);
  }

  template <>
  __m128 Mul128<float>(__m128 const& a, __m128 const& b) {
    return _mm_mul_ps(a,b);
  }

  template <>
  __m128d Mul128<double>(__m128d const& a, __m128d const& b) {
    return _mm_mul_pd(a,b);
  }

  template <typename T>
  typename __sse_value<T>::Type
  Div128(typename __sse_value<T>::Type const& a,
         typename __sse_value<T>::Type const& b) {
    assert("This Operation is Not available!\n");
    return (typename __sse_value<T>::Type)0;
  }

  template <>
  __m128 Div128<float>(__m128 const& a, __m128 const& b) {
    return _mm_div_ps(a,b);
  }

  template <>
  __m128d Div128<double>(__m128d const& a,__m128d const& b) {
    return _mm_div_pd(a,b);
  }

  template <typename T>
  T SumElement128(typename __sse_value<T>::Type const& a) {
    assert("This Operation is Not available!\n");
    return 0;
  }

  template <>
  int SumElement128<int>(__m128i const& a) {
    const int *p=(const int*)(&a);
    return p[0]+p[1]+p[2]+p[3];
  }

  template <>
  float SumElement128<float>(__m128 const& a) {
    const float *p=(const float*)(&a);
    return p[0]+p[1]+p[2]+p[3];
  }

  template <>
  double SumElement128<double>(__m128d const& a) {
    const double *p=(const double*)(&a);
    return p[0]+p[1];
  }

}

#endif

