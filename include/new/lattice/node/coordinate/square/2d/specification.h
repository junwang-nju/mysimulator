
#ifndef _Lattice_Node_Coordinate_Square2D_Specification_H_
#define _Lattice_Node_Coordinate_Square2D_Specification_H_

namespace mysimulator {

  union Square2DCoordinateType {
    public:
      typedef Square2DCoordinateType  Type;

      unsigned short int us;
      char c[2];

      Square2DCoordinateType() : us(0) {}
      Type& operator=(const Type& C) { us=C.us; return *this; }

      unsigned short int& operator()() { return us; }
      const unsigned short int& operator()() const { return us; }

      void nullify() { us=0; }

    private:

      Square2DCoordinateType(const Type&) {}

  };

}

#include "lattice/node/coordinate/interface.h"

namespace mysimulator {

  template <>
  struct LatticeNodeCoordinate<SquareLattice,2U> {
    typedef Square2DCoordinateType  Type;
  };

}

#endif

