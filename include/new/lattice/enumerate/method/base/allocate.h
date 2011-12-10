
#ifndef _Lattice_Enumerate_Method_Base_Allocate_H_
#define _Lattice_Enumerate_Method_Base_Allocate_H_

#include "lattice/enumerate/method/base/interface.h"
#include "object/allocate.h"

namespace mysimulator  {

  template <LatticeShapeName LSN, unsigned int Dim>
  void allocate(LatticeEnumMethodBase<LSN,Dim>& M) {
    release(M);
    allocate(M.Lib);
    M.Lib().load();
  }

}

#endif

