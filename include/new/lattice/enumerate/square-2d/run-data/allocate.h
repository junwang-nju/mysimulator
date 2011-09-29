
#ifndef _Lattice_Enumerate_Square2D_RunData_Allocate_H_
#define _Lattice_Enumerate_Square2D_RunData_Allocate_H_

#include "lattice/enumerate/square-2d/run-data/interface.h"
#include "lattice/motif-chain/allocate.h"

namespace mysimulator {

  template <unsigned int Len>
  void allocate(LatticeSquare2DEnumRunData<Len>& D) {
    allocate(D.Mesh,65536U);
    allocate(D.C);
    allocate(D.TLoc,LatticeMotifChain<SquareLattice,2U,Len>::NumMotifs);
  }

}

#endif

