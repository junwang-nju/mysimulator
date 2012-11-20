
#ifndef _Array_2D_Sum_H_
#define _Array_2D_Sum_H_

#include "array-2d/def.h"
#include "array/interface.h"

namespace mysimulator {

  template <typename T,ArrayKernelName DK,ArrayKernelName LK>
  typename T::value_type Sum(Array2D<T,DK,LK,true> const& A) {
    return Sum(A.Data());
  }

  template <typename T,ArrayKernelName DK>
  T Sum(Array2D<Intrinsic<T>,DK,ArrayKernelName::SSE,true> const& A) {
    return Sum((Array<Array<Intrinsic<T>,ArrayKernelName::SSE>> const&)A);
  }

}

#include "array-2d/expression/sum.h"

namespace mysimulator {

  template <typename EA,typename EB>
  typename Array2DSumBase<EA,EB>::value_type
  Sum(Array2DSum<EA,EB,Array2DExpressionSSEState::NoSSE> const& A) {
    return Sum(A.Data());
  }

  template <typename EA,typename EB>
  typename Array2DSumBase<EA,EB>::value_type
  Sum(Array2DSum<EA,EB,Array2DExpressionSSEState::Mixed> const& A) {
    return Sum(A.first())+Sum(A.second());
  }

  template <typename EA,typename EB>
  typename Array2DSumBase<EA,EB>::value_type
  Sum(Array2DSum<EA,EB,Array2DExpressionSSEState::PureSSE> const& A) {
    typename Array2DSumBase<EA,EB>::value_type  S=0;
    for(unsigned int i=0;i<A.size();++i)  S+=Sum(A[i]);
    return S;
  }

  template <typename E,typename T,Array2DExpressionSSEState ST>
  typename Array2DSumBase<E,Intrinsic<T>>::value_type
  Sum(Array2DSum<E,Intrinsic<T>,ST> const& A) {
    return Sum(A.first())+((T)(A.second()))*A.size();
  }

  template <typename T,typename E,Array2DExpressionSSEState ST>
  typename Array2DSumBase<Intrinsic<T>,E>::value_type
  Sum(Array2DSum<Intrinsic<T>,E,ST> const& A) {
    return ((T)(A.first()))*A.size()+Sum(A.second());
  }

}

#include "array-2d/expression/substract.h"

namespace mysimulator {

  template <typename EA,typename EB>
  typename Array2DSubBase<EA,EB>::value_type
  Sum(Array2DSub<EA,EB,Array2DExpressionSSEState::NoSSE> const& A) {
    return Sum(A.Data());
  }

  template <typename EA,typename EB>
  typename Array2DSubBase<EA,EB>::value_type
  Sum(Array2DSub<EA,EB,Array2DExpressionSSEState::Mixed> const& A) {
    return Sum(A.first())-Sum(A.second());
  }

  template <typename EA,typename EB>
  typename Array2DSubBase<EA,EB>::value_type
  Sum(Array2DSub<EA,EB,Array2DExpressionSSEState::PureSSE> const& A) {
    typename Array2DSubBase<EA,EB>::value_type  S=0;
    for(unsigned int i=0;i<A.size();++i)  S+=Sum(A[i]);
    return S;
  }

  template <typename E,typename T,Array2DExpressionSSEState ST>
  typename Array2DSubBase<E,Intrinsic<T>>::value_type
  Sum(Array2DSub<E,Intrinsic<T>,ST> const& A) {
    return Sum(A.first())-((T)(A.second()))*A.size();
  }

  template <typename T,typename E,Array2DExpressionSSEState ST>
  typename Array2DSubBase<Intrinsic<T>,E>::value_type
  Sum(Array2DSub<Intrinsic<T>,E,ST> const& A) {
    return ((T)(A.first()))*A.size()-Sum(A.second());
  }

}

#include "array-2d/expression/multiple.h"

namespace mysimulator {

  template <typename EA,typename EB>
  typename Array2DMulBase<EA,EB>::value_type
  Sum(Array2DMul<EA,EB,Array2DExpressionSSEState::NoSSE> const& A) {
    return Sum(A.Data());
  }

  template <typename EA,typename EB,Array2DExpressionSSEState ST>
  typename Array2DMulBase<EA,EB>::value_type
  Sum(Array2DMul<EA,EB,ST> const& A) {
    typename Array2DMulBase<EA,EB>::value_type S=0;
    for(unsigned int i=0;i<A.size();++i)  S+=Sum(A[i]);
    return S;
  }

  template <typename E,typename T,Array2DExpressionSSEState ST>
  typename Array2DMulBase<E,Intrinsic<T>>::value_type
  Sum(Array2DMul<E,Intrinsic<T>,ST> const& A) {
    return Sum(A.first())*((T)(A.second()));
  }

  template <typename T,typename E,Array2DExpressionSSEState ST>
  typename Array2DMulBase<Intrinsic<T>,E>::value_type
  Sum(Array2DMul<Intrinsic<T>,E,ST> const& A) {
    return ((T)(A.first()))*Sum(A.second());
  }

}

#include "array-2d/expression/divide.h"

namespace mysimulator {

  template <typename EA,typename EB>
  typename Array2DDivBase<EA,EB>::value_type
  Sum(Array2DDiv<EA,EB,Array2DExpressionSSEState::NoSSE> const& A) {
    return Sum(A.Data());
  }

  template <typename EA,typename EB,Array2DExpressionSSEState ST>
  typename Array2DDivBase<EA,EB>::value_type
  Sum(Array2DDiv<EA,EB,ST> const& A) {
    typename Array2DDivBase<EA,EB>::value_type S=0;
    for(unsigned int i=0;i<A.size();++i)  S+=Sum(A[i]);
    return S;
  }

  template <typename E,typename T,Array2DExpressionSSEState ST>
  typename Array2DDivBase<E,Intrinsic<T>>::value_type
  Sum(Array2DDiv<E,Intrinsic<T>,ST> const& A) {
    return Sum(A.first())/((T)(A.second()));
  }

}

#endif

