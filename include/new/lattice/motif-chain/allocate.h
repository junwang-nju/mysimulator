
#ifndef _Lattice_MotifChain_Allocate_H_
#define _Lattice_MotifChain_Allocate_H_

#include "lattice/motif-chain/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  void allocate(LatticeMotifChain<LSN,Dim,Len>& C) {
    assert(Len>1);
    release(C);
    allocate(C.SegMotif,LatticeMotifChain<LSN,Dim,Len>::NumMotifs);
  }

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  void imprint(LatticeMotifChain<LSN,Dim,Len>& C,
               const LatticeMotifChain<LSN,Dim,Len>&) { allocate(C); }

}

#endif

