
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Parameter_Build_H_

#include "unique/64bit/copy.h"
#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoulomb(Unique64Bit* prm) {
    copy(prm[CoulombStrength],prm[CoulombChargeA].value<T>()*
                              prm[CoulombChargeB].value<T>()*
                              prm[CoulombDielectric].value<T>());
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoulomb(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=CoulombNumberParameters);
    BuildParameterCoulomb<T>(prm.start);
  }

}

#endif

