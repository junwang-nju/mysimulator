
#ifndef _Parameter_Name_Core_Expanded_LJ612_H_
#define _Parameter_Name_Core_Expanded_LJ612_H_

#include "parameter-name-core-expand-base.h"
#include "parameter-name-lj612.h"

namespace std {

  enum CoreExpandLJ612ParameterName {
    CoreExpLJ612EqRadius=LJ612EqRadius+CoreExpBaseNumberParameter,
    CoreExpLJ612EqEnergyDepth=LJ612EqEnergyDepth+CoreExpBaseNumberParameter,
    CoreExpLJ612EqRadiusSQ=LJ612EqRadiusSQ+CoreExpBaseNumberParameter,
    CoreExpLJ612TwlfEqEnergyDepth=
      LJ612TwlfEqEnergyDepth+CoreExpBaseNumberParameter,
    CoreExpLJ612NumberParameter=LJ612NumberParameter+CoreExpBaseNumberParameter
  };

  void GenerateParameterCoreExpandLJ612(UniqueParameter* prm) {
    GenerateParameterLJ612(prm+CoreExpBaseNumberParameter);
  }

  void GenerateParameterCoreExpandLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=CoreExpLJ612NumberParameter);
    GenerateParameterCoreExpandLJ612(prm());
  }

}

#endif
