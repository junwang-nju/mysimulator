
#ifndef _System_Interaction_Parameter_Pairwise_LJ1012_Name_H_
#define _System_Interaction_Parameter_Pairwise_LJ1012_Name_H_

namespace mysimulator {

  class PairLJ1012ParameterName {

    public:

      static const unsigned int EqRadius          = 0;
      static const unsigned int EqEnergyDepth     = 1;
      static const unsigned int FactorA           = 2;
      static const unsigned int FactorB           = 3;
      static const unsigned int DFactorA          = 4;
      static const unsigned int DFactorB          = 5;
      static const unsigned int NumberParameter   = 6;

  };

  const unsigned int PairLJ1012ParameterName::EqRadius;
  const unsigned int PairLJ1012ParameterName::EqEnergyDepth;
  const unsigned int PairLJ1012ParameterName::FactorA;
  const unsigned int PairLJ1012ParameterName::FactorB;
  const unsigned int PairLJ1012ParameterName::DFactorA;
  const unsigned int PairLJ1012ParameterName::DFactorB;
  const unsigned int PairLJ1012ParameterName::NumberParameter;

}

#endif

