
#ifndef _System_Interaction_Parameter_Pairwise_LJ1012_Allocate_H_
#define _System_Interaction_Parameter_Pairwise_LJ1012_Allocate_H_

#include "system/interaction/parameter/pairwise/lj1012/name.h"
#include "array/interface.h"

namespace mysimulator {

  void _allocate_param_pair_lj1012(Array<Double>& _FParam,Array<Int>&) {
    _FParam.allocate(PairLJ1012ParameterName::NumberParameter);
  }

}

#endif

