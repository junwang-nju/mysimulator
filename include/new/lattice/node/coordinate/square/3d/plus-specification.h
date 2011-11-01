
#ifndef _Lattice_Node_Coordinate_Square3D_Plus_Specification_H_
#define _Lattice_Node_Coordinate_Square3D_Plus_Specification_H_

#include "lattice/node/coordinate/square/3d/specification.h"

namespace mysimulator {

  void plus(Square3DCoordinateType& X, const Square3DCoordinateType& Origin,
            const Square3DCoordinateType& Dpls) {
    X.c[0]=Origin.c[0]+Dpls.c[0];
    X.c[1]=Origin.c[1]+Dpls.c[1];
    X.c[2]=Origin.c[2]+Dpls.c[2];
  }

}

#endif

