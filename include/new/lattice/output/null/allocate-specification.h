
#ifndef _Lattice_Output_Null_Allocation_H_
#define _Lattice_Output_Null_Allocation_H_

#include "lattice/output/null/specification.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim>
  void allocate(LatticeOutput<LSN,Dim,NullOutput>&) {}

}

#endif

