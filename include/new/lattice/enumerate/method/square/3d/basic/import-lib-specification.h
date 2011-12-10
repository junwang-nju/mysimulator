
#ifndef _Lattice_Enum_Method_Square3D_Basic_ImportLib_Specification_H_
#define _Lattice_Enum_Method_Square3D_Basic_ImportLib_Specification_H_

#include "lattice/enumerate/method/square/3d/basic/specification.h"
#include "lattice/enumerate/method/base/import-lib.h"

namespace mysimulator {

  void importLibrary(LatticeEnumMethod<SquareLattice,3U,LatticeEnumBasic>& M,
                     const LatticeLibrary<SquareLattice,3U>& Lib) {
    typedef LatticeEnumMethodBase<SquareLattice,3U> Type;
    importLib(static_cast<Type&>(M),Lib);
  }

}

#include "lattice/enumerate/method/base/allocate.h"

namespace mysimulator {

  void importLibrary(LatticeEnumMethod<SquareLattice,3U,LatticeEnumBasic>& M) {
    typedef LatticeEnumMethodBase<SquareLattice,3U> Type;
    allocate(static_cast<Type&>(M));
  }

}

#endif

