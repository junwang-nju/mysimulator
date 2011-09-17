
#ifndef _Lattice_Motif_Copy_H_
#define _Lattice_Motif_Copy_H_

#include "lattice/motif/interface.h"

namespace mysimulator {

  void copy(LatticeMotif& M, const LatticeMotif& cM) {
    assert(IsValid(M)&&IsValid(cM));
    assert(M.name==cM.name);
    copy(M.bond,cM.bond);
    copy(M.coordinate,cM.coordinate);
  }

}

#endif
