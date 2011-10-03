
#ifndef _Lattice_Node_Coordinate_Square2D_Copy_Specification_H_
#define _Lattice_Node_Coordinate_Square2D_Copy_Specification_H_

#include "lattice/node/coordinate/square/2d/specification.h"

namespace mysimulator {

  void copy(Square2DCoordinateType& X, const Square2DCoordinateType& cX) {
    X.us=cX.us;
  }

}

#endif

