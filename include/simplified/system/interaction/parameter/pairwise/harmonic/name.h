
#ifndef _System_Interaction_Parameter_Pairwise_Harmonic_Name_H_
#define _System_Interaction_Parameter_Pairwise_Harmonic_Name_H_

namespace mysimulator {

  class PairHarmonicParameterName {

    public:

      static const unsigned int EqLength          = 0;
      static const unsigned int EqStrength        = EqLength+1;
      static const unsigned int DualEqStrength    = EqStrength+1;
      static const unsigned int NumberParameter   = DualEqStrength+1;

  };

  const unsigned int PairHarmonicParameterName::EqLength;
  const unsigned int PairHarmonicParameterName::EqStrength;
  const unsigned int PairHarmonicParameterName::DualEqStrength;
  const unsigned int PairHarmonicParameterName::NumberParameter;

}

#endif

