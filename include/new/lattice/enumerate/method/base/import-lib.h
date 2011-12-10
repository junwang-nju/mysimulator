
#ifndef _Lattice_Enumerate_Method_Base_ImportLib_H_
#define _Lattice_Enumerate_Method_Base_ImportLib_H_

#include "lattice/enumerate/method/base/interface.h"
#include "object/refer.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void importLib(LatticeEnumMethodBase<LSN,Dim>& M,
                 const LatticeLibrary<LSN,Dim>& Lib) {
    if(!IsValid(M)) allocate(M.Lib);
    refer(M.Lib,Lib);
    M.Lib().load();
  }

}

#endif

