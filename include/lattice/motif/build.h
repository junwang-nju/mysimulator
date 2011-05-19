
#ifndef _Lattice_Motif_Build_H_
#define _Lattice_Motif_Build_H_

#include "lattice/motif/interface.h"
#include "lattice/shape-name.h"

namespace mysimulator {

  template <LatticeShapeName LShape, unsigned int Dim>
  void build(LatticeMotif& M) { Error ("This Motif Cannot be Build!"); }

  template <>
  void build<SquareLattice,2>(LatticeMotif& M) {
    assert(M.Dimension()==2);
    static int x,y;
    x=y=0;
    for(unsigned int i=0;i<M.bond.size;++i) {
      switch(M.bond[i]) {
        case 0: ++x;  break;
        case 1: ++y;  break;
        case 2: --y;  break;
        case 3: --x;  break;
        default: Error("Unknown Bond for Motif Build!");
      }
      M.coordinate[i][0]=x;
      M.coordinate[i][1]=x;
    }
  }

}

#endif

