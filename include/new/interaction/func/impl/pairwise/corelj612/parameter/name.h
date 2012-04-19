
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Name_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"

namespace mysimulator {

  enum CoreLJ612ParameterName {
    CoreLJ612Radius           = LJ612EqRadius,
    CoreLJ612EnergyDepth      = LJ612EqEnergyDepth,
    CoreLJ612FactorA          = LJ612FactorA,
    CoreLJ612FactorB          = LJ612FactorB,
    CoreLJ612DiffFactorA      = LJ612DiffFactorA,
    CoreLJ612DiffFactorB      = LJ612DiffFactorB,
    CoreLJ612RadiusSQ         = LJ612NumberParameters,
    CoreLJ612NumberParameters
  };

}

#include "interaction/func/impl/pairwise/corelj612/parameter/build.h"

#endif

