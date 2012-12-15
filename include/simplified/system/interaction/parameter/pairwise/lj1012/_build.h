
#ifndef _System_Interaction_Parameter_Pairwise_LJ1012_Build_H_
#define _System_Interaction_Parameter_Pairwise_LJ1012_Build_H_

#include "system/interaction/parameter/pairwise/lj1012/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _build_pair_lj1012(
      Array<Double>& _FParam,Array<Int>&, Array<InteractionParameter>&) {
    assert((bool)_FParam);
    assert(_FParam.size()>=PairLJ1012ParameterName::NumberParameter);
    double tmd=_FParam[PairLJ1012ParameterName::EqRadius];
    tmd*=tmd;
    double tmd1=tmd*tmd;
    double tmd2=tmd1*tmd1*_FParam[PairLJ1012ParameterName::EqEnergyDepth];
    double A=tmd2*tmd1*5;
    double B=tmd2*tmd*6;
    _FParam[PairLJ1012ParameterName::FactorA]=A;
    _FParam[PairLJ1012ParameterName::FactorB]=B;
    _FParam[PairLJ1012ParameterName::DFactorA]=12*A;
    _FParam[PairLJ1012ParameterName::DFactorB]=10*B;
  }

}

#endif

