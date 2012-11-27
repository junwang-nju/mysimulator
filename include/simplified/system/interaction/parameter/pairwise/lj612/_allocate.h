
#ifndef _System_Interaction_Parameter_Pairwise_LJ612_Allocate_H_
#define _System_Interaction_Parameter_Pairwise_LJ612_Allocate_H_

#include "system/interaction/parameter/pairwise/lj612/name.h"
#include "array/interface.h"

namespace mysimulator {

  void _allocate_pair_lj612(Array<Double>& _FParam,Array<Int>&) {
    _FParam.allocate(PairLJ612ParameterName::NumberParameter);
  }

}

#endif

