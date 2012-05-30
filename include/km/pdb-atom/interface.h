
#ifndef _PDB_Atom_Interface_H_
#define _PDB_Atom_Interface_H_

#include "pdb-atom-position/interface.h"
#include "array/interface.h"

namespace mysimulator {

  class PDBAtom {

    public:

      typedef PDBAtom   Type;
      friend void Clear(PDBAtom&);

      PDBAtom() : _location(), _altLocation(), _bfactor(0), _altBFactor() {}
      ~PDBAtom() { Clear(*this); }

      bool IsValid() const { return _location.IsValid(); }

      const PDBAtomPosition& Location() const { return _location; }
      const double BFactor() const { return _bfactor; }

    protected:

      PDBAtomPosition _location;
      Array<PDBAtomPosition> _altLocation;
      double _bfactor;
      Array<double> _altBFactor;

    private:

      PDBAtom(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBAtom& A) {
    Clear(A._location);
    Clear(A._altLocation);
    A._bfactor=0;
    Clear(A._altBFactor);
  }

}

#endif

