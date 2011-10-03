
#ifndef _Lattice_Node_Neighbor_Number_Square3D_Specification_H_
#define _Lattice_Node_Neighbor_Number_Square3D_Specification_H_

#include "lattice/node/neighbor/number.h"

namespace mysimulator {

  template <>
  unsigned int NumNeighbors<SquareLattice,3U>() { return 6U; }

}

#endif

