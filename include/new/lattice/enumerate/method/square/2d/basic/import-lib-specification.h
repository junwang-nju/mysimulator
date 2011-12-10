
#ifndef _Lattice_Enumerate_Method_Square2D_Basic_ImportLib_Specification_H_
#define _Lattice_Enumerate_Method_Square2D_Basic_ImportLib_Specification_H_

#include "lattice/enumerate/method/square/2d/basic/specification.h"
#include "lattice/enumerate/method/base/import-lib.h"

namespace mysimulator {

  void importLibrary(LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic>& M,
                     const LatticeLibrary<SquareLattice,2U>& Lib) {
    typedef LatticeEnumMethodBase<SquareLattice,2U> Type;
    importLib(static_cast<Type&>(M),Lib);
  }

}

#include "lattice/enumerate/method/base/allocate.h"

namespace mysimulator {

  void importLibrary(LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic>& M) {
    typedef LatticeEnumMethodBase<SquareLattice,2U> Type;
    allocate(static_cast<Type&>(M));
  }

}

#endif

