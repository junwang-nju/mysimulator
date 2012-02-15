
#ifndef _PDB_Model_Interface_H_
#define _PDB_Model_Interface_H_

#include "pdb/molecule/interface.h"

namespace mysimulator {

  struct PDBModel {

    public:

      typedef PDBModel    Type;

      Array1D<PDBMolecule> Molecule;

      PDBModel() : Molecule() {}
      ~PDBModel() { clearData(); }

      void clearData() { release(Molecule); }
      bool isvalid() const { return IsValid(Molecule); }

    private:

      PDBModel(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  void release(PDBModel& M) { M.clearData(); }
  bool IsValid(const PDBModel& M) { return M.isvalid(); }

}

#endif

