
#ifndef _Lattice_Enumerate_RunData_Square2D_Allocate_H_
#define _Lattice_Enumerate_RunData_Square2D_Allocate_H_

#include "lattice/enumerate/run-data/square-2d/specification.h"
#include "lattice/motif-chain/allocate.h"

namespace mysimulator {

  template <unsigned int Len>
  void allocate(LatticeEumRunData<SquareLattice,2U,Len>& D) {
    allocate(D.Mesh,(1<<16));
    allocate(D.C);
    allocate(M.Pos,Len);
    allocate(M.RunRegion,LatticeMotifChain<SquareLattice,2U,Len>::NumMotifs);
    allocate(M.MotifPosHead,LatticeMotifChain<SquareLattice,2U,Len>::NumMotifs);
    allocate(M.MotifPosTail,LatticeMotifChain<SquareLattice,2U,Len>::NumMotifs);
    D.RunMotifLoc=-1;
  }

}

#endif

