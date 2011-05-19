
#ifndef _Lattice_Library_Square2D_Specification_H_
#define _Lattice_Library_Square2D_Specification_H_

#include "lattice/library/interface.h"

namespace mysimulator {

  template <>
  const unsigned int LatticeLibrary<SquareLattice,2>::MaxBondOfMotif=10;
  template <>
  const unsigned int LatticeLibrary<SquareLattice,2>::NumNeighbors=4;
  template <>
  const unsigned int LatticeLibrary<SquareLattice,2>::NumShifts=3;
  template <>
  const char LatticeLibrary<SquareLattice,2>::relLocation[1024]=
      "include/lattice/library/square-2d";

}

#endif

