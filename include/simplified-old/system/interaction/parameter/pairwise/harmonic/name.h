
#ifndef _System_Interaction_Parameter_Pairwise_Harmonic_Name_H_
#define _System_Interaction_Parameter_Pairwise_Harmonic_Name_H_

namespace mysimulator {

  class PairHarmonicParameterName {
    public:
      static const unsigned int EqLength;
      static const unsigned int EqStrength;
      static const unsigned int DualEqStrength;
      static const unsigned int NumberParameter;
  };

  const unsigned int PairHarmonicParameterName::EqLength        = 0;
  const unsigned int PairHarmonicParameterName::EqStrength      = 1;
  const unsigned int PairHarmonicParameterName::DualEqStrength  = 2;
  const unsigned int PairHarmonicParameterName::NumberParameter = 3;

}

#endif

