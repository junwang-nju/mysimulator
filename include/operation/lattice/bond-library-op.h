
#ifndef _Bond_Library_Operation_H_
#define _Bond_Library_Operation_H_

#include "data/lattice/bond-library.h"
#include <cstring>

namespace std {

  template <unsigned int LT,unsigned int LD>
  void loadLibBond(BondLib<LT,LD>& BL, const char* fname) {
    allocate(BL);
    ifstream ifs(fname);
    for(unsigned int i=0;i<BondLib<LT,LD>::MotifNumber;++i)
    for(unsigned int k=0;k<BondLib<LT,LD>::BondNumber;++k)
      ifs>>BL.BondMapper[i][k];
    for(unsigned int i=0;i<LD;++i)
      ifs>>BL.property[i];
    ifs.close();
  }

  template <unsigned int LT, unsigned int LD>
  void initLib(const char*){ myError("Not implemented for present lattice"); }

  template <>
  void initLib<SquareLattice,2>(const char* ROOT) {
    static char buff[1024];
    strcpy(buff,ROOT);
    strcat(buff,"/include/data/lattice/square-2d.conf");
    loadLibBond(BondLibSquare2D,buff);
    int x,y;
    for(unsigned int i=0;i<BondLib<SquareLattice,2>::MotifNumber;++i) {
      x=y=0;
      for(unsigned int k=0,n=0;k<BondLib<SquareLattice,2>::BondNumber;++k) {
        switch(BondLibSquare2D.BondMapper[i][k]) {
          case 0: ++x;  break;
          case 1: ++y;  break;
          case 2: --y;  break;
          case 3: --x;  break;
        }
        BondLibSquare2D.BondDirectionMapper[i][n++]=x;
        BondLibSquare2D.BondDirectionMapper[i][n++]=y;
      }
    }
  }
  
  template <unsigned int LT, unsigned int LD>
  const BondLib<LT,LD>& fetchLib() {
    myError("This library is not available");
  }

  template <>
  const BondLib<SquareLattice,2>& fetchLib<SquareLattice,2>() {
    return BondLibSquare2D;
  }

}

#endif
