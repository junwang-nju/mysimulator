
#ifndef _Parameter_Name_Core_Expanded_CoreLJ612_H_
#define _Parameter_Name_Core_Expanded_CoreLJ612_H_

#include "parameter-name-core-expand-base.h"
#include "parameter-name-corelj612.h"

namespace std {

  enum CoreExpandCoreLJ612ParameterName {
    CoreExpCoreLJ612Radius=CoreLJ612Radius+CoreExpBaseNumberParameter,
    CoreExpCoreLJ612EnergyDepth=
      CoreLJ612EnergyDepth+CoreExpBaseNumberParameter,
    CoreExpCoreLJ612RadiusSQ=CoreLJ612RadiusSQ+CoreExpBaseNumberParameter,
    CoreExpCoreLJ612TwlfEnergyDepth=
      CoreLJ612TwlfEnergyDepth+CoreExpBaseNumberParameter,
    CoreExpCoreLJ612NumberParameter=
      CoreLJ612NumberParameter+CoreExpBaseNumberParameter
  };

  void GenerateParameterCoreExpandCoreLJ612(UniqueParameter* prm) {
    GenerateParameterCoreLJ612(prm+CoreExpBaseNumberParameter);
  }

  void GenerateParameterCoreExpandCoreLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=CoreExpCoreLJ612NumberParameter);
    GenerateParameterCoreExpandCoreLJ612(prm());
  }

}

#endif

