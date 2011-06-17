
#ifndef _Functional_LJ612_Parameter_Build_H_
#define _Functional_LJ612_Parameter_Build_H_

#include "functional/lj612/parameter/name.h"
#include "unique-parameter/64bit/copy.h"
#include "intrinsic-type/square.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612(UniqueParameter64Bit* prm) {
    copy(prm[LJ612EqRadiusSq],square(prm[LJ612EqRadius].value<T>()));
    copy(prm[LJ612TwlfEnergyDepth],12*prm[LJ612EqEnergyDepth].value<T>());
  }

}

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterLJ612(Vector<UniqueParameter64Bit>& prm) {
    assert(prm.size>=LJ612NumberParameter);
    BuildParameterLJ612<T>(prm.pdata);
  }

}

#endif

