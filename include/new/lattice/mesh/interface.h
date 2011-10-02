
#ifndef _Lattice_Mesh_Interface_H_
#define _Lattice_Mesh_Interface_H_

#include "lattice/shape/name.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeMesh {
    public:
      typedef LatticeMesh<LSN,Dim>  Type;
      LatticeMesh() {}
      ~LatticeMesh() { clearData(); }
      void clearData() {}
      bool isvalid() const { return false; }
    private:
      LatticeMesh(const Type&) {}
      Type& operator=(const Type&) { return *this; }
  };

  template <LatticeShapeName LSN, unsigned int Dim>
  void release(LatticeMesh<LSN,Dim>& M) { M.clearData(); }

  template <LatticeShapeName LSN, unsigned int Dim>
  bool IsValid(const LatticeMesh<LSN,Dim>& M) { return M.isvalid(); }

}

#include "lattice/mesh/square-2d/specification.h"

#endif

