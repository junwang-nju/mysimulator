
#ifndef _Lattice_Node_Coordinate_Square3D_Create_Specification_H_
#define _Lattice_Node_Coordinate_Square3D_Create_Specification_H_

namespace mysimulator {

  static const char Square3DCoordinateShift[6][3]=
    {   {   1,    0,    0   },
        {   0,    1,    0   },
        {   0,    0,    1   },
        {   0,    0,   -1   },
        {   0,   -1,    0   },
        {  -1,    0,    0   }   };

}

#include "lattice/node/coordinate/create.h"

namespace mysimulator {

  template <>
  void create<SquareLattice,3U>(Square3DCoordinateType& coor,
                                const unsigned char& bond) {
    coor.c[0]+=Square3DCoordinateShift[bond][0];
    coor.c[1]+=Square3DCoordinateShift[bond][1];
    coor.c[2]+=Square3DCoordinateShift[bond][2];
  }

  template <>
  void create<SquareLattice,3U>(const Square3DCoordinateType& coor0,
                                const unsigned char& bond,
                                Square3DCoordinateType& coor) {
    coor.c[0]=coor0.c[0]+Square3DCoordinateShift[bond][0];
    coor.c[1]=coor0.c[1]+Square3DCoordinateShift[bond][1];
    coor.c[2]=coor0.c[2]+Square3DCoordinateShift[bond][2];
  }

}

#endif

