
#ifndef _Lattice_Motif_Allocate_H_
#define _Lattice_Motif_Allocate_H_

#include "lattice/motif/interface.h"
#include "list/allocate.h"
#include "vector/fill.h"

namespace mysimulator {

  void allocate(LatticeMotif& M, const unsigned int n, const unsigned int d) {
    release(M);
    allocate(M.bond,n);
    fill(M.bond,d);
    allocate(M.coordinate,M.bond);
    fill(M.bond,0U);
  }

  void imprint(LatticeMotif& M, const LatticeMotif& cM) {
    assert(IsValid(cM));
    release(M);
    imprint(M.bond,cM.bond);
    imprint(M.coordinate,cM.coordinate);
  }

}

#endif

