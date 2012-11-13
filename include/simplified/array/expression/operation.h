
#ifndef _Array_Expression_Operation_H_
#define _Array_Expression_Operation_H_

#include "array/expression/sum.h"
#include "array/expression/substract.h"
#include "array/expression/multiple.h"

namespace mysimulator {

  template <typename T,typename E>
  ArraySum<Array<Intrinsic<T>>,E>
  operator+(Array<Intrinsic<T>> const& A, E const& B) {
    return ArraySum<Array<Intrinsic<T>>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArraySum<ArraySum<EA,EB>,E>
  operator+(ArraySum<EA,EB> const& A, E const& B) {
    return ArraySum<ArraySum<EA,EB>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArraySum<ArraySub<EA,EB>,E>
  operator+(ArraySub<EA,EB> const& A, E const& B) {
    return ArraySum<ArraySub<EA,EB>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArraySum<ArrayMul<EA,EB>,E>
  operator+(ArrayMul<EA,EB> const& A, E const& B) {
    return ArraySum<ArrayMul<EA,EB>,E>(A,B);
  }

  template <typename T1,typename T2>
  ArraySum<Intrinsic<T1>,Array<Intrinsic<T2>>>
  operator+(Intrinsic<T1> const& A, Array<Intrinsic<T2>> const& B) {
    return ArraySum<Intrinsic<T1>,Array<Intrinsic<T2>>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArraySum<Intrinsic<T>,ArraySum<EA,EB>>
  operator+(Intrinsic<T> const& A, ArraySum<EA,EB> const& B) {
    return ArraySum<Intrinsic<T>,ArraySum<EA,EB>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArraySum<Intrinsic<T>,ArraySub<EA,EB>>
  operator+(Intrinsic<T> const& A, ArraySub<EA,EB> const& B) {
    return ArraySum<Intrinsic<T>,ArraySub<EA,EB>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArraySum<Intrinsic<T>,ArrayMul<EA,EB>>
  operator+(Intrinsic<T> const& A, ArrayMul<EA,EB> const& B) {
    return ArraySum<Intrinsic<T>,ArrayMul<EA,EB>>(A,B);
  }

  template <typename T,typename E>
  ArraySub<Array<Intrinsic<T>>,E>
  operator-(Array<Intrinsic<T>> const& A, E const& B) {
    return ArraySub<Array<Intrinsic<T>>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArraySub<ArraySum<EA,EB>,E>
  operator-(ArraySum<EA,EB> const& A, E const& B) {
    return ArraySub<ArraySum<EA,EB>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArraySub<ArraySub<EA,EB>,E>
  operator-(ArraySub<EA,EB> const& A, E const& B) {
    return ArraySub<ArraySub<EA,EB>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArraySub<ArrayMul<EA,EB>,E>
  operator-(ArrayMul<EA,EB> const& A, E const& B) {
    return ArraySub<ArrayMul<EA,EB>,E>(A,B);
  }

  template <typename T1,typename T2>
  ArraySub<Intrinsic<T1>,Array<Intrinsic<T2>>>
  operator-(Intrinsic<T1> const& A, Array<Intrinsic<T2>> const& B) {
    return ArraySub<Intrinsic<T1>,Array<Intrinsic<T2>>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArraySub<Intrinsic<T>,ArraySum<EA,EB>>
  operator-(Intrinsic<T> const& A, ArraySum<EA,EB> const& B) {
    return ArraySub<Intrinsic<T>,ArraySum<EA,EB>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArraySub<Intrinsic<T>,ArraySub<EA,EB>>
  operator-(Intrinsic<T> const& A, ArraySub<EA,EB> const& B) {
    return ArraySub<Intrinsic<T>,ArraySub<EA,EB>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArraySub<Intrinsic<T>,ArrayMul<EA,EB>>
  operator-(Intrinsic<T> const& A,ArrayMul<EA,EB> const& B) {
    return ArraySub<Intrinsic<T>,ArrayMul<EA,EB>>(A,B);
  }

  template <typename T,typename E>
  ArrayMul<Array<Intrinsic<T>>,E>
  operator*(Array<Intrinsic<T>> const& A, E const& B) {
    return ArrayMul<Array<Intrinsic<T>>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArrayMul<ArraySum<EA,EB>,E>
  operator*(ArraySum<EA,EB> const& A, E const& B) {
    return ArrayMul<ArraySum<EA,EB>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArrayMul<ArraySub<EA,EB>,E>
  operator*(ArraySub<EA,EB> const& A, E const& B) {
    return ArrayMul<ArraySub<EA,EB>,E>(A,B);
  }

  template <typename EA,typename EB,typename E>
  ArrayMul<ArrayMul<EA,EB>,E>
  operator*(ArrayMul<EA,EB> const& A, E const& B) {
    return ArrayMul<ArrayMul<EA,EB>,E>(A,B);
  }

  template <typename T1,typename T2>
  ArrayMul<Intrinsic<T1>,Array<Intrinsic<T2>>>
  operator*(Intrinsic<T1> const& A, Array<Intrinsic<T2>> const& B) {
    return ArrayMul<Intrinsic<T1>,Array<Intrinsic<T2>>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArrayMul<Intrinsic<T>,ArraySum<EA,EB>>
  operator*(Intrinsic<T> const& A, ArraySum<EA,EB> const& B) {
    return ArrayMul<Intrinsic<T>,ArraySum<EA,EB>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArrayMul<Intrinsic<T>,ArraySub<EA,EB>>
  operator*(Intrinsic<T> const& A, ArraySub<EA,EB> const& B) {
    return ArrayMul<Intrinsic<T>,ArraySub<EA,EB>>(A,B);
  }

  template <typename T,typename EA,typename EB>
  ArrayMul<Intrinsic<T>,ArrayMul<EA,EB>>
  operator*(Intrinsic<T> const& A, ArrayMul<EA,EB> const& B) {
    return ArrayMul<Intrinsic<T>,ArrayMul<EA,EB>>(A,B);
  }

}

#endif

