
#ifndef _Lattice_Node_Coordinate_Square2D_Plus_Specification_H_
#define _Lattice_Node_Coordinate_Square2D_Plus_Specification_H_

#include "lattice/node/coordinate/square/2d/specification.h"

namespace mysimulator {

  void plus(Square2DCoordinateType& X, const Square2DCoordinateType& Origin,
            const Square2DCoordinateType& Dpls) {
    X.c[0]=Origin.c[0]+Dpls.c[0];
    X.c[1]=Origin.c[1]+Dpls.c[1];
  }

}

#endif

