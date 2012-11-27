
#ifndef _System_Interaction_Function_Pairwise_Vec_Name_H_
#define _System_Interaction_Function_Pairwise_Vec_Name_H_

namespace mysimulator {

  class PairwiseVecName {

    public:
    
      static const unsigned int PairBondVecIJ       = 0;
      static const unsigned int PairScaledBondVecIJ = 1;
      static const unsigned int PairwiseNumberVec   = 2;

  };

  const unsigned int PairwiseVecName::PairBondVecIJ;
  const unsigned int PairwiseVecName::PairScaledBondVecIJ;
  const unsigned int PairwiseVecName::PairwiseNumberVec;

}

#endif

