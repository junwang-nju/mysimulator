
#ifndef _Lattice_Shape_Coordinate_Type_H_
#define _Lattice_Shape_Coordinate_Type_H_

#include "lattice/shape/name.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeCoordinate {};

}

#include "lattice/shape/square-2d/coordinate-type-specification.h"

#endif

