
#ifndef _Lattice_Output_Null_Specification_H_
#define _Lattice_Output_Null_Specification_H_

#include "lattice/output/interface.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  struct LatticeOutput<LSN,Dim,NullOutput> {

    public:

      typedef LatticeOutput<LSN,Dim,NullOutput> Type;
      typedef typename LatticeNodeCoordinate<LSN,Dim>::Type  CoorType;

      LatticeOutput() {}
      ~LatticeOutput() { clearData(); }

      void clearData() {}
      bool isvalid() const { return true; }

      void operator()(
          const Array1DContent<int>& Branch, const LatticeMesh<LSN,Dim>& M,
          const Array1DContent<CoorType>& Pos) {}

    private:

      LatticeOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

