
#ifndef _System_Interaction_Parameter_Pairwise_CoreLJ612_Build_H_
#define _System_Interaction_Parameter_Pairwise_CoreLJ612_Build_H_

#include "system/interaction/parameter/pairwise/corelj612/name.h"
#include "system/interaction/parameter/pairwise/lj612/_build.h"
#include "basic/util/square.h"

namespace mysimulator {

  void _build_pair_corelj612(Array<Double>& _FParam,Array<Int>& _IParam,
                             Array<InteractionParameter>& _PParam) {
    _build_pair_lj612(_FParam,_IParam,_PParam);
    _FParam[PairCoreLJ612ParameterName::EqRadiusSQ]=
      __square(_FParam[PairCoreLJ612ParameterName::EqRadius]);
  }

}

#endif

