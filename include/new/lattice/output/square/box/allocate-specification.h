
#ifndef _Lattice_Output_Square_Box_Allocate_Specification_H_
#define _Lattice_Output_Square_Box_Allocate_Specification_H_

#include "lattice/output/square/box/specification.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  template <unsigned int Dim>
  void allocate(LatticeOutput<SquareLattice,Dim,BoxOutput>& O) {
    release(O);
    allocate(O.Max,Dim);
    allocate(O.Min,Dim);
    allocate(O.RangeMax,Dim);
    allocate(O.RangeMin,Dim);
    allocate(O.posMax,Dim);
    allocate(O.posMin,Dim);
  }

}

#endif

