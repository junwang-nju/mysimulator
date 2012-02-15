
#ifndef _PDB_Model_Allocate_H_
#define _PDB_Model_Allocate_H_

#include "pdb/model/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  void allocate(PDBModel& M, const unsigned int& nmol=1) {
    release(M);
    allocate(M.Molecule,nmol);
  }

}

#endif

