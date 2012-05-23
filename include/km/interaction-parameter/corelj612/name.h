
#ifndef _Interaction_Parameter_CoreLJ612_Name_H_
#define _Interaction_Parameter_CoreLJ612_Name_H_

#include "interaction-parameter/lj612/name.h"

namespace mysimulator {

  enum CoreLJ612ParameterName {
    CoreLJ612Radius           = LJ612EqRadius,
    CoreLJ612EnergyDepth      = LJ612EqEnergyDepth,
    CoreLJ612FactorA          = LJ612FactorA,
    CoreLJ612FactorB          = LJ612FactorB,
    CoreLJ612DiffFactorA      = LJ612DiffFactorA,
    CoreLJ612DiffFactorB      = LJ612DiffFactorB,
    CoreLJ612RadiusSQ         = LJ612NumberParameter,
    CoreLJ612NumberParameter
  };

}

#endif

