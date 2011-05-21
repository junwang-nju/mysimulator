
#ifndef _Lattice_Enumerate_Square2D_RunData_Interface_H_
#define _Lattice_Enumerate_Square2D_RunData_Interface_H_

#include "list/interface.h"
#include "lattice/motif-chain/interface.h"

namespace mysimulator {

  template <unsigned int L>
  struct LatticeEnumSquare2DRunData {

    typedef LatticeEnumSquare2DRunData<L> Type;

    List<int> Mesh;
    List<int> Loc;
    LatticeMotifChain<SquareLattice,2,L>  C;
    Vector<unsigned int> Len;
    Vector<unsigned short> bHigh;
    int B,Bs,BsL,BsH,Bc;

    LatticeEnumSquare2DRunData()
      : Mesh(),Loc(),C(),Len(),bHigh(),B(-1),Bs(-1),BsL(-1),BsH(-1),Bc(-1) {}
    LatticeEnumSquare2DRunData(const Type&) {
      Error("Copier of LatticeEnumSquare2DRunData Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeEnumSquare2DRunData Disabled!");
      return *this;
    }
    ~LatticeEnumSquare2DRunData() { clearData(); }

    void clearData() {
      release(Mesh); release(Loc); release(C); release(Len); release(bHigh);
    }

  };

  template <unsigned int L>
  bool IsValid(const LatticeEnumSquare2DRunData<L>& D) {
    return IsValid(D.Mesh)&&IsValid(D.Loc)&&IsValid(D.C)&&
           IsValid(D.Len)&&IsValid(D.bHigh);
  }

  template <unsigned int L>
  void release(LatticeEnumSquare2DRunData<L>& D) { D.clearData(); }

}

#endif

