
#ifndef _Bond_Library_Operation_H_
#define _Bond_Library_Operation_H_

#include "data/lattice/bond-library.h"

namespace std {

  template <unsigned int LT,unsigned int LD,unsigned int NN,unsigned int BN>
  void loadLib(BondLib<LT,LD,NN,BN>& BL, const char* fname) {
    allocate(BL);
    ifstream ifs(fname);
    for(unsigned int i=0;i<BondLib<LT,LD,NN,BN>::MotifNumber;++i) {
      for(unsigned int k=0;k<BN;++k)    ifs>>BL.BondMapper[i][k];
      for(unsigned int k=0;k<BN*LD;++k) ifs>>BL.BondDirectionMapper[i][k];
    }
    ifs.close();
  }

  void initLib<SquareLattice,2,4,4>() {
    loadLib(BondLibSquare2D,"./square-2d.conf");
  }
  void load(BondLib<SquareLattice,2,4,4>& BL) { refer(BL,BondLibSquare2D); }

}

#endif
