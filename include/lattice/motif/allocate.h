
#ifndef _Lattice_Motif_Allocate_H_
#define _Lattice_Motif_Allocate_H_

#include "lattice/motif/interface.h"
#include "list/allocate.h"
#include "vector/fill.h"

namespace mysimulator {

  void allocate(LatticeMotif& M, const unsigned int n, const unsigned int d) {
    allocate(M.bond,n);
    fill(M.bond,d);
    allocate(M.coordinate,M.bond);
    fill(M.bond,0U);
  }

}

#endif

