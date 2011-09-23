
#ifndef _Lattice_Shape_Create_Neighbor_H_
#define _Lattice_Shape_Create_Neighbor_H_

#include "lattice/shape/name.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, typename CoorType>
  void createNeighbor(CoorType& coor, const unsigned int& bd) {
    Error("Unknown Shape with Dim!");
  }

  template <LatticeShapeName LSN, unsigned int Dim, typename CoorType>
  void createNeighbor(const CoorType& coor0, const unsigned int& bd,
                      CoorType& coor) { Error("Unknown Shape with Dim!"); }

}

#include "lattice/shape/square-2d/create-neighbor-specification.h"

#endif

