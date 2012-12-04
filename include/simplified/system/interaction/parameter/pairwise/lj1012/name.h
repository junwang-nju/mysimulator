
#ifndef _System_Interaction_Parameter_Pairwise_LJ1012_Name_H_
#define _System_Interaction_Parameter_Pairwise_LJ1012_Name_H_

namespace mysimulator {

  class PairLJ1012ParameterName {

    public:

      static const unsigned int EqRadius          = 0;
      static const unsigned int EqEnergyDepth     = EqRadius+1;
      static const unsigned int FactorA           = EqEnergyDepth+1;
      static const unsigned int FactorB           = FactorA+1;
      static const unsigned int DFactorA          = FactorB+1;
      static const unsigned int DFactorB          = DFactorA+1;
      static const unsigned int NumberParameter   = DFactorB+1;

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

