
#ifndef _Array_Operation_Sum_H_
#define _Array_Operation_Sum_H_

#include "array/def.h"

namespace mysimulator {

  template <typename T>
  typename T::value_type Sum(Array<T,ArrayKernelName::Simple,true> const& A) {
    typename T::value_type S=0;
    for(unsigned int i=0;i<A.size();++i)  S+=Sum(A[i]);
    return S;
  }

}

#include "array/kernel/simple.h"

namespace mysimulator {

  template <typename T>
  T Sum(Array<Intrinsic<T>,ArrayKernelName::Simple,true> const& A) {
    return __sum_simple(A);
  }

}

#include "array/kernel/direct-3d.h"

namespace mysimulator {

  template <typename T>
  T Sum(Array<Intrinsic<T>,ArrayKernelName::Direct3D> const& A) {
    return __sum_direct3d(A);
  }

}

#include "array/kernel/sse.h"

namespace mysimulator {

  template <typename T>
  T Sum(Array<Intrinsic<T>,ArrayKernelName::SSE> const& A) {
    return __sum_simple(A);
  }

  double Sum(Array<Double,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }
  float Sum(Array<Float,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }
  int Sum(Array<Int,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }
  long Sum(Array<Long,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

}

#include "array/expression/sum.h"

namespace mysimulator {

  template <typename EA,typename EB,typename vT,ArrayKernelName KN>
  vT Sum(ArraySum<EA,EB,vT,KN> const& A) {
    return __sum_simple(A);
    //return Sum(A.first())+Sum(A.second()); // not safe for size reason
  }

  template <typename E,typename T,typename vT,ArrayKernelName KN>
  vT Sum(ArraySum<E,Intrinsic<T>,vT,KN> const& A) {
    return Sum(A.first())+((T)(A.second()))*A.size();
  }

  template <typename T,typename E,typename vT,ArrayKernelName KN>
  vT Sum(ArraySum<Intrinsic<T>,E,vT,KN> const& A) {
    return ((T)(A.first()))*A.size()+Sum(A.second());
  }

  template <typename EA,typename EB,typename vT>
  vT Sum(ArraySum<EA,EB,vT,ArrayKernelName::Direct3D> const& A) {
    return __sum_direct3d(A);
  }

  template <typename EA,typename EB,typename vT>
  vT Sum(ArraySum<EA,EB,vT,ArrayKernelName::SSE> const& A) {
    return __sum_simple(A);
  }

  template <typename EA,typename EB>
  double Sum(ArraySum<EA,EB,double,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  float Sum(ArraySum<EA,EB,float,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  int Sum(ArraySum<EA,EB,int,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  long Sum(ArraySum<EA,EB,long,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

}

#include "array/expression/substract.h"

namespace mysimulator {

  template <typename EA,typename EB,typename vT,ArrayKernelName KN>
  vT Sum(ArraySub<EA,EB,vT,KN> const& A) {
    return __sum_simple(A);
    //return Sum(A.first())-Sum(A.second()); // not safe for size reason
  }

  template <typename E,typename T,typename vT,ArrayKernelName KN>
  vT Sum(ArraySub<E,Intrinsic<T>,vT,KN> const& A) {
    return Sum(A.first())-((T)(A.second()))*A.size();
  }

  template <typename T,typename E,typename vT,ArrayKernelName KN>
  vT Sum(ArraySub<Intrinsic<T>,E,vT,KN> const& A) {
    return ((T)(A.first()))*A.size()-Sum(A.second());
  }

  template <typename EA,typename EB,typename vT>
  vT Sum(ArraySub<EA,EB,vT,ArrayKernelName::Direct3D> const& A) {
    return __sum_direct3d(A);
  }

  template <typename EA,typename EB,typename vT>
  vT Sum(ArraySub<EA,EB,vT,ArrayKernelName::SSE> const& A) {
    return __sum_simple(A);
  }

  template <typename EA,typename EB>
  double Sum(ArraySub<EA,EB,double,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  float Sum(ArraySub<EA,EB,float,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  int Sum(ArraySub<EA,EB,int,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  long Sum(ArraySub<EA,EB,long,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

}

#include "array/expression/multiple.h"

namespace mysimulator {

  template <typename EA,typename EB,typename vT,ArrayKernelName KN>
  vT Sum(ArrayMul<EA,EB,vT,KN> const& A) {
    return __sum_simple(A);
  }

  template <typename E,typename T,typename vT,ArrayKernelName KN>
  vT Sum(ArrayMul<E,Intrinsic<T>,vT,KN> const& A) {
    return Sum(A.first())*((T)(A.second()));
  }

  template <typename T,typename E,typename vT,ArrayKernelName KN>
  vT Sum(ArrayMul<Intrinsic<T>,E,vT,KN> const& A) {
    return ((T)(A.first()))*Sum(A.second());
  }

  template <typename EA,typename EB,typename vT>
  vT Sum(ArrayMul<EA,EB,vT,ArrayKernelName::Direct3D> const& A) {
    return __sum_direct3d(A);
  }

  template <typename EA,typename EB,typename vT>
  vT Sum(ArrayMul<EA,EB,vT,ArrayKernelName::SSE> const& A) {
    return __sum_simple(A);
  }

  template <typename EA,typename EB>
  double Sum(ArrayMul<EA,EB,double,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  float Sum(ArrayMul<EA,EB,float,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  int Sum(ArrayMul<EA,EB,int,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  long Sum(ArrayMul<EA,EB,long,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

}

#include "array/expression/divide.h"

namespace mysimulator {

  template <typename EA,typename EB,typename vT,ArrayKernelName KN>
  vT Sum(ArrayDiv<EA,EB,vT,KN> const& A) {
    return __sum_simple(A);
  }

  template <typename E,typename T,typename vT,ArrayKernelName KN>
  vT Sum(ArrayDiv<E,Intrinsic<T>,vT,KN> const& A) {
    return Sum(A.first())/((T)(A.second()));
  }

  template <typename EA,typename EB,typename vT>
  vT Sum(ArrayDiv<EA,EB,vT,ArrayKernelName::Direct3D> const& A) {
    return __sum_direct3d(A);
  }

  template <typename EA,typename EB,typename vT>
  vT Sum(ArrayDiv<EA,EB,vT,ArrayKernelName::SSE> const& A) {
    return __sum_simple(A);
  }

  template <typename EA,typename EB>
  double Sum(ArrayDiv<EA,EB,double,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  float Sum(ArrayDiv<EA,EB,float,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  int Sum(ArrayDiv<EA,EB,int,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

  template <typename EA,typename EB>
  long Sum(ArrayDiv<EA,EB,long,ArrayKernelName::SSE> const& A) {
    return __sum_sse(A);
  }

}

#endif

