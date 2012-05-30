
#ifndef _PDB_Residue_Interface_H_
#define _PDB_Residue_Interface_H_

#include "pdb-residue/name.h"
#include "pdb-atom/interface.h"
#include "pdb-residue/atom-library.h"

namespace mysimulator {

  class PDBResidue {

    public:

      typedef PDBResidue    Type;
      friend void Clear(PDBResidue&);

      PDBResidue() : _tag(UnknownResidue), _Atom(), _ID(-1) {}
      ~PDBResidue() { Clear(*this); }

      bool IsValid() const {
        return (_tag!=UnknownResidue)&&_Atom.IsValid()&&(_ID!=-1);
      }

      void Allocate(PDBResidueName& RN) {
        assert(RN!=UnknownResidue);
        Clear(*this);
        _tag=RN;
        _Atom.Allocate(ResidueSize[RN]);
      }

      const PDBResidueName Name() const { return _tag; }
      PDBAtom& Atom(unsigned int i) {
        assert(_Atom.IsValid()); return _Atom[i];
      }
      const PDBAtom& Atom(unsigned int i) const {
        assert(_Atom.IsValid()); return _Atom[i];
      }
      const unsigned int SeqIndex() const {
        assert(_ID>-1); return static_cast<unsigned int>(_ID);
      }

    protected:

      PDBResidueName  _tag;
      Array<PDBAtom>  _Atom;
      int _ID;

    private:

      PDBResidue(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBResidue& R) {
    R._tag=UnknownResidue;
    Clear(R._Atom);
    R._ID=-1;
  }

}

#endif

