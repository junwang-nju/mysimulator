
#ifndef _Interaction_Func_Mehtod_Angle_Both_H_
#define _Interaction_Func_Mehtod_Angle_Both_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "array/1d/content/scale.h"
#include "interaction/func/impl/common/parameter/name.h"
#include "interaction/func/impl/angle/common/buffer/name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void BFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* Grad,
      void (*ufunc)(const T*,const Unique64Bit*,T*),
      void (*bfunc)(const T*,const Unique64Bit*,T*,T*)) {
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    Array1D<T>* tmvec=
      reinterpret_cast<Array1D<T>*>(P[InteractionArrayBuffer].ptr[0]);
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    T dsq[3];
    if(P[InteractionBufferFlag].u[0]==0) {
      dsq[0]=DistanceSQ(tmvec[0],X[I],X[J],Geo);
      dsq[1]=DistanceSQ(tmvec[1],X[K],X[J],Geo);
      dsq[2]=DistanceSQ(tmvec[2],X[K],X[I],Geo);
      ufunc(dsq,P,buffer);
    }
    copy(tmvec[2],tmvec[1]);
    scale(tmvec[2],buffer[AngleIvRabSin]);
    shift(tmvec[2],-buffer[AngleIvRaSQCtg],tmvec[0]);
    copy(tmvec[3],tmvec[0]);
    scale(tmvec[3],buffer[AngleIvRabSin]);
    shift(tmvec[3],-buffer[AngleIvRbSQCtg],tmvec[1]);

    T ee,ef;
    bfunc(buffer,P,&ee,&ef);
    Energy+=ee;
    shift(Grad[I],+ef,tmvec[2]);
    shift(Grad[J],-ef,tmvec[2]);
    shift(Grad[K],+ef,tmvec[3]);
    shift(Grad[J],-ef,tmvec[3]);
  }

}

#endif

