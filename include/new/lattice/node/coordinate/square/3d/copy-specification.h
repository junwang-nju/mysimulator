
#ifndef _Lattice_Node_Coordinate_Square3D_Copy_Specification_H_
#define _Lattice_Node_Coordinate_Square3D_Copy_Specification_H_

#include "lattice/node/coordinate/square/3d/specification.h"

namespace mysimulator {

  void copy(Square3DCoordinateType& X, const Square3DCoordinateType& cX) {
    X.u=cX.u;
  }

}

#endif

