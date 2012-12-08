
#ifndef _System_Interaction_Function_Dihedral_Neighbor_Name_H_
#define _System_Interaction_Function_Dihedral_Neighbor_Name_H_

namespace mysimulator {

  class DihedralNeighborName {

    public:

      static const unsigned int NormA           = 0;
      static const unsigned int NormB           = NormA+1;
      static const unsigned int Axis            = NormB+1;
      static const unsigned int DotAB           = Axis+1;
      static const unsigned int DotBC           = DotAB+1;
      static const unsigned int NumberNeighbor  = DotBC+1;

  };

  const unsigned int DihedralNeighborName::NormA;
  const unsigned int DihedralNeighborName::NormB;
  const unsigned int DihedralNeighborName::Axis;
  const unsigned int DihedralNeighborName::DotAB;
  const unsigned int DihedralNeighborName::DotBC;
  const unsigned int DihedralNeighborName::NumberNeighbor;

}

#endif

