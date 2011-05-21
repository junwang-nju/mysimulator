
#ifndef _Lattice_Enumerate_Square2D_Check_Basic_Specification_H_
#define _Lattice_Enumerate_Square2D_Check_Basic_Specification_H_

#include "lattice/enumerate/square-2d/check/interface.h"
#include "lattice/enumerate/square-2d/check/basic/interface.h"

namespace mysimulator {

  template <unsigned int L>
  struct LatticeEnumSquare2DCheck<L,LatticeEnumSquare2DCheckMethodBasic>
      : public LatticeEnumSquare2DCheckBasic<L> {

    typedef LatticeEnumSquare2DCheck<L,LatticeEnumSquare2DCheckMethodBasic>
            Type;
    typedef LatticeEnumSquare2DCheckBasic<L>  ParentType;

    LatticeEnumSquare2DCheck() {
      Error("Default Initiator of LatticeEnumSquare2DCheck Disabled!");
    }
    LatticeEnumSquare2DCheck(const LatticeEnumSquare2DRunData<L>& D)
      : ParentType(D) {}

    LatticeEnumSquare2DCheck(const Type&) {
      Error("Copier of LatticeEnumSquare2DCheck Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeEnumSquare2DCheck Disabled!");
      return *this;
    }
    ~LatticeEnumSquare2DCheck() { clearData(); }

    void clearData() { static_cast<ParentType*>(this)->clearData(); }

  };

  template <unsigned int L>
  bool IsValid(
      const LatticeEnumSquare2DCheck<L,LatticeEnumSquare2DCheckMethodBasic>& C){
    return IsValid(static_cast<const LatticeEnumSquare2DCheckBasic<L>&>(C));
  }

}

#endif

