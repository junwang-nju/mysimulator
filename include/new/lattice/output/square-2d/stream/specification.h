
#ifndef _Lattice_Output_Square2D_Stream_Specification_H_
#define _Lattice_Output_Square2D_Stream_Specification_H_

#include "lattice/output/interface.h"
#include "array/1d/io.h"

namespace mysimulator {

  template <>
  struct LatticeOutput<SquareLattice,2U,StreamOutput> {
    public:
      typedef LatticeOutput<SquareLattice,2U,StreamOutput>  Type;
      typedef typename LatticeNodeCoordinate<SquareLattice,2U>::Type
              CoorType;

      FileOutput OS;

      LatticeOutput() : OS(stdout) {}
      ~LatticeOutput() { clearData(); }

      void clearData() { OS.close(); }
      bool isvalid() const { return IsValid(OS); }

      void operator()(const Array1DContent<int>& Branch,
                      const LatticeMesh<SquareLattice,2U>& M,
                      const Array1DContent<CoorType>& Pos) {
        assert(IsValid(OS));
        OS<<Branch<<Endl;
      }

    private:
      LatticeOutput(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

