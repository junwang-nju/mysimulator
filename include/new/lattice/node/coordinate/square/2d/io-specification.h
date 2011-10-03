
#ifndef _Lattice_Node_Coordinate_Square2D_InputOutput_Specification_H_
#define _Lattice_Node_Coordinate_Square2D_InputOutput_Specification_H_

#include "lattice/node/coordinate/square/2d/specification.h"
#include "io/output/base/interface.h"

namespace mysimulator {

  OutputBase& operator<<(OutputBase& os, const Square2DCoordinateType& X) {
    os<<static_cast<int>(X.c[0])<<"\t"<<static_cast<int>(X.c[1]);
    return os;
  }

}

#endif

