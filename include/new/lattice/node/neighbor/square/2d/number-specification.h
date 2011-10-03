
#ifndef _Lattice_Node_Neighbor_Number_Square2D_Specification_H_
#define _Lattice_Node_Neighbor_Number_Square2D_Specification_H_

#include "lattice/node/neighbor/number.h"

namespace mysimulator {

  template <>
  unsigned int NumNeighbors<SquareLattice,2U>() { return 4U; }

}

#endif

