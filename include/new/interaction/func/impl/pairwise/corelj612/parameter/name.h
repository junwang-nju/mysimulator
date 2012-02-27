
#ifndef _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Name_H_
#define _Interaction_Func_Implement_Pairwise_CoreLJ612_Parameter_Name_H_

#include "interaction/func/impl/pairwise/lj612/parameter/name.h"

namespace mysimulator {

  enum CoreLJ612ParameterName {
    CoreLJ612Radius           =LJ612EqRadius,
    CoreLJ612EnergyDepth      =LJ612EqEnergyDepth,
    CoreLJ612RadiusSQ         =LJ612EqRadiusSQ,
    CoreLJ612TwlfEnergyDepth  =LJ612TwlfEnergyDepth,
    CoreLJ612NumberParameters =LJ612NumberParameters
  };

}

#include "interaction/func/impl/pairwise/corelj612/parameter/build.h"

#endif

