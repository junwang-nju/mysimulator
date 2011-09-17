
#ifndef _Lattice_Motif_Allocate_H_
#define _Lattice_Motif_Allocate_H_

#include "lattice/motif/interface.h"
#include "array/2d/allocate.h"
#include "array/1d/fill.h"

namespace mysimulator {

  void allocate(LatticeMotif& M, const LatticeShapeName& Nm,
                const unsigned int& len,const unsigned int& d=0) {
    release(M);
    unsigned int rd;
    if(Nm==SquareLattice) {
      assert(d!=0);
      rd=d;
      M.name=SquareLattice;
    } else Error("Improper Name for Lattice!");
    allocate(M.bond,len);
    fill(M.bond,ucZero);
    allocate(M.coordinate,len,rd);
  }

  void imprint(LatticeMotif& M, const LatticeMotif& cM) {
    assert(IsValid(cM));
    release(M);
    M.name=cM.name;
    imprint(M.bond,cM.bond);
    imprint(M.coordinate,cM.coordinate);
  }

}

#endif

