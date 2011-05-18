
#ifndef _Lattice_Library_Bond_2D_Interface_H_
#define _Lattice_Library_Bond_2D_Interface_H_

#include "lattice/library/bond/interface.h"

namespace mysimulator {

  template <>
  const unsigned int LatticeBondLib<SquareLattice,2>::MaxMotifs=10;

  template <>
  const unsigned int LatticeBondLib<SquareLattice,2>::NumNeighbors=4;

  template <>
  const unsigned int LatticeBondLib<SquareLattice,2>::NumberShifts=3;

  template <>
  void LatticeBondLib<SquareLattice,2>::load(const char* Root) {
    if(IsValid(*this))  return;
    static char tmbuffer[1024];
    sprintf(tmbuffer,"%s/include/lattice/library/bond/square-2d/data/chain-l",
            Root);
    _read(tmbuffer);
    int x,y;
    for(unsigned int i=0,nbond=0,nmap=0;i<MaxMotifs;++i) {
      nbond=i+1;
      nmap=map[i].ListSize();
      for(unsigned int k=0;k<nmap;++k) {
        x=y=0;
        for(unsigned int l=0,n=0;l<nbond;++l) {
          switch(map[i][k][l]) {
            case  0: ++x; break;
            case  1: ++y; break;
            case  2: --y; break;
            case  3: --x; break;
          }
          coordinateMap[i][k][n++]=x;
          coordinateMap[i][k][n++]=y;
        }
      }
    }
  }

}

#endif

