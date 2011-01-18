
#ifndef _Lattice_Chain_Operation_H_
#define _Lattice_Chain_Operation_H_

#include "data/lattice/chain.h"

namespace std {

  template <unsigned int LT, unsigned int LD>
  unsigned int GetBond(const LatticeChain<LT,LD>& LC, const unsigned int n) {
    const BondLib<LT,LD>& rBL=RunBondLibrary<LT,LD>();
    unsigned int I=n/rBL.BondNumber();
    unsigned int J=n%rBL.BondNumber();
    unsigned int motif=LC[I];
    return rBL.Bond(motif)[J];
  }

  template <unsigned int LT, unsigned int LD>
  const int* GetBondDirection(const LatticeChain<LT,LD>& LC,
                              const unsigned int n) {
    const BondLib<LT,LD>& rBL=RunBondLibrary<LT,LD>();
    unsigned int I=n/rBL.BondNumber();
    unsigned int J=n%rBL.BondNumber();
    unsigned int motif=LC[I];
    return rBL.Site(motif).data+J;
  }

  template <unsigned int LT, unsigned int LD>
  void SetChain(LatticeChain<LT,LD>& LC, const Vector<unsigned int>& bv) {
    const BondLib<LT,LD>& rBL=RunBondLibrary<LT,LD>();
    allocate(LC,bv.size);
    unsigned int I=bv.size/rBL.BondNumber();
    unsigned int J=bv.size%rBL.BondNumber();
    bool flag;
    for(unsigned int i=0;i<I;++i)
    for(unsigned int j=0;j<rBL.MotifNumber(0);++j) {
      flag=true;
      for(unsigned int k=0;k<rBL.BondNumber();++k)
        if(bv[i*rBL.BondNumber()+k]!=rBL.Bond(j)[k]){
          flag=false;
          break;
        }
      if(flag) {
        LC[i]=static_cast<unsigned char>(j);
        break;
      }
    }
    if(J!=0) {
      unsigned int M=rBL.BondNumber()-J;
      for(unsigned int j=rBL.MotifShift(M);
                       j<rBL.MotifShift(M)+rBL.MotifNumber(M);++j) {
        flag=true;
        for(unsigned int k=0;k<J;++k)
          if(bv[I*rBL.BondNumber()+k]!=rBL.Bond(j)[k]){
            flag=false;
            break;
          }
        if(flag) {
          LC[I]=static_cast<unsigned char>(j);
          break;
        }
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
    copy(CS[Z],static_cast<const Vector<unsigned char>&>(LC));
  } 

}

#endif
