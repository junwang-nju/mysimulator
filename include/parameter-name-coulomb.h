
#ifndef _Parameter_Name_Coulomb_H_
#define _Parameter_Name_Coulomb_H_

namespace std {

  enum CoulombParameterName {
    CoulombStrength=0,
    CoulombNumberParameter
  };

}

#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void GenerateParameterCoulomb(UniqueParameter* prm) {}

  void GenerateParameterCoulomb(Vector<UniqueParameter>& prm) {
    assert(prm.size>=CoulombNumberParameter);
    GenerateParameterCoulomb(prm());
  }

}

#endif

