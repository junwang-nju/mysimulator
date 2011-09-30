
#ifndef _Lattice_Enumerate_RunData_Interface_H_
#define _Lattice_Enumerate_RunData_Interface_H_

#include "lattice/shape/name.h"

namespace mysimulator {

  template <LatticeShapeName LSN, unsigned int Dim, unsigned int Len>
  struct LatticeEnumRunData {};

}

#include "lattice/enumerate/run-data/square-2d/specification.h"

#endif

