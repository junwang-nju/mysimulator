
#ifndef _Interaction_Func_Implement_LJ1012_Parameter_Build_H_
#define _Interaction_Func_Implement_LJ1012_Parameter_Build_H_

#include "interaction/func/impl/lj1012/parameter/name.h"
#include "unique/64bit/copy.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012(Unique64Bit* prm) {
    copy(prm[LJ1012EqRadiusSq],square(prm[LJ1012EqRadius].value<T>()));
    copy(prm[LJ1012SixtyEqEnergyDepth],prm[LJ1012EqEnergyDepth].value<T>()*60);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>=LJ1012NumberParameters);
    BuildParameterLJ1012<T>(prm.start);
  }

}

#endif

