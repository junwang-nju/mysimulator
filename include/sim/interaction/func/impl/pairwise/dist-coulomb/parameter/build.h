
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Build_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterDistCoulomb(Unique64Bit* prm) {
    prm[DistCoulombStrength].value<T>()=
      prm[DistCoulombChargeA].value<T>()*prm[DistCoulombChargeB].value<T>()*
      prm[DistCoulombDielectricFac].value<T>();
    prm[DistCoulombDualStrength].value<T>()=
      2*prm[DistCoulombStrength].value<T>();
  }

}

#endif

