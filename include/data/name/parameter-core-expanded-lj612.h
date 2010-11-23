
#ifndef _Parameter_Core_Expanded_LJ612_H_
#define _Parameter_Core_Expanded_LJ612_H_

#include "data/name/parameter-core-expanded-base.h"
#include "data/name/parameter-lj612.h"

namespace std {

  enum CoreExpandedLJ612ParameterName {
    CoreExpandedLJ612EqRadius=LJ612EqRadius+CoreExpandedBaseNumberParameter,
    CoreExpandedLJ612EqEnergyDepth=
        LJ612EqEnergyDepth+CoreExpandedBaseNumberParameter,
    CoreExpandedLJ612EqRadiusSQ=LJ612EqRadiusSQ+CoreExpandedBaseNumberParameter,
    CoreExpandedLJ612TwlfEqEnergyDepth=
        LJ612TwlfEqEnergyDepth+CoreExpandedBaseNumberParameter,
    CoreExpandedLJ612NumberParameter=
        LJ612NumberParameter+CoreExpandedBaseNumberParameter
  };

}

#endif
