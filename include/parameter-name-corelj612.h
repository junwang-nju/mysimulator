
#ifndef _Parameter_Name_CoreLJ612_H_
#define _Parameter_Name_CoreLJ612_H_

#include "parameter-name-lj612.h"

namespace std {

  enum CoreLJ612ParameterName {
    CoreLJ612Radius=LJ612EqRadius,
    CoreLJ612EnergyDepth=LJ612EqEnergyDepth,
    CoreLJ612RadiusSQ=LJ612EqRadiusSQ,
    CoreLJ612TwlfEnergyDepth=LJ612TwlfEqEnergyDepth,
    CoreLJ612NumberParameter=LJ612NumberParameter
  };

  void GenerateParameterCoreLJ612(UniqueParameter* prm) {
    GenerateParameterLJ612(prm);
  }

  void GenerateParameterCoreLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=CoreLJ612NumberParameter);
    GenerateParameterCoreLJ612(prm());
  }

}

#endif

