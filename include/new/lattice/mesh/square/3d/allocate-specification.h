
#ifndef _Lattice_Mesh_Square3D_Allocate_Specification_H_
#define _Lattice_Mesh_Square3D_Allocate_Specification_H_

#include "lattice/mesh/allocate.h"

namespace mysimulator {

  template <>
  void allocate(LatticeMesh<SquareLattice,3U>& M) {
    release(M);
    allocate(M.data,16777216U);
  }

}

#endif

