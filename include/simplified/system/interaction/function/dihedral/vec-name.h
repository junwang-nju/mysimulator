
#ifndef _System_Interaction_Function_Dihedral_Vec_Name_H_
#define _System_Interaction_Function_Dihedral_Vec_Name_H_

namespace mysimulator {

  class DihedralVecName {

    public:

      static const unsigned int BondJI          = 0;
      static const unsigned int BondKJ          = BondJI+1;
      static const unsigned int BondLK          = BondKJ+1;
      static const unsigned int NormA           = BondLK+1;
      static const unsigned int NormB           = NormA+1;
      static const unsigned int CrossNorm       = NormB+1;
      static const unsigned int NumberVec       = CrossNorm+1;

  };

  const unsigned int DihedralVecName::BondJI;
  const unsigned int DihedralVecName::BondKJ;
  const unsigned int DihedralVecName::BondLK;
  const unsigned int DihedralVecName::NormA;
  const unsigned int DihedralVecName::NormB;
  const unsigned int DihedralVecName::CrossNorm;
  const unsigned int DihedralVecName::NumberVec;

}

#endif

