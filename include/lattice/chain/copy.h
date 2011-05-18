
#ifndef _Lattice_Chain_Copy_H_
#define _Lattice_Chain_Copy_H_

#include "lattice/chain/interface.h"

namespace mysimulator {

  template <LatticeTypeName LT, unsigned int Dim>
  void copy(LatticeChain<LT,Dim>& C, const LatticeChain<LT,Dim>& cC) {
    assert(IsValid(C));
    assert(IsValid(cC));
    typedef Vector<unsigned short>  VType;
    copy(static_cast<VType&>(C),static_cast<const VType&>(cC));
    copy(C.property,cC.property);
  }

}

#endif

