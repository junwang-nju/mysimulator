
#ifndef _Lattice_Enumerate_Square2D_Check_Basic_Interface_H_
#define _Lattice_Enumerate_Square2D_Check_Basic_Interface_H_

#include "lattice/enumerate/square-2d/check/base/interface.h"

namespace mysimulator {

  template <unsigned int L>
  struct LatticeEnumSquare2DCheckBasic
      : public LatticeEnumSquare2DCheckBase<L> {

    typedef LatticeEnumSquare2DCheckBasic<L>  Type;
    typedef LatticeEnumSquare2DCheckBase<L>   ParentType;

    LatticeEnumSquare2DCheckBasic() {
      Error("Default Initiator of LatticeEnumSquare2DCheckBasic Disabled!");
    }
    LatticeEnumSquare2DCheckBasic(
        const List<int>& mesh, const List<int>& loc,
        const LatticeMotifChain<SquareLattice,2,L>& c,
        const Vector<unsigned int>& len, const Vector<unsigned short>& bH,
        const Vector<int>& state) : ParentType(mesh,loc,c,len,bH,state) {}
    LatticeEnumSquare2DCheckBasic(const Type&) {
      Error("Copier of LatticeEnumSquare2DCheckBasic Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeEnumSquare2DCheckBasic Disabled!");
      return *this;
    }
    ~LatticeEnumSquare2DCheckBasic() { clearData(); }

    void clearData() { static_cast<ParentType*>(this)->clearData(); }
    virtual bool act() { return true; }

  };

  template <unsigned int L>
  bool IsValid(const LatticeEnumSquare2DCheckBasic<L>& Ck) {
    return IsValid(static_cast<const LatticeEnumSquare2DCheckBase<L>&>(Ck));
  }

  template <unsigned int L>
  void release(LatticeEnumSquare2DCheckBasic<L>& Ck) { Ck.clearData(); }

}

#endif

