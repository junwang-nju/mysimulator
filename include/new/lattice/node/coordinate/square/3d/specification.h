
#ifndef _Lattice_Node_Coordinate_Square3D_Specification_H_
#define _Lattice_Node_Coordinate_Square3D_Specification_H_

namespace mysimulator {

  union Square3DCoordinateType {

    public:

      typedef Square3DCoordinateType  Type;

      unsigned int u;
      char c[4];

      Square3DCoordinateType() : u(0) {}
      Type& operator=(const Type& C) { u=C.u; return *this; }

      unsigned int& operator()() { return u; }
      const unsigned int& operator()() const { return u; }

      void nullify() { u=0; }

    private:

      Square3DCoordinateType(const Type&) {}

  };

}

#include "lattice/node/coordinate/interface.h"

namespace mysimulator {

  template <>
  struct LatticeNodeCoordinate<SquareLattice,3U> {
    typedef Square3DCoordinateType    Type;
  };

}

#endif

