
#ifndef _Lattice_Chain_Square_2D_H_
#define _Lattice_Chain_Square_2D_H_

#include "data/lattice/chain-base.h"

namespace std {

  template <>
  struct LatticeChain<SquareLattice,2>
    : public LatticeChainBase<SquareLattice,2,4,4> {
    typedef LatticeChain<SquareLattice,2>   Type;
    typedef LatticeChainBase<SquareLattice,2,4,4>   ParentType;
    LatticeChain() : ParentType() {}
    LatticeChain(const Type& LC) { myError("Cannot create Lattice Chain"); }
    Type& operator=(const Type& LC) {
      myError("Cannot copy Lattice Chain");
      return *this;
    }
    ~LatticeChain() { release(*this); }
  };

  bool IsAvailable(const LatticeChain<SquareLattice,2>& LC) {
    return
    IsAvailable(static_cast<const LatticeChainBase<SquareLattice,2,4,4>&>(LC));
  }
  void release(LatticeChain<SquareLattice,2>& LC) {
    release(static_cast<LatticeChainBase<SquareLattice,2,4,4>&>(LC));
  }
  void copy(LatticeChain<SquareLattice,2>& LC,
            const LatticeChain<SquareLattice,2>& cLC) {
    copy(static_cast<LatticeChainBase<SquareLattice,2,4,4>&>(LC),
         static_cast<const LatticeChainBase<SquareLattice,2,4,4>&>(cLC));
  }
  void refer(LatticeChain<SquareLattice,2>& LC,
             const LatticeChain<SquareLattice,2>& rLC) {
    refer(static_cast<LatticeChainBase<SquareLattice,2,4,4>&>(LC),
          static_cast<const LatticeChainBase<SquareLattice,2,4,4>&>(rLC));
  }

}

#endif
