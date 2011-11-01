
#ifndef _Lattice_Mesh_Square3D_Specification_H_
#define _Lattice_Mesh_Square3D_Specification_H_

#include "lattice/node/coordinate/square/3d/specification.h"
#include "intrinsic-type/release.h"
#include "intrinsic-type/valid.h"
#include <cassert>

namespace mysimulator {

  template <>
  struct LatticeMesh<SquareLattice,3U> {
    public:
      typedef LatticeMesh<SquareLattice,3U>   Type;
      
      bool *data; // valid for 256x256*256 size

      LatticeMesh() : data(NULL) {}
      ~LatticeMesh() { clearData(); }

      void clearData() { delete_array(data); } 
      bool isvalid() const { return IsValid(data); }
      void nullify() {
        assert(isvalid());
        for(unsigned int i=0;i<16777216U;++i) data[i]=false;
      }

      bool occupied(const Square3DCoordinateType& Pos) const {
        assert(isvalid());
        return data[Pos()];
      }
      void set_occupied(const Square3DCoordinateType& Pos) {
        assert(isvalid());
        data[Pos()]=true;
      }
      void remove_occupied(const Square3DCoordinateType& Pos) {
        assert(isvalid());
        data[Pos()]=false;
      }

    private:

      LatticeMesh(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

