
#ifndef _Lattice_Enumerate_Square2D_Check_FixBonds_Copy_Specification_H_
#define _Lattice_Enumerate_Square2D_Check_FixBonds_Copy_Specification_H_

#include "lattice/enumerate/square-2d/check/interface.h"
#include "list/copy.h"

namespace mysimulator {

  void copy(
      LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds>& C,
      const LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodFixBonds>&
            cC) {
    assert(IsValid(C)&&IsValid(cC));
    copy(C.flag,cC.flag);
    copy(C.fixedBond,cC.fixedBond);
  }

}

#endif

