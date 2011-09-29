
#ifndef _Lattice_Enumerate_RunData_Allocate_H_
#define _Lattice_Enumerate_RunData_Allocate_H_

#include "lattice/enumerate/run-data/interface.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  void allocate(LatticeEumRunData<LSN,Dim,Len>& D) {
    Error("This kind of Data Are Not Implemented!");
  }

}

#include "lattice/enumerate/run-data/square-2d/allocate-specification.h"

#endif

