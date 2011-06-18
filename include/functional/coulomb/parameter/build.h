
#ifndef _Functional_Coulomb_Parameter_Build_H_
#define _Functional_Coulomb_Parameter_Build_H_

#include "functional/coulomb/parameter/name.h"
#include "unique-parameter/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoulomb(UniqueParameter64Bit* prm) {}

}

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoulomb(Vector<UniqueParameter64Bit>& prm) {
    assert(prm.size>=CoulombNumberParameter);
    BuildParameterCoulomb<T>(prm.pdata);
  }

}

#endif

