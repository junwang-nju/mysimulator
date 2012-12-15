
#ifndef _System_Interaction_Parameter_Pairwise_LJ612Cut_Name_H_
#define _System_Interaction_Parameter_Pairwise_LJ612Cut_Name_H_

#include "system/interaction/parameter/pairwise/lj612/name.h"

namespace mysimulator {

  class PairLJ612CutParameterName : public PairLJ612ParameterName {

    public:

      typedef PairLJ612ParameterName  ParentType;

      static const unsigned int CutR            = ParentType::NumberParameter;
      static const unsigned int CutRSQ          = CutR+1;
      static const unsigned int Vc              = CutRSQ+1;
      static const unsigned int Kc              = Vc+1;
      static const unsigned int NumberParameter = Kc+1;

  };

  const unsigned int PairLJ612CutParameterName::CutR;
  const unsigned int PairLJ612CutParameterName::CutRSQ;
  const unsigned int PairLJ612CutParameterName::Vc;
  const unsigned int PairLJ612CutParameterName::Kc;
  const unsigned int PairLJ612CutParameterName::NumberParameter;

}

#endif

