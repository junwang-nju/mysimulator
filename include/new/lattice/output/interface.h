
#ifndef _Lattice_Output_Interface_H_
#define _Lattice_Output_Interface_H_

#include "lattice/output/name.h"
#include "lattice/mesh/interface.h"
#include "lattice/node/coordinate/interface.h"
#include "array/1d/content/interface.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, LatticeOutputMethodName LON>
  struct LatticeOutput {
    public:
      typedef LatticeOutput<LSN,Dim,LON>  Type;
      typedef typename LatticeNodeCoordinate<LSN,Dim>::Type  CoorType;

      LatticeOutput() {}
      ~LatticeOutput() { clearData(); }

      void clearData() {}
      bool isvalid() const { return false; }

      void operator()(
          const Array1DContent<int>& Branch, const LatticeMesh<LSN,Dim>& M,
          const Array1DContent<CoorType>& Pos) {
        Error("This LatticeOutput Not Implemented!");
      }

    private:
      LatticeOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }
  };

  template <LatticeShapeName LSN, unsigned int Dim, LatticeOutputMethodName LON>
  void release(LatticeOutput<LSN,Dim,LON>& O) { O.clearData(); }

  template <LatticeShapeName LSN, unsigned int Dim, LatticeOutputMethodName LON>
  bool IsValid(const LatticeOutput<LSN,Dim,LON>& O) { return O.isvalid(); }

}

#include "lattice/output/null/specification.h"
#include "lattice/output/square/stream/specification.h"
#include "lattice/output/square/box/specification.h"

#endif

