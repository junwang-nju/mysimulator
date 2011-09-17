
#ifndef _Lattice_Shape_Create_Neighbor_H_
#define _Lattice_Shape_Create_Neighbor_H_

#include "lattice/shape/name.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void createNeighbor(int* const& coor, const unsigned int& bd) {
    Error("Unknown Shape with Dim!");
  }

  template <>
  void createNeighbor<SquareLattice,2>(int* const& coor,const unsigned int& bd){
    switch(bd) {
      case 0: coor[0]++; break;
      case 1: coor[1]++; break;
      case 2: coor[1]--; break;
      case 3: coor[0]--; break;
      default: Error("Improper bond type!");
    }
  }

  template <LatticeShapeName LSN, unsigned int Dim>
  void createNeighbor(const int* const& coor0, const unsigned int& bd,
                      int* const& coor) { Error("Unknown Shape with Dim!"); }

  template <>
  void createNeighbor<SquareLattice,2>(
      const int* const& coor0, const unsigned int& bd, int* const& coor) {
    coor[0]=coor0[0];
    coor[1]=coor0[1];
    createNeighbor<SquareLattice,2>(coor,bd);
  }

}

#endif

