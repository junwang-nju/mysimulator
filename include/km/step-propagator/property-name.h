
#ifndef _Step_Propagator_Property_Name_H_
#define _Step_Propagator_Property_Name_H_

namespace mysimulator {

  enum MassPropertyName {
    UniqueMass=0,
    ArrayMass,
    UnknownMassProperty
  };

  enum FrictionPropertyName {
    UniqueFriction=0,
    ArrayFriction,
    UnknownFrictionProperty
  };

}

#endif

