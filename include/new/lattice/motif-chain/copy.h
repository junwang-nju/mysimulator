
#ifndef _Lattice_MotifChain_Copy_H_
#define _Lattice_MotifChain_Copy_H_

#include "lattice/motif-chain/interface.h"
#include "array/1d/copy.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  void copy(LatticeMotifChain<LSN,Dim,Len>& C,
            const LatticeMotifChain<LSN,Dim,Len>& mC) {
    copy(C.SegMotif,mC,SegMotif);
  }

}

#endif

