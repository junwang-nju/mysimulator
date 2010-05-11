
#ifndef _Parameter_Name_LJ1012_H_
#define _Parameter_Name_LJ1012_H_

namespace std {

  enum LJ1012ParameterName {
    LJ1012EqRadius=0,
    LJ1012EqEnergyDepth,
    LJ1012EqRadiusSQ,
    LJ1012SixtyEqEnergyDepth,
    LJ1012NumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void GenerateParameterLJ1012(UniqueParameter* prm) {
    prm[LJ1012EqRadiusSQ]=prm[LJ1012EqRadius].d*prm[LJ1012EqRadius].d;
    prm[LJ1012SixtyEqEnergyDepth]=prm[LJ1012EqEnergyDepth].d*60;
  }

  void GenerateParameterLJ1012(Vector<UniqueParameter>& prm) {
    assert(prm.size>=LJ1012NumberParameter);
    GenerateParameterLJ1012(prm());
  }

}

#endif

