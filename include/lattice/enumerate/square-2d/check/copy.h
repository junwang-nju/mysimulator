
#ifndef _Lattice_Enumerate_Square2D_Check_Copy_H_
#define _Lattice_Enumerate_Square2D_Check_Copy_H_

#include "lattice/enumerate/square-2d/check/interface.h"

namespace mysimulator {

  template <LatticeEnumSquare2DCheckMethodName Method>
  void copy(LatticeEnumSquare2DCheck<Method>& C,
            const LatticeEnumSquare2DCheck<Method>& cC) {
    Error("Copy for LatticeEnumSquare2DCheck of this Method Disabled!");
  }

}

#include "lattice/enumerate/square-2d/check/basic/copy-specification.h"

#endif

