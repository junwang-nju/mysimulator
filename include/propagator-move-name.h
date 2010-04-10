
#ifndef _Propagator_Move_Name_H_
#define _Propagator_Move_Name_H_

namespace std {

  enum PropagatorMoveNameType {
    UnknownMoveType=0,
    ConstE_VelocityVerlet,
    Berendsen_VelocityVerlet,
    Langevin_VelocityVerlet
  };

}

#endif

