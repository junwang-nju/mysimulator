
#ifndef _Lattice_Chain_Operation_H_
#define _Lattice_Chain_Operation_H_

#include "data/lattice/chain-base.h"

namespace std {

  template <unsigned int LT, unsigned int LD, unsigned int NN, unsigned int BN>
  unsigned int GetBond(const LatticeChainBase<LT,LD,NN,BN>& LC,
                       const unsigned int n){
    unsigned int I=n/BN, J=n&BN;
    unsigned int motif=LC[I];
    return LC.runLib.BondMapper[motif][J];
  }

  template <unsigned int LT, unsigned int LD, unsigned int NN, unsigned int BN>
  const int* GetBondDirection(const LatticeChainBase<LT,LD,NN,BN>& LC,
                              const unsigned int n) {
    unsigned int I=n/BN, J=(n%BN)*LD;
    unsigned int motif=LC[I];
    return LC.runLib.BondDirectionMapper[motif].data+J;
  }

}

#endif
