
#ifndef _System_Interaction_Function_Pairwise_Vec_Name_H_
#define _System_Interaction_Function_Pairwise_Vec_Name_H_

namespace mysimulator {

  class PairwiseVecName {

    public:
    
      static const unsigned int BondVecIJ       = 0;
      static const unsigned int ScaledBondVecIJ = BondVecIJ+1;
      static const unsigned int NumberVec       = ScaledBondVecIJ+1;

  };

  const unsigned int PairwiseVecName::BondVecIJ;
  const unsigned int PairwiseVecName::ScaledBondVecIJ;
  const unsigned int PairwiseVecName::NumberVec;

}

#endif

