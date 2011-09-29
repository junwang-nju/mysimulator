
#ifndef _Lattice_MotifChain_InputOutput_H_
#define _Lattice_MotifChain_InputOutput_H_

#include "lattice/motif-chain/interface.h"
#include "array/1d/io.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  OutputBase& operator<<(OutputBase& os,
                         const LatticeMotifChain<LSN,Dim,Len>& C) {
    assert(IsValid(C));
    os<<Len<<"\t"<<C.SegMotif;
    return os;
  }

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  InputBase& operator>>(InputBase& is, LatticeMotifChain<LSN,Dim,Len>& C) {
    assert(IsValid(C));
    unsigned int L;
    is>>L;
    if(L!=Len)  Error("Length of Data Does Not Match Chain!");
    is>>C.SegMotif;
    return is;
  }

}

#endif

