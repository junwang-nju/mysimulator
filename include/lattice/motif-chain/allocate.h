
#ifndef _Lattice_Motif_Chain_Allocate_H_
#define _Lattice_Motif_Chain_Allocate_H_

#include "lattice/motif-chain/interface.h"

namespace mysimulator {

  template <LatticeShapeName LS, unsigned int Dim>
  void allocate(LatticeMotifChain<LS,Dim>& C, const unsigned int n) {
    assert(n>1);
    release(C);
    unsigned int u=(n-2)/LatticeLibrary<LS,Dim>::MaxBondOfMotif+1;
    allocate(C.motifID,u);
    allocate(C.property,LatMotifChainNumberProperty);
    C.Length()=n;
    C.NumBondsInLastMotif()=(n-2)%LatticeLibrary<LS,Dim>::MaxBondOfMotif+1;
  }

}

#endif

