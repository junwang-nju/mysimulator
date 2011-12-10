
#ifndef _Lattice_Enum_Method_Square2D_ProhibitSite_ImportLib_Specification_H_
#define _Lattice_Enum_Method_Square2D_ProhibitSite_ImportLib_Specification_H_

#include "lattice/enumerate/method/square/2d/prohibit-site/specification.h"
#include "lattice/enumerate/method/base/import-lib.h"

namespace mysimulator {

  void importLibrary(
      LatticeEnumMethod<SquareLattice,2U,LatticeEnumProhibitSite>& M,
      const LatticeLibrary<SquareLattice,2U>& Lib) {
    typedef LatticeEnumMethodBase<SquareLattice,2U>   Type;
    importLib(static_cast<Type&>(M),Lib);
  }

}

#include "lattice/enumerate/method/base/import-lib.h"

namespace mysimulator {

  void importLibrary(
      LatticeEnumMethod<SquareLattice,2U,LatticeEnumProhibitSite>& M) {
    typedef LatticeEnumMethodBase<SquareLattice,2U>   Type;
    allocate(static_cast<Type&>(M));
  }

}

#endif

