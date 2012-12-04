
#ifndef _System_Interaction_Parameter_Pairwise_LJ612Cut_Name_H_
#define _System_Interaction_Parameter_Pairwise_LJ612Cut_Name_H_

#include "system/interaction/parameter/pairwise/lj612/name.h"

namespace mysimulator {

  class PairLJ612CutParameterName {

    public:

      static const unsigned int EqRadius
        = PairLJ612ParameterName::EqRadius;
      static const unsigned int EqEnergyDepth
        = PairLJ612ParameterName::EqEnergyDepth;
      static const unsigned int FactorA
        = PairLJ612ParameterName::FactorA;
      static const unsigned int FactorB
        = PairLJ612ParameterName::FactorB;
      static const unsigned int DFactorA
        = PairLJ612ParameterName::DFactorA;
      static const unsigned int DFactorB
        = PairLJ612ParameterName::DFactorA;
      static const unsigned int CutR              = 6;
      static const unsigned int CutRSQ            = 7;
      static const unsigned int Vc                = 8;
      static const unsigned int Kc                = 9;
      static const unsigned int NumberParameter   = 10;

  };

  const unsigned int PairLJ612CutParameterName::EqRadius;
  const unsigned int PairLJ612CutParameterName::EqEnergyDepth;
  const unsigned int PairLJ612CutParameterName::FactorA;
  const unsigned int PairLJ612CutParameterName::FactorB;
  const unsigned int PairLJ612CutParameterName::DFactorA;
  const unsigned int PairLJ612CutParameterName::DFactorB;
  const unsigned int PairLJ612CutParameterName::CutR;
  const unsigned int PairLJ612CutParameterName::CutRSQ;
  const unsigned int PairLJ612CutParameterName::Vc;
  const unsigned int PairLJ612CutParameterName::Kc;
  const unsigned int PairLJ612CutParameterName::NumberParameter;

}

#endif

