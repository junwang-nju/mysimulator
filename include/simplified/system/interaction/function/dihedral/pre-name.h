
#ifndef _System_Interaction_Function_Dihedral_Pre_Name_H_
#define _System_Interaction_Function_Dihedral_Pre_Name_H_

namespace mysimulator {

  class DihedralPreName {

    public:

      static const unsigned int IvNormASQ           = 0;
      static const unsigned int IvNormBSQ           = IvNormASQ+1;
      static const unsigned int DotNormAB           = IvNormBSQ+1;
      static const unsigned int CrossNormAB         = DotNormAB+1;
      static const unsigned int AxisSQ              = CrossNormAB+1;
      static const unsigned int DotBondAB           = AxisSQ+1;
      static const unsigned int DotBondBC           = DotBondAB+1;
      static const unsigned int NumberPre           = DotBondBC+1;

  };

  const unsigned int DihedralPreName::IvNormASQ;
  const unsigned int DihedralPreName::IvNormBSQ;
  const unsigned int DihedralPreName::DotNormAB;
  const unsigned int DihedralPreName::CrossNormAB;
  const unsigned int DihedralPreName::AxisSQ;
  const unsigned int DihedralPreName::DotBondAB;
  const unsigned int DihedralPreName::DotBondBC;
  const unsigned int DihedralPreName::NumberPre;

}

#endif

