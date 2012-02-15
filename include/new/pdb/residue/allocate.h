
#ifndef _PDB_Residue_Allocate_H_
#define _PDB_Residue_Allocate_H_

#include "pdb/residue/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  void allocate(PDBResidue& R, const PDBResidueName& PRN) {
    assert(PRN!=UnknownResidue);
    release(R);
    R.Name=PRN;
    allocate(R.Atom,ResidueStart[PRN],ResidueEnd[PRN]);
  }

}

#endif

