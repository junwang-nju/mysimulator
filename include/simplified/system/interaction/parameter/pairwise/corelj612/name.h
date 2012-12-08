
#ifndef _System_Interaction_Parameter_Pairwise_CoreLJ612_Name_H_
#define _System_Interaction_Parameter_Pairwise_CoreLJ612_Name_H_

#include "system/interaction/parameter/pairwise/lj612/name.h"

namespace mysimulator {

  class PairCoreLJ612ParameterName : public PairLJ612ParameterName {

    public:

      typedef PairLJ612ParameterName  ParentType;

      static const unsigned int EqRadiusSQ      = ParentType::NumberParameter;
      static const unsigned int NumberParameter = EqRadiusSQ+1;

  };

  const unsigned int PairCoreLJ612ParameterName::EqRadiusSQ;
  const unsigned int PairCoreLJ612ParameterName::NumberParameter;

}

#endif

