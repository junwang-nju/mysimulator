
#ifndef _Lattice_Chain_InputOutput_H_
#define _Lattice_Chain_InputOutput_H_

#include "lattice/chain/interface.h"
#include "io/output/interface.h"

namespace mysimulator {

  template <LatticeTypeName LT, unsigned int Dim>
  OutputBase& operator<<(OutputBase& os, LatticeChain<LT,Dim>& C) {
    os<<static_cast<const Vector<unsigned short>&>(C);
    return os;
  }

}

#endif

