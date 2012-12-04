
#ifndef _System_Interaction_Function_Pairwise_LJ1012_Post_Name_H_
#define _System_Interaction_Function_Pairwise_LJ1012_Post_Name_H_

namespace mysimulator {

  class PairLJ1012PostName {

    public:

      static const unsigned int IvDistanceSQ      = 0;
      static const unsigned int IvDistance10      = IvDistanceSQ+1;
      static const unsigned int NumberPost        = IvDistance10+1;

  };

  const unsigned int PairLJ1012PostName::IvDistanceSQ;
  const unsigned int PairLJ1012PostName::IvDistance10;
  const unsigned int PairLJ1012PostName::NumberPost;

}

#endif

