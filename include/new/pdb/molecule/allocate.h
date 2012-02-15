
#ifndef _PDB_Molecule_Allocate_H_
#define _PDB_Molecule_Allocate_H_

#include "pdb/molecule/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  void allocate(PDBMolecule& M, const unsigned int& nres) {
    release(M);
    allocate(M.Residue,nres);
  }

}

#endif

