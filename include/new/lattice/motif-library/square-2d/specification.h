
#ifndef _Lattice_Motif_Library_Square2D_Specification_H_
#define _Lattice_Motif_Library_Square2D_Specification_H_

#include "lattice/motif-library/interface.h"

namespace mysimulator {

  template <>
  const unsigned int LatticeMotifLibrary<SquareLattice,2U>::MaxBondOfMotif=10;

  template <>
  const unsigned int LatticeMotifLibrary<SquareLattice,2U>::NumStart=8;

  template <>
  const char LatticeMotifLibrary<SquareLattice,2U>::relFileLoc[]=
    "lattice/motif-library/square-2d/data";

}

#endif

