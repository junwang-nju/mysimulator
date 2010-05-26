
#ifndef _Parameter_Name_LJ612_H_
#define _Parameter_Name_LJ612_H_

namespace std {

  enum LJ612ParameterName {
    LJ612EqRadius=0,
    LJ612EqEnergyDepth,
    LJ612EqRadiusSQ,
    LJ612TwlfEqEnergyDepth,
    LJ612NumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void GenerateParameterLJ612(UniqueParameter* prm) {
    prm[LJ612EqRadiusSQ]=prm[LJ612EqRadius].d*prm[LJ612EqRadius].d;
    prm[LJ612TwlfEqEnergyDepth]=prm[LJ612EqEnergyDepth].d*12.;
  }

  void GenerateParameterLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ612NumberParameter);
    GenerateParameterLJ612(prm());
  }

}

#endif

