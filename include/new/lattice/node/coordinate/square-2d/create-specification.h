
#ifndef _Lattice_Node_Coordinate_Square2D_Create_Specification_H_
#define _Lattice_Node_Coordinate_Square2D_Create_Specification_H_

#include "intrinsic-type/constant.h"

namespace mysimulator {

  static const unsigned short int Square2DCoordinateShift[4]={
    cOne,       // x plus 1
    cOne<<8,    // y plus 1
    cNOne<<8,   // y minus 1
    cNOne       // x minus 1
  };
}

#include "lattice/node/coordinate/create.h"

namespace mysimulator {

  template <>
  void create<SquareLattice,2U>(Square2DCoordinateType& coor,
                                const unsigned char& bond) {
    coor()+=Square2DCoordinateShift[bond];
  }

  template <>
  void create<SquareLattice,2U>(const Square2DCoordinateType& coor0,
                                const unsigned char& bond,
                                Square2DCoordinateType& coor) {
    coor()=coor0()+Square2DCoordinateShift[bond];
  }

}

#endif

