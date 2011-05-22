
#ifndef _Lattice_Enumerate_Square2D_Check_Allocate_H_
#define _Lattice_Enumerate_Square2D_Check_Allocate_H_

#include "lattice/enumerate/square-2d/check/interface.h"

namespace mysimulator {

  template <LatticeEnumSquare2DCheckMethodName Method>
  void allocate(LatticeEnumSquare2DCheck<Method>& C) {
    Error("Allocate for LatticeEnumSquare2DCheck of this Method Disabled!");
  }

}

#include "lattice/enumerate/square-2d/check/basic/allocate-specification.h"
#include "lattice/enumerate/square-2d/check/fix-bonds/allocate-specification.h"

#endif

