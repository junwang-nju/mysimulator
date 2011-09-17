
#ifndef _Lattice_Shape_Neighbor_Number_H_
#define _Lattice_Shape_Neighbor_Number_H_

#include "lattice/shape/name.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  unsigned int NumNeighbors() { Error("Unknown Shape with Dim!"); return 0; }

  template <>
  unsigned int NumNeighbors<SquareLattice,2>() { return 4; }

}

#endif

