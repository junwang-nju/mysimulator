
#ifndef _Array_Expression_Operation_H_
#define _Array_Expression_Operation_H_

#include "array/expression/sum.h"
#include "array/expression/substract.h"

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

}

#endif

