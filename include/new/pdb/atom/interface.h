
#ifndef _PDB_Atom_Interface_H_
#define _PDB_Atom_Interface_H_

#include "pdb/atom/position/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  struct PDBAtom {

    public:

      typedef PDBAtom   Type;

      PDBAtomPosition Loc;
      Array1D<PDBAtomPosition>  altLoc;
      double BFactor;
      Array1D<double> altBFactor;

      PDBAtom() : Loc(), altLoc(), BFactor(), altBFactor() {}
      ~PDBAtom() { clearData(); }

      void clearData() {
        release(altBFactor); BFactor=0; release(altLoc); release(Loc);
      }
      bool isvalid() const { return IsValid(Loc); }

    private:

      PDBAtom(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBAtom& A) { A.clearData(); }
  bool IsValid(const PDBAtom& A) { return A.isvalid(); }

}

#endif

