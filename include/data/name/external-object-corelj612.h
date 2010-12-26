
#ifndef _Parameter_External_Object_CoreLJ612_H_
#define _Parameter_External_Object_CoreLJ612_H_

#include "data/name/external-object-base.h"
#include "data/name/corelj612.h"

namespace std {

  enum ExtObjCoreLJ612Parametername {
    ExtObjCoreLJ612Radius=ExtObjectBaseNumberParameter+CoreLJ612Radius,
    ExtObjCoreLJ612EnergyDepth=
        ExtObjectBaseNumberParameter+CoreLJ612EnergyDepth,
    ExtObjCoreLJ612RadiusSQ=ExtObjectBaseNumberParameter+CoreLJ612RadiusSQ,
    ExtObjCoreLJ612TwlfEnergyDepth=
        ExtObjectBaseNumberParameter+CoreLJ612TwlfEnergyDepth,
    ExtObjCoreLJ612NumberParameter
  };

}

#endif
