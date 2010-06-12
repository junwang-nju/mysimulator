
#ifndef _Parameter_Name_Wall_CoreLJ612_H_
#define _Parameter_Name_Wall_CoreLJ612_H_

#include "parameter-name-wall-base.h"
#include "parameter-name-corelj612.h"

namespace std {

  enum WallCoreLJ612ParameterName {
    WallCoreLJ612Radius=CoreLJ612Radius+WallBaseNumberParameter,
    WallCoreLJ612EnergyDepth=CoreLJ612EnergyDepth+WallBaseNumberParameter,
    WallCoreLJ612RadiusSQ=CoreLJ612RadiusSQ+WallBaseNumberParameter,
    WallCoreLJ612TwlfEnergyDepth=
      CoreLJ612TwlfEnergyDepth+WallBaseNumberParameter,
    WallCoreLJ612ParameterNumber,
    WallCoreLJ612ParameterEnd,
  };

}

#endif
