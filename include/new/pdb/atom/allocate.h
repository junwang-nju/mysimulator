
#ifndef _PDB_Atom_Allocate_H_
#define _PDB_Atom_Allocate_H_

#include "pdb/atom/interface.h"

namespace mysimulator {

  void allocate(PDBAtom& A, const unsigned int& nloc=1) {
    release(A);
    if(nloc-1>0)  { allocate(A.altLoc,nloc-1); allocate(A.altBFactor,nloc-1); }
  }

}

#endif

