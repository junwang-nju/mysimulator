
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Build_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "unique/64bit/copy.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterDistCoulomb(Unique64Bit* prm) {
    copy(prm[dCoulombStrength],prm[dCoulombChargeA].value<T>()*
                               prm[dCoulombChargeB].value<T>()*
                               prm[dCoulombDielectricFac].value<T>());
    copy(prm[dCoulombDualStrength],2*prm[dCoulombStrength].value<T>());
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterDistCoulomb(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=DistCoulombNumberParameters);
    BuildParameterDistCoulomb<T>(prm.start);
  }

}

#endif

