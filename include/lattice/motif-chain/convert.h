
#ifndef _Lattice_Motif_Chain_Convert_H_
#define _Lattice_Motif_Chain_Convert_H_

#include "lattice/motif-chain/interface.h"

namespace mysimulator {

  template <LatticeShapeName LS, unsigned int D, unsigned int L>
  void convert(const Vector<unsigned char>& bond, LatticeMotifChain<LS,D,L>& C){
    assert(bond.size>=L);
    assert(IsValid(C));
    bool flag;
    Vector<unsigned short> motifID(LatticeMotifChain<LS,D,L>::NumMotifs);
    copy(motifID,LatticeLibrary<LS,D>::MaxBondOfMotif);
    motifID[LatticeMotifChain<LS,D,L>::NumMotifs-1]=
      LatticeMotifChain<LS,D,L>::NumBondsLastMotif;
    unsigned short nmotifs;
    unsigned int bsh=0,sz,u;
    for(unsigned int i=0;i<LatticeMotifChain<LS,D,L>::NumMotifs;++i) {
      u=motifID[i];
      sz=LatticeLibrary<LS,D>::shiftLoc[u-1].size;
      nmotifs=LatticeLibrary<LS,D>::shiftLoc[u-1][sz-1];
      for(unsigned short j=0;j<nmotifs;++j) {
        flag=true;
        for(unsigned int k=0;k<u;++k)
          if(bond[bsh+k]!=LatticeLibrary<LS,D>::map[u-1][j].bond[k]) {
            flag=false;
            break;
          }
        if(flag) {
          C.motifValue[i]=j;
          break;
        }
      }
      bsh+=motifID[i];
    }
  }

}

#endif

