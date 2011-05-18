
#ifndef _Lattice_Library_Bond_Init_H_
#define _Lattice_Library_Bond_Init_H_

#include "lattice/library/bond/interface.h"

namespace mysimulator {

  template <LatticeTypeName LT, unsigned int Dim>
  void initLatticeBondLib() { Error("This Library is not Valid!"); }

  template <LatticeTypeName LT, unsigned int Dim>
  void initLatticeBondLib(const char*) { Error("This Library is not Valid!"); }

}

#endif

