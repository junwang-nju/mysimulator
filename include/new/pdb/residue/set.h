
#ifndef _PDB_Residue_Set_H_
#define _PDB_Residue_Set_H_

#include "pdb/residue/interface.h"
#include "pdb/residue/atom-library.h"

namespace mysimulator {

  void set(PDBResidue& R, const PDBResidueName& RN) {
    assert(RN!=UnknownResidue);
    R.Name=RN;
    allocate(R.AtomName,ResidueSize[RN]);
    for(unsigned int i=0;i<ResidueSize[RN];++i)
      R.AtomName[i]=Atoms4Residue[i+AtomStart4Residue[RN]];
  }

}

#endif

