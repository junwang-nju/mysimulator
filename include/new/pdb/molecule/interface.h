
#ifndef _PDB_Molecule_Interface_H_
#define _PDB_Molecule_Interface_H_

#include "pdb/residue/interface.h"

namespace mysimulator {

  struct PDBMolecule {

    public:

      typedef PDBMolecule   Type;

      Array1D<PDBResidue>   Residue;
      unsigned int Tag;

      PDBMolecule() : Residue(), Tag(0) {}
      ~PDBMolecule() { clearData(); }

      void clearData() { Tag=0; release(Residue); }
      bool isvalid() const { return IsValid(Residue)&&(Tag!=0); }

    private:

      PDBMolecule(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBMolecule& M) { M.clearData(); }
  bool IsValid(const PDBMolecule& M) { return M.isvalid(); }

}

#endif

