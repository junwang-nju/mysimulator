
#ifndef _Lattice_Chain_Get_H_
#define _Lattice_Chain_Get_H_

#include "lattice/chain/interface.h"
#include "lattice/library/bond/interface.h"

namespace mysimulator {

  template <LatticeTypeName LT, unsigned int Dim>
  unsigned int getBond(const LatticeChain<LT,Dim>& C, const unsigned int n) {
    assert(IsValid(C));
    assert(LatticeBondLib<LT,Dim>::MaxMotifs>0);
    unsigned int u=LatticeBondLib<LT,Dim>::MaxMotifs;
    unsigned int I=n/u;
    unsigned int J=n%u;
    unsigned int NB=(I==C.Length()-1?C.NumMotifs():u);
    unsigned int motif=C[I];
    return RunBondLibrary<LT,Dim>().map[NB][motif][J];
  }

}

#endif

