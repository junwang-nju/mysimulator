
#ifndef _PDB_Model_Interface_H_
#define _PDB_Model_Interface_H_

#include "pdb-molecule/interface.h"

namespace mysimulator {

  class PDBModel {

    public:

      typedef PDBModel    Type;
      friend void Clear(PDBModel&);

      PDBModel() : _Molecule() {}
      ~PDBModel() { Clear(*this); }

      bool IsValid() const { return _Molecule.IsValid(); }

      void Allocate(unsigned int n) { Clear(*this); _Molecule.Allocate(n); }

      PDBMolecule& Molecule(unsigned int i) {
        assert(_Molecule.IsValid());
        return _Molecule[i];
      }
      const PDBMolecule& Molecule(unsigned int i) const {
        assert(_Molecule.IsValid());
        return _Molecule[i];
      }

    protected:

      Array<PDBMolecule>  _Molecule;

    private:

      PDBModel(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void Clear(PDBModel& M) { Clear(M._Molecule); }

}

#endif

