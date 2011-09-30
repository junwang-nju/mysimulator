
#ifndef _Lattice_Enumerate_Check_Base_Allocate_H_
#define _Lattice_Enumerate_Check_Base_Allocate_H_

#include "lattice/enumerate/check/base/interface.h"
#include "io/error.h"

namespace mysimulator {

  template <LatticeShapeName SN,unsigned int D,LatticeEnumCheckMethodName EN>
  void allocate(LatticeEnumCheckBase<SN,D,EN>& C) { C.load(); }

}

#endif

