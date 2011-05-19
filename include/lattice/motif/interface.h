
#ifndef _Lattice_Motif_Interface_H_
#define _Lattice_Motif_Interface_H_

#include "list/interface.h"

namespace mysimulator {

  struct LatticeMotif {

    typedef LatticeMotif  Type;

    Vector<unsigned int> bond;
    List<int> coordinate;

    LatticeMotif() : bond(), coordinate() {}
    LatticeMotif(const Type&) { Error("Copier of LatticeMotif Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeMotif Disabled!");
      return *this;
    }
    ~LatticeMotif() { clearData(); }

    void clearData() { release(bond); release(coordinate); }
    const unsigned int Dimension() const { return coordinate[0].size; }

  };

  bool IsValid(const LatticeMotif& M) {
    return IsValid(M.bond)&&IsValid(M.coordinate);
  }

  void release(LatticeMotif& M) { M.clearData(); }

}

#endif

