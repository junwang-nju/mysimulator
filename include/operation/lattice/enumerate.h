
#ifndef _Lattice_Enumerate_H_
#define _Lattice_Enumerate_H_

#include "operation/lattice/chain-op.h"

namespace std {

  template <unsigned int LT, unsigned int LD>
  void enumerate(const unsigned int N, istream& is) {
    myError("This Lattice Cannot be enumerated");
  }

  template <>
  void enumerate<SquareLattice,2>(const unsigned int N, istream& is) {
    PropertyList<int> Mesh;
    Vector<unsigned int> sz(N+N-1);
    copy(sz,N+N-1);
    allocate(Mesh,sz);
    LatticeChain<SquareLattice,2> LC;
    allocate(LC,N);
    PropertyList<int> R;
    allocate(sz,N);
    copy(sz,2);
    allocate(R,sz);
  }

}

#endif

