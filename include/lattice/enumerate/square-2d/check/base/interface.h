
#ifndef _Lattice_Enumerate_Square2D_Check_Base_Interface_H_
#define _Lattice_Enumerate_Square2D_Check_Base_Interface_H_

#include "lattice/enumerate/square-2d/check/method-name.h"
#include "lattice/enumerate/square-2d/run-data/interface.h"

namespace mysimulator {

  template <unsigned int L>
  struct LatticeEnumSquare2DCheckBase{

    typedef LatticeEnumSquare2DCheckBase<L>   Type;

    Object<LatticeEnumSquare2DRunData<L> > Data;

    LatticeEnumSquare2DCheckBase() {
      Error("Default Initiator of LatticeEnumSquare2DCheckBase Disabled!");
    }
    LatticeEnumSquare2DCheckBase(const LatticeEnumSquare2DRunData<L>& D) {
      refer(Data,D);
    }
    LatticeEnumSquare2DCheckBase(const Type&) {
      Error("Copier of LatticeEnumSquare2DCheckBase Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator for LatticeEnumSquare2DCheckBase Disabled!");
      return *this;
    }
    ~LatticeEnumSquare2DCheckBase() { clearData(); }

    void clearData() { release(Data); }

    virtual bool Act()=0;

  };

  template <unsigned int L>
  bool IsValid(const LatticeEnumSquare2DCheckBase<L>& C) {
    return IsValid(C.Data);
  }

  template <unsigned int L>
  void release(LatticeEnumSquare2DCheckBase<L>& C) { C.clearData(); }

}

#endif

