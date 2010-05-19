
#ifndef _Propagator_Operate_H_
#define _Propagator_Operate_H_

#include "propagator-move-name.h"
#include "propagator-conste-vverlet.h"
#include "propagator-berendsen-vverlet.h"
#include "propagator-langevin-vverlet.h"

namespace std {

  template <typename DistEvalMethod, typename GeomType>
  void Set(Propagator<DistEvalMethod,GeomType>& P, const unsigned int MType) {
    assert(IsAvailable(P));
    *(P.MoveMode)=MType;
    if(MType==ConstantE_VelocityVerlet) SetAsEV(P);
    else if(MType==Berendsen_VelocityVerlet)  SetAsBV(P);
    else if(MType==Langevin_VelocityVerlet) SetAsLV(P);
    else myError("Not implemented Move Type");
  }

}

#endif

