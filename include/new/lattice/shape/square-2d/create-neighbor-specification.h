
#ifndef _Square_2D_Create_Neighbor_Specification_H_
#define _Square_2D_Create_Neighbor_Specification_H_

#include "lattice/shape/create-neighbor.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  static const unsigned short int Square2DCoordinateShift[4]={
    cOne, cOne<<8, cNOne<<8, cNOne };

  template <>
  void createNeighbor<SquareLattice,2>(Square2DCoordinateType& coor,
                                       const unsigned char& bd) {
    coor.us+=Square2DCoordinateShift[bd-'0'];
  }

  template <>
  void createNeighbor<SquareLattice,2>(const Square2DCoordinateType& coor0,
                                       const unsigned char& bd,
                                       Square2DCoordinateType& coor) {
    coor.us=coor0.us+Square2DCoordinateShift[bd-'0'];
  }

}

#endif

