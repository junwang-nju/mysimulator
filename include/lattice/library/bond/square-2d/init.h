
#ifndef _Lattice_Library_Bond_Square2D_Init_H_
#define _Lattice_Library_Bond_Square2D_Init_H_

#include "lattice/library/bond/square-2d/interface.h"

namespace mysimulator {

  template <>
  void initLatticeBondLib<SquareLattice,2>() {
    LatticeBondLibSquare2D.load(".");
  }

  template <>
  void initLatticeBondLib<SquareLattice,2>(const char* Root) {
    LatticeBondLibSquare2D.load(Root);
  }

}

#endif

