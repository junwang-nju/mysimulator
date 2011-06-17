
#ifndef _Functional_Core12_Parameter_Build_H_
#define _Functional_Core12_Parameter_Build_H_

#include "unique-parameter/64bit/copy.h"
#include "functional/core12/parameter/name.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCore12(UniqueParameter64Bit* prm) {
    copy(prm[Core12TwlfEqStrength],12*prm[Core12EqStrength].value<T>());
  }

}

#include "vector/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterCore12(Vector<UniqueParameter64Bit>& prm) {
    assert(prm.size>=Core12NumberParameter);
    BuildParameterCore12<T>(prm.pdata);
  }

}

#endif

