
#ifndef _Lattice_Motif_Chain_Interface_H_
#define _Lattice_Motif_Chain_Interface_H_

#include "vector/interface.h"

namespace mysimulator {

  struct LatticeMotifChain {

    typedef LatticeMotifChain Type;

    Vector<unsigned short>  motifID;
    Vector<unsigned int> property;

    LatticeMotifChain() : motifID(), property() {}
    LatticeMotifChain(const Type&) {
      Error("Copier of LatticeMotifChain Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LatticeMotifChain Disabled!");
      return *this;
    }
    ~LatticeMotifChain() { clearData(); }

    void clearData() { release(motifID); release(property); }

    const unsigned int& Length() const { return motifID.size; }

  };

  bool IsValid(const LatticeMotifChain& C) {
    return IsValid(C.motifID)&&IsValid(C.property);
  }

  void release(LatticeMotifChain& C) { C. clearData(); }

}

#endif

