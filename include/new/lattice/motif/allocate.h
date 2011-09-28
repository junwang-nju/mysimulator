
#ifndef _Lattice_Motif_Allocate_H_
#define _Lattice_Motif_Allocate_H_

#include "lattice/motif/interface.h"
#include "array/1d/allocate.h"
#include "array/1d/fill.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void allocate(LatticeMotif<LSN,Dim>& M, const unsigned int& len) {
    release(M);
    if(LSN==SquareLattice) {
      assert(Dim!=0);
    } else Error("Improper Name for Lattice!");
    allocate(M.bond,len);
    fill(M.bond,ucZero);
    allocate(M.coordinate,len);
  }

  template <LatticeShapeName LSN, unsigned int Dim>
  void imprint(LatticeMotif<LSN,Dim>& M, const LatticeMotif<LSN,Dim>& cM) {
    assert(IsValid(cM));
    release(M);
    imprint(M.bond,cM.bond);
    imprint(M.coordinate,cM.coordinate);
  }

}

#endif

