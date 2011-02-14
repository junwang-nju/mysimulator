
#ifndef _Lattice_Chain_Input_Output_H_
#define _Lattice_Chain_Input_Output_H_

#include "operation/basic/vector-io.h"

namespace std {

  OutputBase& operator<<(OutputBase& os,
                         const LatticeChain<SquareLattice,2>& LC) {
    os<<static_cast<const Vector<unsigned short int>&>(LC);
    return os;
  }


}

#endif

