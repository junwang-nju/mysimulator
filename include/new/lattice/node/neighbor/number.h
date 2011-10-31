
#ifndef _Lattice_Node_Neighbor_Number_H_
#define _Lattice_Node_Neighbor_Number_H_

#include "lattice/shape/name.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  unsigned int NumNeighbors() {
    Error("Not Valid for this Lattice!");
    return 0;
  }

}

#include "lattice/node/neighbor/square-2d/number-specification.h"

#endif

