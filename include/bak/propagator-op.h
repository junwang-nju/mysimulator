
#ifndef _Propagator_Operation_H_
#define _Propagator_Operation_H_

#include "propagator-move-name.h"
#include "propagator-conste-vverlet.h"
#include "propagator-berendsen-vverlet.h"
#include "propagator-langevin-vverlet.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void SetUp(Propagator<DistEvalMethod,GeomType>& P,
             const unsigned int MoveType) {
    P.MoveMode=MoveType;
    if(MoveType==ConstE_VelocityVerlet)         SetAsEV(P);
    else if(MoveType==Berendsen_VelocityVerlet) SetAsBV(P);
    else if(MoveType==Langevin_VelocityVerlet)  SetAsLV(P);
    else myError("Not Implemented Move Type");
  }

}

#endif
