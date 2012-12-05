
#ifndef _System_Interaction_Parameter_Pairwise_LJ612_Build_H_
#define _System_Interaction_Parameter_Pairwise_LJ612_Build_H_

#include "system/interaction/parameter/pairwise/lj612/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _build_pair_lj612(
      Array<Double>& _FParam,Array<Int>&,Array<InteractionParameter>&) {
    assert((bool)_FParam);
    assert(_FParam.size() >= PairLJ612ParameterName::NumberParameter);
    double tmd=_FParam[PairLJ612ParameterName::EqRadius];
    tmd*=tmd;
    double tmd1=tmd*tmd*tmd;
    tmd=tmd1*_FParam[PairLJ612ParameterName::EqEnergyDepth];
    double A=tmd*tmd1;
    double B=tmd+tmd;
    _FParam[PairLJ612ParameterName::FactorA]  = A;
    _FParam[PairLJ612ParameterName::FactorB]  = B;
    _FParam[PairLJ612ParameterName::DFactorA] = 12*A;
    _FParam[PairLJ612ParameterName::DFactorB] = 6*B;
  }

}

#endif

