
#ifndef _Parameter_Core_Expanded_CoreLJ612_H_
#define _Parameter_Core_Expanded_CoreLJ612_H_

#include "data/name/core-expanded-base.h"
#include "data/name/corelj612.h"

namespace std {

  enum CoreExpandedCoreLJ612ParameterName {
    CoreExpandedCoreLJ612Radius=CoreLJ612Radius+CoreExpandedBaseNumberParameter,
    CoreExpandedCoreLJ612EnergyDepth=
        CoreLJ612EnergyDepth+CoreExpandedBaseNumberParameter,
    CoreExpandedCoreLJ612RadiusSQ=
        CoreLJ612RadiusSQ+CoreExpandedBaseNumberParameter,
    CoreExpandedCoreLJ612TwlfEnergyDepth=
        CoreLJ612TwlfEnergyDepth+CoreExpandedBaseNumberParameter,
    CoreExpandedCoreLJ612NumberParameter=
        CoreLJ612NumberParameter+CoreExpandedBaseNumberParameter
  };

}

#endif
