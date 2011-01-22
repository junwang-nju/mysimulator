
#ifndef _Lattice_Chain_Operation_H_
#define _Lattice_Chain_Operation_H_

#include "data/lattice/chain.h"

namespace std {

  template <unsigned int LT, unsigned int LD>
  unsigned int GetBond(const LatticeChain<LT,LD>& LC, const unsigned int n) {
    const BondLib<LT,LD>& rBL=RunBondLibrary<LT,LD>();
    unsigned int I=n/rBL.MaxBonds;
    unsigned int J=n%rBL.MaxBonds;
    unsigned int NB=(I==LC.Length()-1?LC.ResidualBonds():rBL.MaxBonds);
    unsigned int motif=LC[I];
    return rBL.mapper[NB][motif][J];
  }

  template <unsigned int LT, unsigned int LD>
  const int* GetBondDirection(const LatticeChain<LT,LD>& LC,
                              const unsigned int n) {
    const BondLib<LT,LD>& rBL=RunBondLibrary<LT,LD>();
    unsigned int I=n/rBL.MaxBonds;
    unsigned int J=n%rBL.MaxBonds;
    unsigned int NB=(I==LC.Length()-1?LC.ResidualBonds():rBL.MaxBonds);
    unsigned int motif=LC[I];
    return rBL.xmapper[NB][motif].data+J*LD;
  }

  template <unsigned int LT, unsigned int LD>
  void SetChain(LatticeChain<LT,LD>& LC, const Vector<unsigned int>& bv) {
    const BondLib<LT,LD>& rBL=RunBondLibrary<LT,LD>();
    allocate(LC,bv.size+1);
    bool flag;
    unsigned int nmotif;
    for(unsigned int i=0;i<LC.size-1;++i) {
      nmotif=rBL.mshift[rBL.MaxBonds-1][2];
      for(unsigned int j=0;j<nmotif;++j) {
        flag=true;
        for(unsigned int k=0;k<rBL.MaxBonds;++k)
          if(bv[i*rBL.MaxBonds+k]!=rBL.mapper[rBL.MaxBonds-1][j][k]) {
            flag=false;
            break;
          }
        if(flag) {
          LC[i]=static_cast<unsigned short int>(j);
          break;
        }
      }
    }
    unsigned int M=bv.size-LC.ResidualBonds();
    nmotif=rBL.mshift[LC.ResidualBonds()-1][2];
    for(unsigned int j=0;j<nmotif;++j) {
      flag=true;
      for(unsigned int k=0;k<LC.ResidualBonds();++k)
        if(bv[M+k]!=rBL.mapper[LC.ResidualBonds()-1][j][k]) {
          flag=false;
          break;
        }
      if(flag) {
        LC[LC.size-1]=static_cast<unsigned short int>(j);
        break;
      }
    }
  }

  void WriteSequence(const LatticeChain<SquareLattice,2>& LC, ostream& os,
                     const unsigned int Z) {
    os<<LC<<endl;
  }

}

#include "data/lattice/chain-set.h"

namespace std {

  void WriteSequence(const LatticeChain<SquareLattice,2>& LC,
                     LatticeChainSet<SquareLattice,2>& CS,
                     const unsigned int Z) {
    assert(LC.Length()==CS.Length());
    copy(CS[Z],static_cast<const Vector<unsigned short int>&>(LC));
  } 

}

#endif
