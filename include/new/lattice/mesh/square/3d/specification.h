
#ifndef _Lattice_Mesh_Square3D_Specification_H_
#define _Lattice_Mesh_Square3D_Specification_H_

#include "lattice/node/coordinate/square/3d/specification.h"
#include "array/1d/fill.h"
#include <cassert>

namespace mysimulator {

  template <>
  struct LatticeMesh<SquareLattice,3U> {
    public:
      typedef LatticeMesh<SquareLattice,3U>   Type;
      
      Array1D<bool> data; // valid for 256x256*256 size

      LatticeMesh() : data() {}
      ~LatticeMesh() { clearData(); }

      void clearData() { release(data); } 
      bool isvalid() const { return IsValid(data); }
      void nullify() {  assert(isvalid()); fill(data,false); }

      bool occupied(const Square3DCoordinateType& Pos) const {
        return data[Pos()];
      }
      void set_occupied(const Square3DCoordinateType& Pos) { data[Pos()]=true; }
      void remove_occupied(const Square3DCoordinateType& Pos) {
        data[Pos()]=false;
      }

    private:

      LatticeMesh(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

