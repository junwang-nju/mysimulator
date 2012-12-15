
#ifndef _System_Interaction_Parameter_Pairwise_Core12_Name_H_
#define _System_Interaction_Parameter_Pairwise_Core12_Name_H_

namespace mysimulator {

  class PairCore12ParameterName {

    public:

      static const unsigned int EqStrength      = 0;
      static const unsigned int TwlfEqStrength  = EqStrength+1;
      static const unsigned int NumberParameter = TwlfEqStrength+1;

  };

  const unsigned int PairCore12ParameterName::EqStrength;
  const unsigned int PairCore12ParameterName::TwlfEqStrength;
  const unsigned int PairCore12ParameterName::NumberParameter;

}

#endif

