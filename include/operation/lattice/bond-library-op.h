
#ifndef _Bond_Library_Operation_H_
#define _Bond_Library_Operation_H_

#include "data/lattice/bond-library.h"

namespace std {

  template <unsigned int LT, unsigned int LD>
  void LoadBondLibrary() {
    myError("This library is not available");
  }
  template <unsigned int LT, unsigned int LD>
  void LoadBondLibrary(const char*) {
    myError("This library is not available");
  }
  template <unsigned int LT, unsigned int LD>
  void UnloadBondLibrary() {
    myError("This library is not available");
  }


  template <>
  void LoadBondLibrary<SquareLattice,2>() {
    pBondLibSquare2D=new BondLib<SquareLattice,2>(".");
  }
  template <>
  void LoadBondLibrary<SquareLattice,2>(const char* ROOT) {
    pBondLibSquare2D=new BondLib<SquareLattice,2>(ROOT);
  }
  template <>
  void UnloadBondLibrary<SquareLattice,2>() { safe_delete(pBondLibSquare2D); }

}

#endif

