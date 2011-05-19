
#ifndef _Lattice_Motif_Chain_InputOutput_H_
#define _Lattice_Motif_Chain_InputOutput_H_

#include "lattice/motif-chain/interface.h"
#include "io/output/interface.h"

namespace mysimulator {

  template <LatticeShapeName LS, unsigned int Dim>
  OutputBase& operator<<(OutputBase& os, const LatticeMotifChain<LS,Dim>& C) {
    os<<C.Length()<<"\t"<<C.motifID;
    return os;
  }

}

#endif

