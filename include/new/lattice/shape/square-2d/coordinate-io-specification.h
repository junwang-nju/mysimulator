
#ifndef _Lattice_Shape_Square2D_Coordinate_InputOutput_H_
#define _Lattice_Shape_Square2D_Coordinate_InputOutput_H_

#include "lattice/shape/square-2d/coordinate-type-specification.h"
#include "io/output/base/interface.h"

namespace mysimulator {

  OutputBase& operator<<(OutputBase& os, const Square2DCoordinateType& X) {
    os<<static_cast<int>(X.c[0])<<"\t"<<static_cast<int>(X.c[1]);
    return os;
  }

}

#endif

