
#ifndef _Functional_LJ1012_Parameter_Build_H_
#define _Functional_LJ1012_Parameter_Build_H_

#include "functional/lj1012/parameter/name.h"
#include "unique-parameter/64bit/copy.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012(UniqueParameter64Bit* prm) {
    copy(prm[LJ1012EqRadiusSq],square(prm[LJ1012EqRadius].value<T>()));
    copy(prm[LJ1012SixtyEqEnergyDepth],prm[LJ1012EqEnergyDepth].value<T>()*60);
  }

}

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ1012(Vector<UniqueParameter64Bit>& prm) {
    assert(prm.size>=LJ1012NumberParameter);
    BuildParameterLJ1012<T>(prm.pdata);
  }

}

#endif

