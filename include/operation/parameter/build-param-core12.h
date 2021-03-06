
#ifndef _Build_Parameter_Core12_H_
#define _Build_Parameter_Core12_H_

#include "data/name/core12.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void BuildParameterCore12(UniqueParameter* prm) {
    copy(prm[Core12TwlfEqStrength],12*prm[Core12EqStrength].value<T>());
  }

}

#include "data/basic/vector.h"

namespace std {

  template <typename T>
  void BuildParameterCore12(Vector<UniqueParameter>& prm) {
    assert(prm.size>=Core12NumberParameter);
    BuildParameterCore12<T>(prm.data);
  }

}

#endif

