
#ifndef _Array_Expression_Size_Check_H_
#define _Array_Expression_Size_Check_H_

#include "array/interface.h"

namespace mysimulator {

  template <typename T,typename E>
  bool __is_expression_size_same(Intrinsic<T> const&,E const&) { return true; }

  template <typename E,typename T>
  bool __is_expression_size_same(E const&,Intrinsic<T> const&) { return true; }

  template <typename T1,typename T2>
  bool __is_expression_size_same(Array<Intrinsic<T1>> const& A,
                                 Array<Intrinsic<T2>> const& B) {
    return A.size() == B.size();
  }
  template <typename T,typename EA,typename EB>
  bool __is_expression_size_same(Array<Intrinsic<T>> const& A,
                                 ArraySum<EA,EB> const& B) {
    return A.size() == B.size();
  }
  template <typename T,typename EA,typename EB>
  bool __is_expression_size_same(Array<Intrinsic<T>> const& A,
                                 ArraySub<EA,EB> const& B) {
    return A.size() == B.size();
  }
  template <typename T,typename EA,typename EB>
  bool __is_expression_size_same(Array<Intrinsic<T>> const& A,
                                 ArrayMul<EA,EB> const& B) {
    return A.size() == B.size();
  }
  template <typename T,typename EA,typename EB>
  bool __is_expression_size_same(Array<Intrinsic<T>> const& A,
                                 ArrayDiv<EA,EB> const& B) {
    return A.size() == B.size();
  }

  template <typename EA,typename EB,typename T>
  bool __is_expression_size_same(ArraySum<EA,EB> const& A,
                                 Array<Intrinsic<T>> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArraySum<EA,EB> const& A,
                                 ArraySum<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArraySum<EA,EB> const& A,
                                 ArraySub<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArraySum<EA,EB> const& A,
                                 ArrayMul<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArraySum<EA,EB> const& A,
                                 ArrayDiv<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename T>
  bool __is_expression_size_same(ArraySub<EA,EB> const& A,
                                 Array<Intrinsic<T>> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArraySub<EA,EB> const& A,
                                 ArraySum<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArraySub<EA,EB> const& A,
                                 ArraySub<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArraySub<EA,EB> const& A,
                                 ArrayMul<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArraySub<EA,EB> const& A,
                                 ArrayDiv<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename T>
  bool __is_expression_size_same(ArrayMul<EA,EB> const& A,
                                 Array<Intrinsic<T>> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArrayMul<EA,EB> const& A,
                                 ArraySum<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArrayMul<EA,EB> const& A,
                                 ArraySub<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArrayMul<EA,EB> const& A,
                                 ArrayMul<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArrayMul<EA,EB> const& A,
                                 ArrayDiv<EC,ED> const& B) {
    return A.size() == B.size();
  }

  template <typename EA,typename EB,typename T>
  bool __is_expression_size_same(ArrayDiv<EA,EB> const& A,
                                 Array<Intrinsic<T>> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArrayDiv<EA,EB> const& A,
                                 ArraySum<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArrayDiv<EA,EB> const& A,
                                 ArraySub<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArrayDiv<EA,EB> const& A,
                                 ArrayMul<EC,ED> const& B) {
    return A.size() == B.size();
  }
  template <typename EA,typename EB,typename EC,typename ED>
  bool __is_expression_size_same(ArrayDiv<EA,EB> const& A,
                                 ArrayDiv<EC,ED> const& B) {
    return A.size() == B.size();
  }

}

#endif

