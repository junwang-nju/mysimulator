
#ifndef _PDB_Molecule_Interface_H_
#define _PDB_Molecule_Interface_H_

#include "pdb-residue/interface.h"

namespace mysimulator {

  class PDBMolecule {

    public:

      typedef PDBMolecule   Type;
      friend void Clear(PDBMolecule&);

      PDBMolecule() : _Residue(), _tag(0) {}
      ~PDBMolecule() { Clear(*this); }

      bool IsValid() const { return _Residue.IsValid()&&(_tag!=0); }

      void Allocate(unsigned int n) { Clear(*this); _Residue.Allocate(n); }

      PDBResidue& Residue(unsigned int i) { return _Residue[i]; }
      const PDBResidue& Residue(unsigned int i) const { return _Residue[i]; }
      const unsigned int Tag() const { return _tag; }

    protected:

      Array<PDBResidue> _Residue;
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

