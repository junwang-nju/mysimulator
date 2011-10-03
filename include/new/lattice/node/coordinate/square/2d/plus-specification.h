
#ifndef _Lattice_Node_Coordinate_Square2D_Plus_Specification_H_
#define _Lattice_Node_Coordinate_Square2D_Plus_Specification_H_

#include "lattice/node/coordinate/square/2d/specification.h"

namespace mysimulator {

  void plus(Square2DCoordinateType& X, const Square2DCoordinateType& Origin,
            const Square2DCoordinateType& Dpls) {
    X.us=Origin.us+Dpls.us;
  }

}

#endif

