
#ifndef _Lattice_Shape_Square2D_Coordinate_Type_Specification_H_
#define _Lattice_Shape_Square2D_Coordinate_Type_Specification_H_

namespace mysimulator {

  union Square2DCoordinateType {
    unsigned short int us;
    char c[2];
  };

}

#include "lattice/shape/coordinate-type.h"

namespace mysimulator {

  template <>
  struct LatticeCoordinate<SquareLattice,2> {
    typedef Square2DCoordinateType  Type;
  };

}

#endif

