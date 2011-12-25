
#ifndef _Interaction_Func_Implement_DistCoulomb_Diff_H_
#define _Interaction_Func_Implement_DistCoulomb_Diff_H_

#include "interaction/func/impl/dist-coulomb/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void DiffDistCoulomb(const T& dsq, const Unique64Bit* P, T& diff) {
    T ivd2=1./dsq;
    diff=-P[dCoulombDualStrength].value<T>()*ivd2*ivd2;
  }

}

#endif

