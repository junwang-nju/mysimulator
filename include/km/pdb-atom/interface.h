
#ifndef _PDB_Atom_Interface_H_
#define _PDB_Atom_Interface_H_

#include "pdb-atom-position/interface.h"
#include "pdb-atom/name.h"

namespace mysimulator {

  class PDBAtom {

    public:

      typedef PDBAtom   Type;
      friend void Clear(PDBAtom&);

      PDBAtom() : _tag(UnknownAtom), _loc(), _bfac(0) {}
      ~PDBAtom() { Clear(*this); }

      bool IsValid() const { return _loc.IsValid(); }

      void Allocate(PDBAtomName PAN) {
        Clear(*this);
        _tag=PAN;
      }

      const PDBAtomName Name() const { return _tag; }
      PDBAtomPosition& Location() { return _loc; }
      double& BFactor() { return _bfac; }

      const PDBAtomPosition& Location() const { return _loc; }
      const double& BFactor() const { return _bfac; }

    protected:

      PDBAtomName _tag;
      PDBAtomPosition _loc;
      double _bfac;

    private:

      PDBAtom(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBAtom& A) {
    A._tag=UnknownAtom;
    Clear(A._loc);
    A._bfac=0;
  }

}

#endif

