
#ifndef _Lattice_Enumerate_Square2D_RunData_Interface_H_
#define _Lattice_Enumerate_Square2D_RunData_Interface_H_

#include "lattice/motif-chain/interface.h"

namespace mysimulator {

  template <unsigned int Len>
  struct LatticeSquare2DEnumRunData {

    public:

      typedef LatticeSquare2DEnumRunData<Len> Type;

      Array1D<int> Mesh;
      LatticeMotifChain<SquareLattice,2U,Len> C;
      Array1D<typename LatticeCoordinate<SquareLattice,2U>::Type> TLoc;

      LatticeSquare2DEnumRunData() : Mesh(), C(), TLoc() {}
      ~LatticeSquare2DEnumRunData() { clearData(); }

      void clearData() { release(Mesh); release(C); release(TLoc); }
      bool isvalid() const { return IsValid(Mesh)&&IsValid(C)&&IsValid(TLoc); }

    private:

      LatticeSquare2DEnumRunData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <unsigned int Len>
  bool IsValid(const LatticeSquare2DEnumRunData<Len>& D) { return D.isvalid(); }

  template <unsigned int Len>
  void release(LatticeSquare2DEnumRunData<Len>& D) { D.clearData(); }

}

#endif

