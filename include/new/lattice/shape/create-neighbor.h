
#ifndef _Lattice_Shape_Create_Neighbor_H_
#define _Lattice_Shape_Create_Neighbor_H_

#include "lattice/shape/coordinate-type.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void createNeighbor(typename LatticeCoordinate<LSN,Dim>::Type& coor,
                      const unsigned char& bd) {
    Error("Unknown Shape with Dim!");
  }

  template <LatticeShapeName LSN, unsigned int Dim>
  void createNeighbor(const typename LatticeCoordinate<LSN,Dim>::Type& coor0,
                      const unsigned char& bd,
                      typename LatticeCoordinate<LSN,Dim>::Type& coor) {
    Error("Unknown Shape with Dim!");
  }

}

#include "lattice/shape/square-2d/create-neighbor-specification.h"

#endif

