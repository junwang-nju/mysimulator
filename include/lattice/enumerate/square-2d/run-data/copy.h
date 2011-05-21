
#ifndef _Lattice_Enumerate_Square2D_RunData_Copy_H_
#define _Lattice_Enumerate_Square2D_RunData_Copy_H_

#include "lattice/enumerate/square-2d/run-data/interface.h"

namespace mysimulator {

  template <unsigned int L>
  void copy(LatticeEnumSquare2DRunData<L>& D,
            const LatticeEnumSquare2DRunData<L>& cD) {
    assert(IsValid(D)&&IsValid(cD));
    copy(D.Mesh,cD.Mesh);
    copy(D.Loc,cD.Loc);
    copy(D.C,cD.C);
    copy(D.Len,cD.Len);
    copy(D.bHigh,cD.bHigh);
    D.B=cD.B;
    D.Bs=cD.Bs;
    D.BsL=cD.BsL;
    D.BsH=cD.BsH;
    D.Bc=cD.Bc;
  }

}

#endif

