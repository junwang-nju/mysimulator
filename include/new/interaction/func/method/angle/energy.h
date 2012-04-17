
#ifndef _Interaction_Func_Method_Angle_Energy_H_
#define _Interaction_Func_Method_Angle_Energy_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, InteractionBuffer<T>& Buf,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    if(Buf.postUpdate) {
      if(IsValid(Buf.inf)) Buf.GetPreFunc(&Buf,Buf.inf.start,Buf.pre.start);
      else {
        Buf.pre[0]=DistanceSQ(Buf.tmvec[0],X[I],X[J],Geo);
        Buf.pre[1]=DistanceSQ(Buf.tmvec[1],X[K],X[J],Geo);
      }
      Buf.pre[2]=dot(Buf.tmvec[0],Buf.tmvec[1]);
      Buf.P2PFunc(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
    }
    T ee;
    efunc(Buf.post.start,P,&ee);
    Energy+=ee;
  }

}

#endif

