
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Build_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "unique/64bit/copy.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterDistCoulomb(Unique64Bit* prm) {
    copy(prm[DistCoulombStrength],prm[DistCoulombChargeA].value<T>()*
                               prm[DistCoulombChargeB].value<T>()*
                               prm[iDistCoulombDielectricFac].value<T>());
    copy(prm[DistCoulombDualStrength],2*prm[DistCoulombStrength].value<T>());
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

