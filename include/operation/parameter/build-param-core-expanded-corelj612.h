
#ifndef _Build_Parameter_Core_Expanded_CoreLJ612_H_
#define _Build_Parameter_Core_Expanded_CoreLJ612_H_

#include "data/name/core-expanded-corelj612.h"
#include "operation/parameter/build-param-corelj612.h"

namespace std {

  template <typename T>
  void BuildParameterCoreExpandedCoreLJ612(UniqueParameter* prm) {
    BuildParameterCoreLJ612<T>(prm+CoreExpandedBaseNumberParameter);
  }

  template <typename T>
  void BuildParameterCoreExpandedCoreLJ612(Vector<UniqueParameter>& prm) {
    assert(prm.size>=CoreExpandedCoreLJ612NumberParameter);
    BuildParameterCoreExpandedCoreLJ612<T>(prm.data);
  }

}

#endif
