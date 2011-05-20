
#ifndef _Lattice_Motif_Chain_Copy_H_
#define _Lattice_Motif_Chain_Copy_H_

#include "lattice/motif-chain/interface.h"
#include "vector/copy.h"

namespace mysimulator {

  template <LatticeShapeName LS, unsigned int D, unsigned int L>
  void copy(LatticeMotifChain<LS,D,L>& C, const LatticeMotifChain<LS,D,L>& cC) {
    assert(IsValid(C)&&IsValid(cC));
    copy(C.motifValue,cC.motifValue);
  }

}

#endif

