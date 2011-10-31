
#ifndef _Lattice_Enumerate_Method_Square2D_Basic_Specification_H_
#define _Lattice_Enumerate_Method_Square2D_Basic_Specification_H_

#include "lattice/enumerate/method/interface.h"
#include "array/1d/content/interface.h"

namespace mysimulator {

  template <>
  struct LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic> {

    public:

      typedef LatticeEnumMethod<SquareLattice,2U,LatticeEnumBasic>  Type;

      LatticeEnumMethod() {}
      ~LatticeEnumMethod() { clearData(); }

      void clearData() {}
      bool isvalid() const { return true; }

      bool Check(const Array1DContent<int>& Branch, const Array1DContent<int>

  };

}

#endif

