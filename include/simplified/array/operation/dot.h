
#ifndef _Array_Operation_Dot_H_
#define _Array_Operation_Dot_H_

#include "array/kernel/simple.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K,typename E>
  typename __dual_selector<T,typename E::value_type,__mul>::Type
  Dot(Array<Intrinsic<T>,K,true> const& A, E const& B) {
    return __dot_simple(A,B);
  }

  template <typename EA,typename EB,typename E>
  typename __dual_selector<typename ArraySum<EA,EB>::value_type,
                           typename E::value_type,__mul>::Type
  Dot(ArraySum<EA,EB> const& A, E const& B) {
    return __dot_simple(A,B);
  }

  template <typename EA,typename EB,typename E>
  typename __dual_selector<typename ArraySub<EA,EB>::value_type,
                           typename E::value_type,__mul>::Type
  Dot(ArraySub<EA,EB> const& A, E const& B) {
    return __dot_simple(A,B);
  }

  template <typename EA,typename EB,typename E>
  typename __dual_selector<typename ArrayMul<EA,EB>::value_type,
                           typename E::value_type,__mul>::Type
  Dot(ArrayMul<EA,EB> const& A, E const& B) {
    return __dot_simple(A,B);
  }

  template <typename EA,typename EB,typename E>
  typename __dual_selector<typename ArrayDiv<EA,EB>::value_type,
                           typename E::value_type,__mul>::Type
  Dot(ArrayDiv<EA,EB> const& A,E const& B) {
    return __dot_simple(A,B);
  }

}

#include "array/kernel/sse.h"

namespace mysimulator {

  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             ArraySum<EA,EB,double,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             ArraySub<EA,EB,double,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             ArrayMul<EA,EB,double,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(Array<Double,ArrayKernelName::SSE,true> const& A,
             ArrayDiv<EA,EB,double,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(ArraySum<EA,EB,double,ArrayKernelName::SSE> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySum<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArraySum<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySum<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArraySub<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySum<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArrayMul<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySum<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArrayDiv<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(ArraySub<EA,EB,double,ArrayKernelName::SSE> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySub<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArraySum<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySub<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArraySub<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySub<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArrayMul<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArraySub<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArrayDiv<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(ArrayMul<EA,EB,double,ArrayKernelName::SSE> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayMul<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArraySum<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayMul<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArraySub<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayMul<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArrayMul<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayMul<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArrayDiv<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  double Dot(ArrayDiv<EA,EB,double,ArrayKernelName::SSE> const& A,
             Array<Double,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayDiv<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArraySum<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayDiv<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArraySub<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayDiv<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArrayMul<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  double Dot(ArrayDiv<EA,EB,double,ArrayKernelName::SSE> const& A,
             ArrayDiv<EC,ED,double,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }

  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            ArraySum<EA,EB,float,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            ArraySub<EA,EB,float,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            ArrayMul<EA,EB,float,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(Array<Float,ArrayKernelName::SSE,true> const& A,
            ArrayDiv<EA,EB,float,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(ArraySum<EA,EB,float,ArrayKernelName::SSE> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySum<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArraySum<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySum<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArraySub<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySum<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArrayMul<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySum<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArrayDiv<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(ArraySub<EA,EB,float,ArrayKernelName::SSE> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySub<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArraySum<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySub<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArraySub<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySub<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArrayMul<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArraySub<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArrayDiv<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(ArrayMul<EA,EB,float,ArrayKernelName::SSE> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayMul<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArraySum<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayMul<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArraySub<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayMul<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArrayMul<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayMul<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArrayDiv<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  float Dot(ArrayDiv<EA,EB,float,ArrayKernelName::SSE> const& A,
            Array<Float,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayDiv<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArraySum<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayDiv<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArraySub<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayDiv<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArrayMul<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  float Dot(ArrayDiv<EA,EB,float,ArrayKernelName::SSE> const& A,
            ArrayDiv<EC,ED,float,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }

  int Dot(Array<Int,ArrayKernelName::SSE,true> const& A,
          Array<Int,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(Array<Int,ArrayKernelName::SSE,true> const& A,
          ArraySum<EA,EB,int,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(Array<Int,ArrayKernelName::SSE,true> const& A,
          ArraySub<EA,EB,int,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(Array<Int,ArrayKernelName::SSE,true> const& A,
          ArrayMul<EA,EB,int,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(ArraySum<EA,EB,int,ArrayKernelName::SSE> const& A,
          Array<Int,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySum<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArraySum<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySum<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArraySub<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySum<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArrayMul<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(ArraySub<EA,EB,int,ArrayKernelName::SSE> const& A,
          Array<Int,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySub<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArraySum<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySub<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArraySub<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArraySub<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArrayMul<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  int Dot(ArrayMul<EA,EB,int,ArrayKernelName::SSE> const& A,
          Array<Int,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArrayMul<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArraySum<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArrayMul<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArraySub<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  int Dot(ArrayMul<EA,EB,int,ArrayKernelName::SSE> const& A,
          ArrayMul<EC,ED,int,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }

  long Dot(Array<Long,ArrayKernelName::SSE,true> const& A,
           Array<Long,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(Array<Long,ArrayKernelName::SSE,true> const& A,
           ArraySum<EA,EB,long,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(Array<Long,ArrayKernelName::SSE,true> const& A,
           ArraySub<EA,EB,long,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(Array<Long,ArrayKernelName::SSE,true> const& A,
           ArrayMul<EA,EB,long,ArrayKernelName::SSE>& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(ArraySum<EA,EB,long,ArrayKernelName::SSE> const& A,
           Array<Long,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySum<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArraySum<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySum<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArraySub<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySum<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArrayMul<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(ArraySub<EA,EB,long,ArrayKernelName::SSE> const& A,
           Array<Long,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySub<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArraySum<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySub<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArraySub<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArraySub<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArrayMul<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB>
  long Dot(ArrayMul<EA,EB,long,ArrayKernelName::SSE> const& A,
           Array<Long,ArrayKernelName::SSE,true> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArrayMul<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArraySum<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArrayMul<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArraySub<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }
  template <typename EA,typename EB,typename EC,typename ED>
  long Dot(ArrayMul<EA,EB,long,ArrayKernelName::SSE> const& A,
           ArrayMul<EC,ED,long,ArrayKernelName::SSE> const& B) {
    return __dot_sse(A,B);
  }

  template <typename T,typename E>
  typename __dual_selector<T,typename E::value_type,__mul>::Type
  Dot(Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& A, E const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT,typename E>
  typename __dual_selector<typename ArraySum<EA,EB>::value_type,
                           typename E::value_type,__mul>::Type
  Dot(ArraySum<EA,EB,vT,ArrayKernelName::Direct3D> const& A, E const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT,typename E>
  typename __dual_selector<typename ArraySub<EA,EB>::value_type,
                           typename E::value_type,__mul>::Type
  Dot(ArraySub<EA,EB,vT,ArrayKernelName::Direct3D> const& A, E const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT,typename E>
  typename __dual_selector<typename ArrayMul<EA,EB>::value_type,
                           typename E::value_type,__mul>::Type
  Dot(ArrayMul<EA,EB,vT,ArrayKernelName::Direct3D> const& A, E const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT,typename E>
  typename __dual_selector<typename ArrayDiv<EA,EB>::value_type,
                           typename E::value_type,__mul>::Type
  Dot(ArrayDiv<EA,EB,vT,ArrayKernelName::Direct3D> const& A, E const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename E,typename T>
  typename __dual_selector<typename E::value_type,T,__mul>::Type
  Dot(E const& A, Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename E,typename EA,typename EB,typename vT>
  typename __dual_selector<typename E::value_type,
                           typename ArraySum<EA,EB>::value_type,__mul>::Type
  Dot(E const& A,ArraySum<EA,EB,vT,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename E,typename EA,typename EB,typename vT>
  typename __dual_selector<typename E::value_type,
                           typename ArraySub<EA,EB>::value_type,__mul>::Type
  Dot(E const& A,ArraySub<EA,EB,vT,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename E,typename EA,typename EB,typename vT>
  typename __dual_selector<typename E::value_type,
                           typename ArrayMul<EA,EB>::value_type,__mul>::Type
  Dot(E const& A,ArrayMul<EA,EB,vT,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename E,typename EA,typename EB,typename vT>
  typename __dual_selector<typename E::value_type,
                           typename ArrayDiv<EA,EB>::value_type,__mul>::Type
  Dot(E const& A,ArrayDiv<EA,EB,vT,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename T1,typename T2>
  typename __dual_selector<T1,T2,__mul>::Type
  Dot(Array<Intrinsic<T1>,ArrayKernelName::Direct3D,true> const& A,
      Array<Intrinsic<T2>,ArrayKernelName::Direct3D,true> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename T,typename EA,typename EB,typename vT>
  typename __dual_selector<T,typename ArraySum<EA,EB>::value_type,__mul>::Type
  Dot(Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& A,
      ArraySum<EA,EB,vT,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename T,typename EA,typename EB,typename vT>
  typename __dual_selector<T,typename ArraySub<EA,EB>::value_type,__mul>::Type
  Dot(Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& A,
      ArraySub<EA,EB,vT,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename T,typename EA,typename EB,typename vT>
  typename __dual_selector<T,typename ArrayMul<EA,EB>::value_type,__mul>::Type
  Dot(Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& A,
      ArrayMul<EA,EB,vT,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename T,typename EA,typename EB,typename vT>
  typename __dual_selector<T,typename ArrayDiv<EA,EB>::value_type,__mul>::Type
  Dot(Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& A,
      ArrayDiv<EA,EB,vT,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT,typename T>
  typename __dual_selector<typename ArraySum<EA,EB>::value_type,T,__mul>::Type
  Dot(ArraySum<EA,EB,vT,ArrayKernelName::Direct3D> const& A,
      Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArraySum<EA,EB>::value_type,
                           typename ArraySum<EC,ED>::value_type,__mul>::Type
  Dot(ArraySum<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArraySum<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArraySum<EA,EB>::value_type,
                           typename ArraySub<EC,ED>::value_type,__mul>::Type
  Dot(ArraySum<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArraySub<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArraySum<EA,EB>::value_type,
                           typename ArrayMul<EC,ED>::value_type,__mul>::Type
  Dot(ArraySum<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArrayMul<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArraySum<EA,EB>::value_type,
                           typename ArrayDiv<EC,ED>::value_type,__mul>::Type
  Dot(ArraySum<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArrayDiv<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT,typename T>
  typename __dual_selector<typename ArraySub<EA,EB>::value_type,T,__mul>::Type
  Dot(ArraySub<EA,EB,vT,ArrayKernelName::Direct3D> const& A,
      Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArraySub<EA,EB>::value_type,
                           typename ArraySum<EC,ED>::value_type,__mul>::Type
  Dot(ArraySub<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArraySum<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArraySub<EA,EB>::value_type,
                           typename ArraySub<EC,ED>::value_type,__mul>::Type
  Dot(ArraySub<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArraySub<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArraySub<EA,EB>::value_type,
                           typename ArrayMul<EC,ED>::value_type,__mul>::Type
  Dot(ArraySub<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArrayMul<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArraySub<EA,EB>::value_type,
                           typename ArrayDiv<EC,ED>::value_type,__mul>::Type
  Dot(ArraySub<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArrayDiv<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT,typename T>
  typename __dual_selector<typename ArrayMul<EA,EB>::value_type,T,__mul>::Type
  Dot(ArrayMul<EA,EB,vT,ArrayKernelName::Direct3D> const& A,
      Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArrayMul<EA,EB>::value_type,
                           typename ArraySum<EC,ED>::value_type,__mul>::Type
  Dot(ArrayMul<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArraySum<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArrayMul<EA,EB>::value_type,
                           typename ArraySub<EC,ED>::value_type,__mul>::Type
  Dot(ArrayMul<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArraySub<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArrayMul<EA,EB>::value_type,
                           typename ArrayMul<EC,ED>::value_type,__mul>::Type
  Dot(ArrayMul<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArrayMul<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArrayMul<EA,EB>::value_type,
                           typename ArrayDiv<EC,ED>::value_type,__mul>::Type
  Dot(ArrayMul<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArrayDiv<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT,typename T>
  typename __dual_selector<typename ArrayDiv<EA,EB>::value_type,T,__mul>::Type
  Dot(ArrayDiv<EA,EB,vT,ArrayKernelName::Direct3D> const& A,
      Array<Intrinsic<T>,ArrayKernelName::Direct3D,true> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArrayDiv<EA,EB>::value_type,
                           typename ArraySum<EC,ED>::value_type,__mul>::Type
  Dot(ArrayDiv<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArraySum<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArrayDiv<EA,EB>::value_type,
                           typename ArraySub<EC,ED>::value_type,__mul>::Type
  Dot(ArrayDiv<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArraySub<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArrayDiv<EA,EB>::value_type,
                           typename ArrayMul<EC,ED>::value_type,__mul>::Type
  Dot(ArrayDiv<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArrayMul<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

  template <typename EA,typename EB,typename vT1,
            typename EC,typename ED,typename vT2>
  typename __dual_selector<typename ArrayDiv<EA,EB>::value_type,
                           typename ArrayDiv<EC,ED>::value_type,__mul>::Type
  Dot(ArrayDiv<EA,EB,vT1,ArrayKernelName::Direct3D> const& A,
      ArrayDiv<EC,ED,vT2,ArrayKernelName::Direct3D> const& B) {
    return A[0]*B[0]+A[1]*B[1]+A[2]*B[2];
  }

}

#endif

