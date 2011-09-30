
#ifndef _Lattice_Enumerate_Check_Basic_Allocate_H_
#define _Lattice_Enumerate_Check_Basic_Allocate_H_

#include "lattice/enumerate/check/basic/specification.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void allocate(LatticeEnumCheck<LSN,Dim,LatticeEnumCheckMethodBasic>& C) {
    typedef LatticeEnumCheckBase<LSN,Dim,LatticeEnumCheckMethodBasic>
            Type;
    allocate(static_cast<Type&>(D));
  }

}

#endif

