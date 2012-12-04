
#ifndef _System_Interaction_Function_Pairwise_Core12_Post_Name_H_
#define _System_Interaction_Function_Pairwise_Core12_Post_Name_H_

namespace mysimulator {

  class PairCore12PostName {

    public:

      static const unsigned int IvDistance12  = 0;
      static const unsigned int IvDistance14  = IvDistance12+1;
      static const unsigned int NumberPost    = IvDistance14+1;

  };

  const unsigned int PairCore12PostName::IvDistance12;
  const unsigned int PairCore12PostName::IvDistance14;
  const unsigned int PairCore12PostName::NumberPost;

}

#endif

