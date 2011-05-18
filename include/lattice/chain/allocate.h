
#ifndef _Lattice_Chain_Allocate_H_
#define _Lattice_Chain_Allocate_H_

#include "lattice/chain/interface.h"
#include "lattice/library/bond/interface.h"

namespace mysimulator {

  template <LatticeTypeName LT, unsigned int Dim>
  void allocate(LatticeChain<LT,Dim>& C, const unsigned int n) {
    assert(n>1);
    if(LatticeBondLib<LT,Dim>::MaxMotifs)
      Error("Proper Lattice Library Interface is not Included!");
    unsigned int u=(n-2)/LatticeBondLib<LT,Dim>::MaxMotifs+1;
    allocate(static_cast<Vector<unsigned short>&>(C),u);
    allocate(C.property,LatticeChainNumberProperty);
    C.Length()=n;
    C.NumberMotifs()=u;
  }

}

#endif

