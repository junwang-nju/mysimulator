
#ifndef _Lattice_Analyse_TurnCount_H_
#define _Lattice_Analyse_TurnCount_H_

#include "array/1d/content/interface.h"

namespace mysimulator {

  unsigned int NumTurns(const Array1DContent<int>& Branch) {
    unsigned int nt=0;
    for(int i=2;i<=Branch.last;++i)  nt+=(Branch[i-1]!=Branch[i]?1:0);
    return nt;
  }

}

#endif

