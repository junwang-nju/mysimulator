
#ifndef _System_Interaction_Function_Pairwise_Harmonic_Post_Name_H_
#define _System_Interaction_Function_Pairwise_Harmonic_Post_Name_H_

namespace mysimulator {

  class PairHarmonicPostName {

    public:

      static const unsigned int Length      = 0;
      static const unsigned int IvLength    = Length+1;
      static const unsigned int NumberPost  = IvLength+1;

  };

  const unsigned int PairHarmonicPostName::Length;
  const unsigned int PairHarmonicPostName::IvLength;
  const unsigned int PairHarmonicPostName::NumberPost;

}

#endif

