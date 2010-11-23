
#ifndef _Build_Parameter_Core_Expanded_LJ612_H_
#define _Build_Parameter_Core_Expanded_LJ612_H_

#include "data/name/parameter-core-expanded-lj612.h"
#include "operation/parameter/build-param-lj612.h"

namespace std {

  template <typename T>
  void BuildParameterCoreExpandedLJ612(UniqueParameter* prm) {
    BuildParameterLJ612<T>(prm+CoreExpandedBaseNumberParameter);
  }

  template <typename T>
  void BuildParameterCoreExpandedLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=CoreExpandedLJ612NumberParameter);
    BuildParameterCoreExpandedLJ612<T>(prm.data);
  }
}

#endif
