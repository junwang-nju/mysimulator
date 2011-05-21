
#ifndef _Lattice_Enumerate_Square2D_Check_Basic_Copy_Specification_H_
#define _Lattice_Enumerate_Square2D_Check_Basic_Copy_Specification_H_

#include "lattice/enumerate/square-2d/check/interface.h"

namespace mysimulator {

  void copy(LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic>& C,
            const
            LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic>& cC){
    assert(IsValid(C)&&IsValid(cC));
  } 

}

#endif

