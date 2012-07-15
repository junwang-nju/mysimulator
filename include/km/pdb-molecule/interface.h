
#ifndef _PDB_Molecule_Interface_H_
#define _PDB_Molecule_Interface_H_

#include "pdb-alt-residue/interface.h"

namespace mysimulator {

  class PDBMolecule {

    public:

      typedef PDBMolecule   Type;
      friend void Clear(PDBMolecule&);
      friend class PDBFile;

      PDBMolecule() : _Residue(), _tag(0) {}
      ~PDBMolecule() { Clear(*this); }

      bool IsValid() const { return _Residue.IsValid()&&(_tag!=0); }

      void Allocate(unsigned int n) { Clear(*this); _Residue.Allocate(n); }

      PDBAltResidue& AltResidue(unsigned int i) { return _Residue[i]; }
      PDBResidue& Residue(unsigned int i, unsigned int w=0) {
        return _Residue[i].WorkResidue(w);
      }
      const PDBAltResidue& AltResidue(unsigned int i) const {
        return _Residue[i];
      }
      const PDBResidue& Residue(unsigned int i, unsigned int w=0) const {
        return _Residue[i].WorkResidue(w);
      }
      const unsigned int Tag() const { return _tag; }

      const unsigned int NumberResidue() const { return _Residue.Size(); }

    protected:

      Array<PDBAltResidue> _Residue;
      unsigned int _tag;

    private:

      PDBMolecule(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBMolecule& M) {
    Clear(M._Residue);
    M._tag=0;
  }

}

#endif

