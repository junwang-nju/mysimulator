
#ifndef _System_Interaction_Parameter_Pairwise_LJ612_Name_H_
#define _System_Interaction_Parameter_Pairwise_LJ612_Name_H_

namespace mysimulator {

  class PairLJ612ParameterName {
    public:
      static const unsigned int EqRadius;
      static const unsigned int EqEnergyDepth;
      static const unsigned int FactorA;
      static const unsigned int FactorB;
      static const unsigned int DFactorA;
      static const unsigned int DFactorB;
      static const unsigned int NumberParameter;
  };

  const unsigned int PairLJ612ParameterName::EqRadius         = 0;
  const unsigned int PairLJ612ParameterName::EqEnergyDepth    = 1;
  const unsigned int PairLJ612ParameterName::FactorA          = 2;
  const unsigned int PairLJ612ParameterName::FactorB          = 3;
  const unsigned int PairLJ612ParameterName::DFactorA         = 4;
  const unsigned int PairLJ612ParameterName::DFactorB         = 5;
  const unsigned int PairLJ612ParameterName::NumberParameter  = 6;

}

#endif

