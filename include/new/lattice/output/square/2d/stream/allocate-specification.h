
#ifndef _Lattice_Output_Square2D_Stream_Allocate_Specification_H_
#define _Lattice_Output_Square2D_Stream_Allocate_Specification_H_

#include "lattice/output/square/2d/stream/specification.h"
#include "io/output/file/copy.h"

namespace mysimulator {

  void allocate(LatticeOutput<SquareLattice,2U,StreamOutput>& O) {
    release(O);
    copy(O.OS,COut);
  }

  void allocate(LatticeOutput<SquareLattice,2U,StreamOutput>& O,
                const char *fname) {
    release(O);
    O.OS.open(fname);
  }

}

#endif

