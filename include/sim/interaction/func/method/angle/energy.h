
#ifndef _Interaction_Func_Method_Angle_Energy_H_
#define _Interaction_Func_Method_Angle_Energy_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EMethodAngle(
      T** const X,const unsigned int* id,const Unique64Bit* P,
      const GeomType& Geo,T& Energy,InteractionBuffer<T>& Buf,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    if(Buf.postUpdate) {
      if(Buf.inf!=NULL)   Buf.GetPreFunc();
      else {
        unsigned int I=id[0],J=id[1],K=id[2];
        Buf.pre[AngleEdgeASQ]
          =DistanceSQ(Buf.tmvec[AngleBondVecIJ],X[I],X[J],Geo,Buf.dim);
        Buf.pre[AngleEdgeBSQ]
          =DistanceSQ(Buf.tmvec[AngleBondVecKJ],X[K],X[J],Geo,Buf.dim);
      }
      Buf.pre[AngleDotAB]
        =Dot(Buf.tmvec[AngleBondVecIJ],Buf.tmvec[AngleBondVecKJ],Buf.dim);
      Buf.Pre2PostFunc(P);
    }
    T ee;
    efunc(Buf.post,P,&ee);
    Energy+=ee;
  }

}

#endif

