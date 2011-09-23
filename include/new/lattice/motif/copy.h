
#ifndef _Lattice_Motif_Copy_H_
#define _Lattice_Motif_Copy_H_

#include "lattice/motif/interface.h"
#include "array/1d/copy.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void copy(LatticeMotif<LSN,Dim>& M, const LatticeMotif<LSN,Dim>& cM) {
    assert(IsValid(M)&&IsValid(cM));
    copy(M.bond,cM.bond);
    copy(M.coordinate,cM.coordinate);
  }

}

#endif
