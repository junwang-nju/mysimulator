
#ifndef _Lattice_Node_Coordinate_Square3D_InputOutput_Specification_H_
#define _Lattice_Node_Coordinate_Square3D_InputOutput_Specification_H_

#include "lattice/node/coordinate/square/3d/specification.h"
#include "io/output/base/interface.h"

namespace mysimulator {

  OutputBase& operator<<(OutputBase& os, const Square3DCoordinateType& X) {
    os<<static_cast<int>(X.c[0])<<"\t"<<static_cast<int>(X.c[1])<<"\t";
    os<<static_cast<int>(X.c[2]);
    return os;
  }

}

#endif

