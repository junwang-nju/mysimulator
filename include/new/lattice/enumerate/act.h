
#ifndef _Lattice_Enumerate_Act_H_
#define _Lattice_Enumerate_Act_H_

#include "lattice/enumerate/run-data/allocate.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len,
            LatticeEnumCheckMethodName ECMethod>
  unsigned long long enumerate(
      const LatticeEnumCheck<LSN,Dim,ECMethod>& Check,
      LatticeEnumProcessBase<LSN,Dim,Len>& Proc) {
    unsigned long long NC=0;
    bool flag;
    LatticeEnumRunData<LSN,Dim,Len> Data;
    allocate(Data);
    do {
      if(Check(Data)) {
        if(Data.RunMotif+1<LatticeMotifChain<SquareLattice,2U,Len>::NumMotifs) {
          _NextMotif(Data);
          flag=false;
        } else {
          Proc(Data);
          flag=true;
          ++NC;
        }
      }
      if(flag)  _IncMotif(Data);
    } while(Data.RunMotif>=0);
    release(Data);
    return NC;
  }

}

#endif

