
#ifndef _Lattice_Enumerate_Square2D_Check_Interface_H_
#define _Lattice_Enumerate_Square2D_Check_Interface_H_

#include "lattice/enumerate/square-2d/check/method-name.h"
#include "lattice/enumerate/square-2d/run-data/interface.h"

namespace mysimulator {

  template <LatticeEnumSquare2DCheckMethodName Method>
  struct LatticeEnumSquare2DCheck {

    typedef LatticeEnumSquare2DCheck<Method>  Type;

    LatticeEnumSquare2DCheck() { Error("This Check Disabled!"); }
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
    bool Act(LatticeEnumSquare2DRunData<L>& D) { return false; }

  };

  template <LatticeEnumSquare2DCheckMethodName Method>
  bool IsValid(LatticeEnumSquare2DCheck<Method>& C) { return false; }

  template <LatticeEnumSquare2DCheckMethodName Method>
  void release(LatticeEnumSquare2DCheck<Method>& C) { C.clearData(); }

}

#include "lattice/enumerate/square-2d/check/basic/specification.h"

#endif

