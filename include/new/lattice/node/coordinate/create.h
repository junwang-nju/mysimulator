
#ifndef _Lattice_Node_Coordinate_Create_H_
#define _Lattice_Node_Coordinate_Create_H_

#include "lattice/node/coordinate/interface.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void create(typename LatticeNodeCoordinate<LSN,Dim>::Type& coor,
              const unsigned char& bond) {
    Error("Create Operation Unknown for This Lattice!");
  }

  template <LatticeShapeName LSN, unsigned int Dim>
  void create(const typename LatticeNodeCoordinate<LSN,Dim>::Type& coor0,
              const unsigned char& bond,
              typename LatticeNodeCoordinate<LSN,Dim>::Type& coor) {
    Error("Create Operation Unknown for This Lattice!");
  }

}

#include "lattice/node/coordinate/square-2d/create-specification.h"

#endif

