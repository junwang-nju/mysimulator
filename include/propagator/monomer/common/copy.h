
#ifndef _Propagator_Monomer_Common_Copy_H_
#define _Propagator_Monomer_Common_Copy_H_

#include "propagator/monomer/common/interface.h"

namespace mysimulator {

  template <typename T>
  void copy(MonomerPropagatorCommon<T>& P,const MonomerPropagatorCommon<T>& cP){
    assert(IsValid(P)&&IsValid(cP));
    assert(P.MonomerKind==cP.MonomerKind);
    copy(P.XVector,cP.XVector);
    copy(P.VVector,cP.VVector);
    copy(P.GVector,cP.GVector);
    copy(P.MskVector,cP.MskVector);
    copy(P.Mass,cP.Mass);
    copy(P.ivMass,cP.ivMass);
  }

}

#endif

