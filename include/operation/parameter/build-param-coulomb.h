
#ifndef _Build_Parameter_Coulomb_H_
#define _Build_Parameter_Coulomb_H_

#include "data/basic/unique-parameter.h"
#include "data/name/parameter-coulomb.h"

namespace std {

  template <typename T>
  void BuildParameterCoulomb(UniqueParameter* prm) {}

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterCoulomb(Vector<UniqueParameter>& prm) {
    assert(prm.size>=CoulombNumberParameter);
    BuildParameterCoulomb<T>(prm.data);
  }

}

#endif

