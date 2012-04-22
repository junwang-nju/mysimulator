
#ifndef _Interaction_Func_Method_Angle_Energy_H_
#define _Interaction_Func_Method_Angle_Energy_H_

#include "interaction/buffer/interface.h"
#include "distance/calc.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GT,typename T>
  void EMethodAngle(
      const Array1D<Array1D<T> >& X,const Array1D<unsigned int>& ID,
      const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,const GT& Geo,
      T& Energy,
      void (*efunc)(const Array1D<T>&,const Array1D<Unique64Bit>&,T*)) {
    if(Buf.postUpdate) {
      if(Buf.inf.IsValid())   Buf.GetPreFunc();
      else {
        unsigned int I=ID[0],J=ID[1],K=ID[2];
        Buf.pre[AngleEdgeASQ]=
          DistanceSQ(Buf.tmvec[AngleBondVecIJ],X[I],X[J],Geo,Buf.dim);
        Buf.pre[AngleEdgeBSQ]=
          DistanceSQ(Buf.tmvec[AngleBondVecKJ],X[K],X[J],Geo,Buf.dim);
      }
      Buf.pre[AngleDotAB]=
        Dot(Buf.tmvec[AngleBondVecIJ],Buf.tmvec[AngleBondVecKJ],Buf.dim);
      Buf.Pre2PostFunc(P);
    }
    T ee;
    efunc(Buf.post,P,&ee);
    Energy+=ee;
  }

}

#endif

