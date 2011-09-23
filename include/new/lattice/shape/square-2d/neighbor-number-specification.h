
#ifndef _Square_2D_Neighbor_Number_Specification_H_
#define _Square_2D_Neighbor_Number_Specification_H_

#include "lattice/shape/name.h"

namespace mysimulator {

  template <>
  unsigned int NumNeighbors<SquareLattice,2>() { return 4; }

}

#endif

