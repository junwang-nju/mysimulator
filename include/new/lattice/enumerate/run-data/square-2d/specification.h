
#ifndef _Lattice_Enumerate_RunData_Square2D_Specification_H_
#define _Lattice_Enumerate_RunData_Square2D_Specification_H_

#include "lattice/enumerate/run-data/interface.h"
#include "lattice/motif-chain/interface.h"

namespace mysimulator {

  template <unsigned int Len>
  struct LatticeEumRunData<SquareLattice,2U,Len> {

    public:

      typedef LatticeEumRunData<SquareLattice,2U,Len>   Type;

      Array1D<bool> Mesh;
      LatticeMotifChain<SquareLattice,2U,Len> C;
      Array1D<typename LatticeCoordinate<SquareLattice,2U>::Type> HeadPos;
      Array1D<unsigned int> NowRegion;
      int RunRegion;

      LatticeEumRunData() : Mesh(),C(),HeadPos(),NowRegion(),RunRegion(-1) {}
      ~LatticeEumRunData() { clearData(); }

      void clearData() {
        release(Mesh); release(C); release(HeadPos); release(NowRegion);
        RunRegion=-1;
      }
      bool isvalid() const {
        return IsValid(Mesh)&&IsValid(C)&&IsValid(HeadPos)&&
               IsValid(NowRegion)&&(RunRegion>0);
      }

    private:
      LatticeEumRunData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <unsigned int Len>
  bool IsValid(const LatticeEumRunData<SquareLattice,2U,Len>& D) {
    return D.isvalid();
  }

  template <unsigned int Len>
  void release(LatticeEumRunData<SquareLattice,2U,Len>& D) { D.clearData(); }

}

#endif

