
#ifndef _Lattice_Node_Coordinate_Interface_H_
#define _Lattice_Node_Coordinate_Interface_H_

#include "lattice/shape/name.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeNodeCoordinate {};

}

#include "lattice/node/coordinate/square/2d/specification.h"

#endif

