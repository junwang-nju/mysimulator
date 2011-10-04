
#ifndef _Lattice_Mesh_Allocate_H_
#define _Lattice_Mesh_Allocate_H_

#include "lattice/mesh/interface.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void allocate(LatticeMesh<LSN,Dim>& M) {
    Error("Allocation of Mesh Not Implemented!");
  }

}

#include "lattice/mesh/square/2d/allocate-specification.h"
#include "lattice/mesh/square/3d/allocate-specification.h"

#endif

