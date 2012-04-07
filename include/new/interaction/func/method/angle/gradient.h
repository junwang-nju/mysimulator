
#ifndef _Interaction_Func_Method_Angle_Gradient_H_
#define _Interaction_Func_Method_Angle_Gradient_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "array/1d/content/scale.h"
#include "interaction/func/impl/common/parameter/name.h"
#include "interaction/func/impl/angle/common/buffer/name.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void GFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad,
      void (*ufunc)(const T*,const Unique64Bit*,T*),
      void (*dfunc)(const T*,const Unique64Bit*,T*)) {
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    Array1D<T>* tmvec=
      reinterpret_cast<Array1D<T>*>(P[InteractionArrayBuffer].ptr[0]);
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    if(P[InteractionBufferFlag].u[0]==0) {
      T dsq[3];
      dsq[0]=DistanceSQ(tmvec[0],X[I],X[J],Geo);
      dsq[1]=DistanceSQ(tmvec[1],X[K],X[J],Geo);
      dsq[2]=dot(tmvec[0],tmvec[1]);
      ufunc(dsq,P,buffer);
    }
    copy(tmvec[2],tmvec[1]);
    scale(tmvec[2],buffer[AngleIvRabSin]);
    shift(tmvec[2],-buffer[AngleIvRaSQCtg],tmvec[0]);
    copy(tmvec[3],tmvec[0]);
    scale(tmvec[3],buffer[AngleIvRabSin]);
    shift(tmvec[3],-buffer[AngleIvRbSQCtg],tmvec[1]);

    T ef;
    dfunc(buffer,P,&ef);
    shift(Grad[I],+ef,tmvec[2]);
    shift(Grad[J],-ef,tmvec[2]);
    shift(Grad[K],+ef,tmvec[3]);
    shift(Grad[J],-ef,tmvec[3]);
  }

}

#endif

