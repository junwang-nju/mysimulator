
#ifndef _Lattice_Enumerate_Square2D_Check_Copy_H_
#define _Lattice_Enumerate_Square2D_Check_Copy_H_

#include "lattice/enumerate/square-2d/check/interface.h"

namespace mysimulator {

  template <unsigned int L, LatticeEnumSquare2DCheckMethodName Method>
  void copy(LatticeEnumSquare2DCheck<L,Method>& Ck,
            const LatticeEnumSquare2DCheck<L,Method>& cCk) {
    assert(IsValid(Ck)&&IsValid(cCk));
  }

}

#include "lattice/enumerate/square-2d/check/basic/copy-specification.h"

#endif

