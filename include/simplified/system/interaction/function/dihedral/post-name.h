
#ifndef _System_Interaction_Function_Dihedral_Post_Name_H_
#define _System_Interaction_Function_Dihedral_Post_Name_H_

namespace mysimulator {

  class DihedralPostName {

    public:

      static const unsigned int Angle         = 0;
      static const unsigned int FactorI       = Angle+1;
      static const unsigned int FactorJ       = FactorI+1;
      static const unsigned int FactorK       = FactorJ+1;
      static const unsigned int FactorL       = FactorK+1;
      static const unsigned int NumberPost    = FactorL+1;

  };

  const unsigned int DihedralPostName::Angle;
  const unsigned int DihedralPostName::FactorI;
  const unsigned int DihedralPostName::FactorJ;
  const unsigned int DihedralPostName::FactorK;
  const unsigned int DihedralPostName::FactorL;
  const unsigned int DihedralPostName::NumberPost;

}

#endif

