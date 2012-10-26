
#ifndef _Vector_Array_Expression_Operation_H_
#define _Vector_Array_Expression_Operation_H_

#include "vec-array/expression-sum.h"
#include "vec-array/expression-substract.h"
#include "vec-array/expression-multiple.h"
#include "vec-array/expression-divide.h"

namespace mysimulator {

  template <typename T> class VectorArray;

  template <typename T1,typename E>
  VecArraySum<VectorArray<T1>,E>
  operator+(VectorArray<T1> const& A, E const& B) {
    return VecArraySum<VectorArray<T1>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArraySum<VecArraySum<EA,EB>,E>
  operator+(VecArraySum<EA,EB> const & A, E const& B) {
    return VecArraySum<VecArraySum<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArraySum<VecArraySub<EA,EB>,E>
  operator+(VecArraySub<EA,EB> const & A, E const& B) {
    return VecArraySum<VecArraySub<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArraySum<VecArrayMul<EA,EB>,E>
  operator+(VecArrayMul<EA,EB> const & A, E const& B) {
    return VecArraySum<VecArrayMul<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArraySum<VecArrayDiv<EA,EB>,E>
  operator+(VecArrayDiv<EA,EB> const & A, E const& B) {
    return VecArraySum<VecArrayDiv<EA,EB>,E>(A,B);
  }

  template <typename T1,typename T2>
  VecArraySum<Intrinsic<T1>,VectorArray<T2>>
  operator+(Intrinsic<T1> const& A,VectorArray<T2> const& B) {
    return VecArraySum<Intrinsic<T1>,VectorArray<T2>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArraySum<Intrinsic<T>,VecArraySum<EA,EB>>
  operator+(Intrinsic<T> const& A,VecArraySum<EA,EB> const& B) {
    return VecArraySum<Intrinsic<T>,VecArraySum<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArraySum<Intrinsic<T>,VecArraySub<EA,EB>>
  operator+(Intrinsic<T> const& A,VecArraySub<EA,EB> const& B) {
    return VecArraySum<Intrinsic<T>,VecArraySub<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArraySum<Intrinsic<T>,VecArrayMul<EA,EB>>
  operator+(Intrinsic<T> const& A,VecArrayMul<EA,EB> const& B) {
    return VecArraySum<Intrinsic<T>,VecArrayMul<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArraySum<Intrinsic<T>,VecArrayDiv<EA,EB>>
  operator+(Intrinsic<T> const& A,VecArrayDiv<EA,EB> const& B) {
    return VecArraySum<Intrinsic<T>,VecArrayDiv<EA,EB>>(A,B);
  }

  template <typename T1,typename E>
  VecArraySub<VectorArray<T1>,E>
  operator-(VectorArray<T1> const& A, E const& B) {
    return VecArraySub<VectorArray<T1>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArraySub<VecArraySum<EA,EB>,E>
  operator-(VecArraySum<EA,EB> const & A, E const& B) {
    return VecArraySub<VecArraySum<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArraySub<VecArraySub<EA,EB>,E>
  operator-(VecArraySub<EA,EB> const & A, E const& B) {
    return VecArraySub<VecArraySub<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArraySub<VecArrayMul<EA,EB>,E>
  operator-(VecArrayMul<EA,EB> const & A, E const& B) {
    return VecArraySub<VecArrayMul<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArraySub<VecArrayDiv<EA,EB>,E>
  operator-(VecArrayDiv<EA,EB> const & A, E const& B) {
    return VecArraySub<VecArrayDiv<EA,EB>,E>(A,B);
  }

  template <typename T1,typename T2>
  VecArraySub<Intrinsic<T1>,VectorArray<T2>>
  operator-(Intrinsic<T1> const& A,VectorArray<T2> const& B) {
    return VecArraySub<Intrinsic<T1>,VectorArray<T2>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArraySub<Intrinsic<T>,VecArraySum<EA,EB>>
  operator-(Intrinsic<T> const& A,VecArraySum<EA,EB> const& B) {
    return VecArraySub<Intrinsic<T>,VecArraySum<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArraySub<Intrinsic<T>,VecArraySub<EA,EB>>
  operator-(Intrinsic<T> const& A,VecArraySub<EA,EB> const& B) {
    return VecArraySub<Intrinsic<T>,VecArraySub<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArraySub<Intrinsic<T>,VecArrayMul<EA,EB>>
  operator-(Intrinsic<T> const& A,VecArrayMul<EA,EB> const& B) {
    return VecArraySub<Intrinsic<T>,VecArrayMul<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArraySub<Intrinsic<T>,VecArrayDiv<EA,EB>>
  operator-(Intrinsic<T> const& A,VecArrayDiv<EA,EB> const& B) {
    return VecArraySub<Intrinsic<T>,VecArrayDiv<EA,EB>>(A,B);
  }

  template <typename T1,typename E>
  VecArrayMul<VectorArray<T1>,E>
  operator*(VectorArray<T1> const& A, E const& B) {
    return VecArrayMul<VectorArray<T1>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArrayMul<VecArraySum<EA,EB>,E>
  operator*(VecArraySum<EA,EB> const & A, E const& B) {
    return VecArrayMul<VecArraySum<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArrayMul<VecArraySub<EA,EB>,E>
  operator*(VecArraySub<EA,EB> const & A, E const& B) {
    return VecArrayMul<VecArraySub<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArrayMul<VecArrayMul<EA,EB>,E>
  operator*(VecArrayMul<EA,EB> const & A, E const& B) {
    return VecArrayMul<VecArrayMul<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArrayMul<VecArrayDiv<EA,EB>,E>
  operator*(VecArrayDiv<EA,EB> const & A, E const& B) {
    return VecArrayMul<VecArrayDiv<EA,EB>,E>(A,B);
  }

  template <typename T1,typename T2>
  VecArrayMul<Intrinsic<T1>,VectorArray<T2>>
  operator*(Intrinsic<T1> const& A,VectorArray<T2> const& B) {
    return VecArrayMul<Intrinsic<T1>,VectorArray<T2>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArrayMul<Intrinsic<T>,VecArraySum<EA,EB>>
  operator*(Intrinsic<T> const& A,VecArraySum<EA,EB> const& B) {
    return VecArrayMul<Intrinsic<T>,VecArraySum<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArrayMul<Intrinsic<T>,VecArraySub<EA,EB>>
  operator*(Intrinsic<T> const& A,VecArraySub<EA,EB> const& B) {
    return VecArrayMul<Intrinsic<T>,VecArraySub<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArrayMul<Intrinsic<T>,VecArrayMul<EA,EB>>
  operator*(Intrinsic<T> const& A,VecArrayMul<EA,EB> const& B) {
    return VecArrayMul<Intrinsic<T>,VecArrayMul<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArrayMul<Intrinsic<T>,VecArrayDiv<EA,EB>>
  operator*(Intrinsic<T> const& A,VecArrayDiv<EA,EB> const& B) {
    return VecArrayMul<Intrinsic<T>,VecArrayDiv<EA,EB>>(A,B);
  }

  template <typename T1,typename E>
  VecArrayDiv<VectorArray<T1>,E>
  operator/(VectorArray<T1> const& A, E const& B) {
    return VecArrayDiv<VectorArray<T1>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArrayDiv<VecArraySum<EA,EB>,E>
  operator/(VecArraySum<EA,EB> const & A, E const& B) {
    return VecArrayDiv<VecArraySum<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArrayDiv<VecArraySub<EA,EB>,E>
  operator/(VecArraySub<EA,EB> const & A, E const& B) {
    return VecArrayDiv<VecArraySub<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArrayDiv<VecArrayMul<EA,EB>,E>
  operator/(VecArrayMul<EA,EB> const & A, E const& B) {
    return VecArrayDiv<VecArrayMul<EA,EB>,E>(A,B);
  }
  template <typename EA,typename EB,typename E>
  VecArrayDiv<VecArrayDiv<EA,EB>,E>
  operator/(VecArrayDiv<EA,EB> const & A, E const& B) {
    return VecArrayDiv<VecArrayDiv<EA,EB>,E>(A,B);
  }

  template <typename T1,typename T2>
  VecArrayDiv<Intrinsic<T1>,VectorArray<T2>>
  operator/(Intrinsic<T1> const& A,VectorArray<T2> const& B) {
    return VecArrayDiv<Intrinsic<T1>,VectorArray<T2>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArrayDiv<Intrinsic<T>,VecArraySum<EA,EB>>
  operator/(Intrinsic<T> const& A,VecArraySum<EA,EB> const& B) {
    return VecArrayDiv<Intrinsic<T>,VecArraySum<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArrayDiv<Intrinsic<T>,VecArraySub<EA,EB>>
  operator/(Intrinsic<T> const& A,VecArraySub<EA,EB> const& B) {
    return VecArrayDiv<Intrinsic<T>,VecArraySub<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArrayDiv<Intrinsic<T>,VecArrayMul<EA,EB>>
  operator/(Intrinsic<T> const& A,VecArrayMul<EA,EB> const& B) {
    return VecArrayDiv<Intrinsic<T>,VecArrayMul<EA,EB>>(A,B);
  }
  template <typename T,typename EA,typename EB>
  VecArrayDiv<Intrinsic<T>,VecArrayDiv<EA,EB>>
  operator/(Intrinsic<T> const& A,VecArrayDiv<EA,EB> const& B) {
    return VecArrayDiv<Intrinsic<T>,VecArrayDiv<EA,EB>>(A,B);
  }

}

#endif


