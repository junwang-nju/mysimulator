
#ifndef _Lattice_Enumerate_RunData_Square2D_Specification_H_
#define _Lattice_Enumerate_RunData_Square2D_Specification_H_

#include "lattice/enumerate/run-data/interface.h"
#include "lattice/motif-chain/interface.h"

namespace mysimulator {

  template <unsigned int Len>
  struct LatticeEnumRunData<SquareLattice,2U,Len> {

    public:

      typedef LatticeEnumRunData<SquareLattice,2U,Len>   Type;

      Array1D<bool> Mesh;
      LatticeMotifChain<SquareLattice,2U,Len> C;
      Array1D<typename LatticeCoordinate<SquareLattice,2U>::Type> Pos;
      Array1D<unsigned int> RunRegion;
      Array1D<unsigned int> MotifPosHead, MotifPosTail;
      int RunMotifLoc;
      Array1D<int> RunMotifSeg;
      Array1D<unsigned int> RunMotifSegMax;
      Array1D<unsigned short int> RunMotifSegHead,RunMotifSegTail;

      LatticeEnumRunData()
        : Mesh(),C(),Pos(), RunRegion(), MotifPosHead(),MotifPosTail(),
          RunMotifLoc(-1), RunMotifSeg(), RunMotifSegMax(),
          RunMotifSegHead(),RunMotifSegTail() {}
      ~LatticeEnumRunData() { clearData(); }

      void clearData() {
        release(Mesh); release(C); release(Pos);  release(RunRegion);
        release(MotifPosHead);  release(MotifPosTail);
        RunMotifLoc=-1;
        release(RunMotifSeg); release(RunMotifSegMax);
        release(RunMotifSegHead); release(RunMotifSegTail);
      }
      bool isvalid() const {
        return IsValid(Mesh)&&IsValid(C)&&IsValid(Pos)&&IsValid(RunRegion)&&
               IsValid(MotifPosHead)&&IsValid(MotifPosTail)&&
               IsValid(RunMotifSeg)&&IsValid(RunMotifSegMax)&&
               IsValid(RunMotifSegHead)&&IsValid(RunMotifSegTail);
      }

    private:
      LatticeEnumRunData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <unsigned int Len>
  bool IsValid(const LatticeEnumRunData<SquareLattice,2U,Len>& D) {
    return D.isvalid();
  }

  template <unsigned int Len>
  void release(LatticeEnumRunData<SquareLattice,2U,Len>& D) { D.clearData(); }

}

#endif

