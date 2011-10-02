
#ifndef _Lattice_Mesh_Square2D_Specification_H_
#define _Lattice_Mesh_Square2D_Specification_H_

#include "lattice/node/coordinate/square-2d/specification.h"

namespace mysimulator {

  template <>
  struct LatticeMesh<SquareLattice,2U> {
    public:
      typedef LatticeMesh<SquareLattice,2U>   Type;
      
      bool data[65538]; // valid for 256x256 size

      LatticeMesh() : data() { nullify(); }
      ~LatticeMesh() { clearData(); }

      void clearData() { nullify(); }
      bool isvalid() const { return true; }
      void nullify() { for(unsigned int i=0;i<65538;++i) data[i]=false; }

      bool occupied(const Square2DCoordinateType& Pos) { return data[Pos()]; }
      void set_occupied(const Square2DCoordinateType& Pos) { data[Pos()]=true; }
      void remove_occupied(const Square2DCoordinateType& Pos) {
        data[Pos()]=false;
      }

    private:

      LatticeMesh(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(LatticeMesh<SquareLattice,2U>& M) { M.clearData(); }
  bool IsValid(const LatticeMesh<SquareLattice,2U>& M) { return M.isvalid(); }

}

#endif

