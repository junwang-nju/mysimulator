
#ifndef _Lattice_Mesh_Square2D_Allocate_Specification_H_
#define _Lattice_Mesh_Square2D_Allocate_Specification_H_

#include "lattice/mesh/allocate.h"

namespace mysimulator {

  template <>
  void allocate(LatticeMesh<SquareLattice,2U>& M) {}

}

#endif

