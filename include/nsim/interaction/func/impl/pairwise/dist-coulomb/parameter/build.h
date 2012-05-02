
#ifndef _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Build_H_
#define _Interaction_Func_Implement_Pairwise_DistCoulomb_Parameter_Build_H_

#include "interaction/func/impl/pairwise/dist-coulomb/parameter/name.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterDistCoulomb(Array1D<Unique64Bit>& prm) {
    Value<T>(prm[DistCoulombStrength])=
      Value<T>(prm[DistCoulombChargeA])*Value<T>(prm[DistCoulombChargeB])*
      Value<T>(prm[DistCoulombDielectricFac]);
    Value<T>(prm[DistCoulombDualStrength])=
      2*Value<T>(prm[DistCoulombStrength]);
  }

}

#endif

