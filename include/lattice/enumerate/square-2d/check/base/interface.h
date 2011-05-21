
#ifndef _Lattice_Enumerate_Square2D_Check_Base_Interface_H_
#define _Lattice_Enumerate_Square2D_Check_Base_Interface_H_

#include "referable-object/refer.h"
#include "lattice/motif-chain/interface.h"
#include "lattice/enumerate/square-2d/check/method-name.h"

namespace mysimulator {

  template <unsigned int L>
  struct LatticeEnumSquare2DCheckBase{

    typedef LatticeEnumSquare2DCheckBase<L>   Type;

    Object<List<int> > Mesh;
    Object<List<int> > Loc;
    Object<LatticeMotifChain<SquareLattice,2,L> > C;
    Object<Vector<unsigned int> > Len;
    Object<Vector<unsigned short> > boundHigh;
    Object<Vector<int> >  State;

    LatticeEnumSquare2DCheckBase() {
      Error("Default Initiator of LatticeEnumSquare2DCheckBase Disabled!");
    }
    LatticeEnumSquare2DCheckBase(
        const List<int>& mesh, const List<int>& loc,
        const LatticeMotifChain<SquareLattice,2,L>& c,
        const Vector<unsigned int>& len, const Vector<unsigned short>& bH,
        const Vector<int>& state) {
      refer(Mesh,mesh);
      refer(Loc,loc);
      refer(C,c);
      refer(Len,len);
      refer(boundHigh,bH);
      refer(State,state);
    }
    LatticeEnumSquare2DCheckBase(const Type&) {
      Error("Copier of LatticeEnumSquare2DCheckBase Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator for LatticeEnumSquare2DCheckBase Disabled!");
      return *this;
    }
    ~LatticeEnumSquare2DCheckBase() { clearData(); }

    void clearData() {
      release(Mesh);
      release(Loc);
      release(C);
      release(Len);
      release(boundHigh);
      release(State);
    }

    virtual bool Act()=0;

  };

  template <unsigned int L>
  bool IsValid(const LatticeEnumSquare2DCheckBase<L>& C) {
    return IsValid(C.Mesh)&&IsValid(C.Loc)&&IsValid(C.C)&&
           IsValid(C.Len)&&IsValid(C.boundHigh)&&IsValid(C.State);
  }

  template <unsigned int L>
  void release(LatticeEnumSquare2DCheckBase<L>& C) { C.clearData(); }

}

#endif

