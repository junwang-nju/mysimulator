
#ifndef _Lattice_Enumerate_Square2D_Check_Basic_Specification_H_
#define _Lattice_Enumerate_Square2D_Check_Basic_Specification_H_

#include "lattice/enumerate/square-2d/check/interface.h"

namespace mysimulator {

  template <>
  struct LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic> {

    typedef LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic>
            Type;

    LatticeEnumSquare2DCheck() {}
    LatticeEnumSquare2DCheck(const Type&) {
      Error("Copier of LatticeEnumSquare2DCheck Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeEnumSquare2DCheck Disabled!");
      return *this;
    }
    ~LatticeEnumSquare2DCheck() { clearData(); }

    void clearData() {}

    template <unsigned int L>
    bool Act(LatticeEnumSquare2DRunData<L>&) { return true; }

  };

  bool IsValid(
      const LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic>&) {
    return true;
  }

  void release(
      LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic>& C) {
    C.clearData();
  }

}

#endif

