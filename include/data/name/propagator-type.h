
#ifndef _Parameter_Propagator_Type_H_
#define _Parameter_Propagator_Type_H_

namespace std {

  enum PropagatorTypeName {
    UnknownPropagatorType=0,
    ConstantE_VelocityVerlet,
    Berendsen_VelocityVerlet,
    Langevin_VelocityVerlet
  };

}

#endif

