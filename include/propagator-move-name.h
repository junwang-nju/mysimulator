
#ifndef _Propagator_Move_Name_H_
#define _Propagator_Move_Name_H_

namespace std {

  enum PropagatorMoveTypeName {
    UnknownMoveType=0,
    ConstantE_VelocityVerlet,
    Berendsen_VelocityVerlet,
    Langevin_VelocityVerlet
  };

}

#endif

