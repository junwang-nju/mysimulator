
#ifndef _Lattice_MotifChain_Convert_H_
#define _Lattice_MotifChain_Convert_H_

#include "lattice/motif-chain/interface.h"

#define _LibBond(h,g) \
  reinterpret_cast<char*>(LatticeMotifLibrary<LSN,Dim>::map[h][g].bond.start)

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  void convert(const Array1DContent<unsigned char>& bd,
               LatticeMotifChain<LSN,Dim,Len>& C) {
    assert(IsValid(C));
    assert(bd.size>=Len-1);
    char* bp=reinterpret_cast<char*>(const_cast<unsigned char*>(bd.start));
    unsigned int u,nu;
    unsigned int ni=LatticeMotifChain<LSN,Dim,Len>::NumMotifs-1;
    u=LatticeMotifLibrary<LSN,Dim>::MaxBondOfMotif;
    nu=LatticeMotifLibrary<LSN,Dim>::map[u-1].size;
    for(unsigned int i=0;i<ni;++i) {
      for(unsigned int j=0;j<nu;++j)
        if(strncmp(bp,_LibBond((u-1),j),u)==0) {
          C.SegMotif[i]=j;
          break;
        }
      bp+=u;
    }
    u=LatticeMotifChain<LSN,Dim,Len>::NumBondsLastMotif;
    nu=LatticeMotifLibrary<LSN,Dim>::map[u-1].size;
    for(unsigned int j=0;j<nu;++j)
      if(strncmp(bp,_LibBond((u-1),j),u)==0) {
        C.SegMotif[ni]=j;
        break;
      }
  }

}

#undef _LibBond

#endif

