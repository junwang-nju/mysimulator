
#ifndef _Lattice_Output_Square_Stream_Allocate_Specification_H_
#define _Lattice_Output_Square_Stream_Allocate_Specification_H_

#include "lattice/output/square/stream/specification.h"
#include "io/output/file/copy.h"

namespace mysimulator {

  template <unsigned int Dim>
  void allocate(LatticeOutput<SquareLattice,Dim,StreamOutput>& O) {
    release(O);
    copy(O.OS,COut);
  }

  template <unsigned int Dim>
  void allocate(LatticeOutput<SquareLattice,Dim,StreamOutput>& O,
                const char *fname) {
    release(O);
    O.OS.open(fname);
  }

}

#endif

