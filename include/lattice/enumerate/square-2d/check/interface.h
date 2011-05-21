
#ifndef _Lattice_Enumerate_Square2D_Check_Interface_H_
#define _Lattice_Enumerate_Square2D_Check_Interface_H_

#include "lattice/enumerate/square-2d/check/method-name.h"
#include "list/interface.h"
#include "lattice/motif-chain/interface.h"

namespace mysimulator {

  template <unsigned int L, LatticeEnumSquare2DCheckMethodName Method>
  struct LatticeEnumSquare2DCheck {

    typedef LatticeEnumSquare2DCheck<L,Method>  Type;

    LatticeEnumSquare2DCheck() {
      Error("This Method of LatticeEnumSquare2DCheck Disabled!");
    }
    LatticeEnumSquare2DCheck(
        const List<int>& mesh, const List<int>& loc,
        const LatticeMotifChain<SquareLattice,2,L>& c,
        const Vector<unsigned int>& len, const Vector<unsigned short>& bH,
        const Vector<int>& state) {
      Error("This Method of LatticeEnumSquare2DCheck Disabled!");
    }
    LatticeEnumSquare2DCheck(const Type&) {
      Error("This Method of LatticeEnumSquare2DCheck Disabled!");
    }
    Type& operator=(const Type&) {
      Error("This Method of LatticeEnumSquare2DCheck Disabled!");
      return *this;
    }
    ~LatticeEnumSquare2DCheck() {}

    void clearData() {}

  };

  template <unsigned int L, LatticeEnumSquare2DCheckMethodName M>
  bool IsValid(const LatticeEnumSquare2DCheck<L,M>&) { return false; }

  template <unsigned int L, LatticeEnumSquare2DCheckMethodName M>
  void release(LatticeEnumSquare2DCheck<L,M>& Ck) { Ck.clearData(); }

}

#include "lattice/enumerate/square-2d/check/basic/specification.h"

#endif

