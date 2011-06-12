
#ifndef _Lattice_Enumerate_Square2D_Check_FixBonds_Allocate_Specification_H_
#define _Lattice_Enumerate_Square2D_Check_FixBonds_Allocate_Specification_H_

#include "lattice/enumerate/square-2d/check/interface.h"
#include "list/allocate.h"
#include "vector/fill.h"

namespace mysimulator {

  void allocate(
      LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds>& C,
      const unsigned int nbond) {
    release(C);
    Vector<unsigned int> sz(nbond);
    fill(sz,2U);
    allocate(C.fixedBond,sz);
  }

  void imprint(
      LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds>& C,
      const LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds>&
      cC) {
    assert(IsValid(cC));
    allocate(C,cC.fixedBond.ListSize());
  }

}

#endif

