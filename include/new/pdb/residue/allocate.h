
#ifndef _PDB_Residue_Allocate_H_
#define _PDB_Residue_Allocate_H_

#include "pdb/residue/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  void allocate(PDBResidue& R) {
    release(R);
    allocate(R.Atom,NumberAtomNames);
    for(unsigned int i=0;i<NumberAtomNames;++i) R.Atom[i]=NULL;
  }

}

#endif

