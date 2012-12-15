
#ifndef _System_Interaction_Function_Pairwise_LJ612_Post_Name_H_
#define _System_Interaction_Function_Pairwise_LJ612_Post_Name_H_

namespace mysimulator {

  class PairLJ612PostName {

    public:

      static const unsigned int IvDistanceSQ   = 0;
      static const unsigned int IvDistance6    = IvDistanceSQ+1;
      static const unsigned int NumberPost     = IvDistance6+1;

  };

  const unsigned int PairLJ612PostName::IvDistanceSQ;
  const unsigned int PairLJ612PostName::IvDistance6;
  const unsigned int PairLJ612PostName::NumberPost;

}

#endif

