
#ifndef _Lattice_Motif_Chain_Allocate_H_
#define _Lattice_Motif_Chain_Allocate_H_

#include "lattice/motif-chain/interface.h"
#include "vector/allocate.h"

namespace mysimulator {

  template <LatticeShapeName LS, unsigned int Dim, unsigned int L>
  void allocate(LatticeMotifChain<LS,Dim,L>& C) {
    assert(L>1);
    release(C);
    allocate(C.motifValue,LatticeMotifChain<LS,Dim,L>::NumMotifs);
  }

  template <LatticeShapeName LS, unsigned int Dim, unsigned int L>
  void imprint(LatticeMotifChain<LS,Dim,L>& C,
               const LatticeMotifChain<LS,Dim,L>&) { allocate(C); }

}

#endif

