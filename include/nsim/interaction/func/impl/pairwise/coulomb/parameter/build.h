
#ifndef _Interaction_Func_Implement_Pairwise_Coulomb_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_Coulomb_Parameter_Build_H_

#include "interaction/func/impl/pairwise/coulomb/parameter/name.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCoulomb(Array1D<Unique64Bit>& prm) {
    Value<T>(prm[CoulombStrength])=
      Value<T>(prm[CoulombChargeA])*Value<T>(prm[CoulombChargeB])*
      Value<T>(prm[CoulombDielectric]);
  }

}

#endif

