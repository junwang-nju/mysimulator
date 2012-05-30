
#ifndef _PDB_Atom_Interface_H_
#define _PDB_Atom_Interface_H_

#include "pdb-atom-position/interface.h"
#include "array/interface.h"
#include "pdb-atom/name.h"

namespace mysimulator {

  class PDBAtom {

    public:

      typedef PDBAtom   Type;
      friend void Clear(PDBAtom&);

      PDBAtom() : _tag(UnknownAtom), _loc(), _altLoc(), _bfac(0), _altBFac() {}
      ~PDBAtom() { Clear(*this); }

      bool IsValid() const { return _loc.IsValid(); }

      void Allocate(PDBAtomName PAN) {
        Clear(*this);
        _tag=PAN;
      }

      const PDBAtomName Name() const { return _tag; }
      PDBAtomPosition& Location() { return _loc; }
      double& BFactor() { return _bfac; }
      PDBAtomPosition& AltLocation(unsigned int i) {
        assert(_altLoc.IsValid());
        return _altLoc[i];
      }
      double& ALtBFactor(unsigned int i) {
        assert(_altBFac.IsValid());
        return _altBFac[i];
      }
      const PDBAtomPosition& Location() const { return _loc; }
      const double& BFactor() const { return _bfac; }
      const PDBAtomPosition& AltLocation(unsigned int i) const {
        assert(_altLoc.IsValid());
        return _altLoc[i];
      }
      const double& ALtBFactor(unsigned int i) const {
        assert(_altBFac.IsValid());
        return _altBFac[i];
      }

    protected:

      PDBAtomName _tag;
      PDBAtomPosition _loc;
      Array<PDBAtomPosition> _altLoc;
      double _bfac;
      Array<double> _altBFac;

    private:

      PDBAtom(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBAtom& A) {
    A._tag=UnknownAtom;
    Clear(A._loc);
    Clear(A._altLoc);
    A._bfac=0;
    Clear(A._altBFac);
  }

}

#endif

