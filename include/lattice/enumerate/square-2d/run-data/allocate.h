
#ifndef _Lattice_Enumerate_Square2D_RunData_Allocate_H_
#define _Lattice_Enumerate_Square2D_RunData_Allocate_H_

#include "lattice/enumerate/square-2d/run-data/interface.h"
#include "list/allocate.h"
#include "list/fill.h"

namespace mysimulator {

  template <unsigned int L>
  void allocate(LatticeEnumSquare2DRunData<L>& D) {
    release(D);
    Vector<unsigned int> sz;
    allocate(sz,L+L-1);
    fill(sz,L+L-1);
    allocate(D.Mesh,sz);
    fill(D.Mesh,-1);
    allocate(sz,L);
    fill(sz,2U);
    allocate(D.Loc,sz);
    fill(D.Loc[0],static_cast<int>(L-1));
    D.Mesh[L-1][L-1]=0;
    allocate(D.C);
    allocate(D.Len,LatticeMotifChain<SquareLattice,2,L>::NumMotifs);
    fill(D.Len,LatticeLibrary<SquareLattice,2>::MaxBondOfMotif);
    D.Len[D.Len.size-1]=
      LatticeMotifChain<SquareLattice,2,L>::NumBondsLastMotif;
    allocate(D.bHigh,LatticeMotifChain<SquareLattice,2,L>::NumMotifs);
    D.B=0;
    D.Bs=0;
    D.BsL=1;
    D.BsH=D.BsL+D.Len[0];
    D.Bc=-1;
    D.C.motifValue[0]=0;
    D.bHigh[0]=LatticeLibrary<SquareLattice,2>::shiftLoc[D.Len[0]-1][0];
  }

  template <unsigned int L>
  void imprint(LatticeEnumSquare2DRunData<L>& D,
               const LatticeEnumSquare2DRunData<L>& cD) { allocate(D); }

}

#endif

