
#ifndef _Lattice_Motif_Chain_Copy_H_
#define _Lattice_Motif_Chain_Copy_H_

#include "lattice/motif-chain/interface.h"
#include "vector/copy.h"

namespace mysimulator {

  template <LatticeShapeName LS, unsigned int Dim>
  void copy(LatticeMotifChain<LS,Dim>& C, const LatticeMotifChain<LS,Dim>& cC) {
    assert(IsValid(C)&&IsValid(cC));
    assert(C.Length()==cC.Length());
    copy(C.motifID,cC.motifID);
  }

}

#endif

