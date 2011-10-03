
#ifndef _Lattice_Node_Coordinate_Square2D_Create_Specification_H_
#define _Lattice_Node_Coordinate_Square2D_Create_Specification_H_

#include "intrinsic-type/constant.h"

namespace mysimulator {

  static const char Square2DCoordinateShift[4][2]=
    { {   1,   0   },     // x plus 1
      {   0,   1   },     // y plus 1
      {   0,  -1   },     // y minus 1
      {  -1,   0   } };   // x minus 1

}

#include "lattice/node/coordinate/create.h"

namespace mysimulator {

  template <>
  void create<SquareLattice,2U>(Square2DCoordinateType& coor,
                                const unsigned char& bond) {
    coor.c[0]+=Square2DCoordinateShift[bond][0];
    coor.c[1]+=Square2DCoordinateShift[bond][1];
  }

  template <>
  void create<SquareLattice,2U>(const Square2DCoordinateType& coor0,
                                const unsigned char& bond,
                                Square2DCoordinateType& coor) {
    coor.c[0]=coor0.c[0]+Square2DCoordinateShift[bond][0];
    coor.c[1]=coor0.c[1]+Square2DCoordinateShift[bond][1];
  }

}

#endif

