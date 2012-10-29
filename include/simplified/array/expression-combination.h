
#ifndef _Array_Expression_Combination_H_
#define _Array_Expression_Combination_H_

#include "array/expression-sum.h"
#include "array/expression-substract.h"

namespace mysimulator {

  template <typename T1,typename T2,typename E>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,E>
  operator+(const Intrinsic<T1>& a,const ArraySum<Intrinsic<T2>,E>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    E>(a+b.first(),b.second());
  }
  template <typename T1,typename T2,typename E>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,E>
  operator+(const Intrinsic<T1>& a,const ArraySum<E,Intrinsic<T2>>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    E>(a+b.second(),b.first());
  }

  template <typename T1,typename T2,typename E>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,E>
  operator+(const Intrinsic<T1>& a,const ArraySub<E,Intrinsic<T2>>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    E>(a-b.second(),b.first());
  }
  template <typename T1,typename T2,typename E>
  ArraySub<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,E>
  operator+(const Intrinsic<T1>& a,const ArraySub<Intrinsic<T2>,E>& b) {
    return ArraySub<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    E>(a+b.first(),b.second());
  }

  template <typename T1,typename T2,typename E>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,E>
  operator+(const ArraySum<Intrinsic<T2>,E>& a,const Intrinsic<T1>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    E>(a.first()+b,a.second());
  }
  template <typename T1,typename T2,typename E>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,E>
  operator+(const ArraySum<E,Intrinsic<T2>>& a,const Intrinsic<T1>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    E>(a.second()+b,a.first());
  }

  template <typename T1,typename T2,typename E>
  ArraySub<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,E>
  operator+(const ArraySub<Intrinsic<T2>,E>& a,const Intrinsic<T1>& b) {
    return ArraySub<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    E>(a.first()+b,a.second());
  }
  template <typename T1,typename T2,typename E>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,E>
  operator+(const ArraySub<E,Intrinsic<T2>>& a,const Intrinsic<T1>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    E>(b-a.second(),a.first());
  }

  template <typename T1,typename T2,typename E1,typename E2>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
           ArraySum<E1,E2>>
  operator+(const ArraySum<Intrinsic<T1>,E1>& a,
            const ArraySum<Intrinsic<T2>,E2>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    ArraySum<E1,E2>>(a.first()+b.first(),a.second()+b.second());
  }
  template <typename T1,typename T2,typename E1,typename E2>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
           ArraySum<E1,E2>>
  operator+(const ArraySum<E1,Intrinsic<T1>>& a,
            const ArraySum<Intrinsic<T2>,E2>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    ArraySum<E1,E2>>(a.second()+b.first(),a.first()+b.second());
  }
  template <typename T1,typename T2,typename E1,typename E2>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
           ArraySum<E1,E2>>
  operator+(const ArraySum<Intrinsic<T1>,E1>& a,
            const ArraySum<E2,Intrinsic<T2>>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    ArraySum<E1,E2>>(a.first()+b.second(),a.second()+b.first());
  }
  template <typename T1,typename T2,typename E1,typename E2>
  ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
           ArraySum<E1,E2>>
  operator+(const ArraySum<E1,Intrinsic<T1>>& a,
            const ArraySum<E2,Intrinsic<T2>>& b) {
    return ArraySum<Intrinsic<typename __dual_selector<T1,T2,__sum_flag>::Type>,
                    ArraySum<E1,E2>>(a.second()+b.second(),a.first()+b.first());
  }

  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySum<Intrinsic<T1>,E1>& a,
            const ArraySub<Intrinsic<T2>,E2>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySum<E1,Intrinsic<T1>>& a,
            const ArraySub<Intrinsic<T2>,E2>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySum<Intrinsic<T1>,E1>& a,
            const ArraySub<E2,Intrinsic<T2>>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySum<E1,Intrinsic<T1>>& a,
            const ArraySub<E2,Intrinsic<T2>>& b) {
  }

  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySub<Intrinsic<T1>,E1>& a,
            const ArraySum<Intrinsic<T2>,E2>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySub<E1,Intrinsic<T1>>& a,
            const ArraySum<Intrinsic<T2>,E2>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySub<Intrinsic<T1>,E1>& a,
            const ArraySum<E2,Intrinsic<T2>>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySub<E1,Intrinsic<T1>>& a,
            const ArraySum<E2,Intrinsic<T2>>& b) {
  }

  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySub<Intrinsic<T1>,E1>& a,
            const ArraySub<Intrinsic<T2>,E2>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySub<E1,Intrinsic<T1>>& a,
            const ArraySub<Intrinsic<T2>,E2>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySub<Intrinsic<T1>,E1>& a,
            const ArraySub<E2,Intrinsic<T2>>& b) {
  }
  template <typename T1,typename T2,typename E1,typename E2>
  operator+(const ArraySub<E1,Intrinsic<T1>>& a,
            const ArraySub<E2,Intrinsic<T2>>& b) {
  }

}

#endif

