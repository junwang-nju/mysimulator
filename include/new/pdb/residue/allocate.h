
#ifndef _PDB_Residue_Allocate_H_
#define _PDB_Residue_Allocate_H_

#include "pdb/residue/interface.h"
#include "array/1d/allocate.h"
#include "array/1d/fill.h"

namespace mysimulator {

  void allocate(PDBResidue& R) {
    release(R);
    allocate(R.Atom,NumberAtomNames);
    fill(R.Atom,NULL);
  }

}

#endif

