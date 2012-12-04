
#ifndef _System_Interaction_Parameter_Pairwise_LJ612_Name_H_
#define _System_Interaction_Parameter_Pairwise_LJ612_Name_H_

namespace mysimulator {

  class PairLJ612ParameterName {

    public:

      static const unsigned int EqRadius          = 0;
      static const unsigned int EqEnergyDepth     = EqRadius+1;
      static const unsigned int FactorA           = EqEnergyDepth+1;
      static const unsigned int FactorB           = FactorA+1;
      static const unsigned int DFactorA          = FactorB+1;
      static const unsigned int DFactorB          = DFactorA+1;
      static const unsigned int NumberParameter   = DFactorB+1;

  };

  const unsigned int PairLJ612ParameterName::EqRadius;
  const unsigned int PairLJ612ParameterName::EqEnergyDepth;
  const unsigned int PairLJ612ParameterName::FactorA;
  const unsigned int PairLJ612ParameterName::FactorB;
  const unsigned int PairLJ612ParameterName::DFactorA;
  const unsigned int PairLJ612ParameterName::DFactorB;
  const unsigned int PairLJ612ParameterName::NumberParameter;

}

#endif

