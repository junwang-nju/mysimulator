
#ifndef _System_Interaction_Function_Pairwise_Pre_Name_H_
#define _System_Interaction_Function_Pairwise_Pre_Name_H_

namespace mysimulator {

  class PairwisePreName {

    public:

      static const unsigned int DistanceSQ    = 0;
      static const unsigned int NumberPre     = DistanceSQ+1;

  };

  const unsigned int PairwisePreName::DistanceSQ;
  const unsigned int PairwisePreName::NumberPre;

}

#endif

