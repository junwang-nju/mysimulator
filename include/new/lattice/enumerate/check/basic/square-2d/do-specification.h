
#ifndef _Lattice_Enumerate_Check_Basic_Square2D_Do_Specification_H_
#define _Lattice_Enumerate_Check_Basic_Square2D_Do_Specification_H_

#include "lattice/enumerate/check/basic/specification.h"

namespace mysimulator {

  template <unsigned int Len>
  bool
  LatticeEnumCheck<SquareLattice,2U,LatticeEnumCheckMethodBasic>::operator()(
      LatticeEnumRunData<SquareLattice,2U,Len>& D) {
    if(D.RunMotifLoc>=0) {
    }
    return true;
  }

}

#endif

