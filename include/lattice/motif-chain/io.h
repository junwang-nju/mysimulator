
#ifndef _Lattice_Motif_Chain_InputOutput_H_
#define _Lattice_Motif_Chain_InputOutput_H_

#include "lattice/motif-chain/interface.h"
#include "vector/io.h"

namespace mysimulator {

  template <LatticeShapeName LS, unsigned int D, unsigned int L>
  OutputBase& operator<<(OutputBase& os, const LatticeMotifChain<LS,D,L>& C) {
    assert(IsValid(C));
    os<<L<<"\t"<<C.motifValue;
    return os;
  }

  template <LatticeShapeName LS, unsigned int D, unsigned int L>
  InputBase& operator>>(InputBase& is, LatticeMotifChain<LS,D,L>& C) {
    assert(IsValid(C));
    unsigned int Length;
    is>>Length;
    if(Length!=L) Error("The Length in Data does not match Chain!");
    is>>C.motifValue;
    return is;
  }

}

#endif

