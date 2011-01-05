
#ifndef _Lattice_Chain_Operation_H_
#define _Lattice_Chain_Operation_H_

#include "data/lattice/chain.h"

namespace std {

  template <unsigned int LT, unsigned int LD>
  unsigned int GetBond(const LatticeChain<LT,LD>& LC, const unsigned int n) {
    unsigned int I=n/BN, J=n%BN;
    unsigned int motif=LC[I];
    return fetchLib<LT,LD>().BondMapper[motif][J];
  }

  template <unsigned int LT, unsigned int LD>
  const int* GetBondDirection(const LatticeChain<LT,LD>& LC,
                              const unsigned int n) {
    unsigned int I=n/BN, J=(n%BN)*LD;
    unsigned int motif=LC[I];
    return fetchLib<LT,LD>().BondDirectionMapper[motif].data+J;
  }

}

#endif
