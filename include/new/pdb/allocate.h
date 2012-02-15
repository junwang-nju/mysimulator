
#ifndef _PDB_Allocate_H_
#define _PDB_Allocate_H_

#include "pdb/interface.h"
#include "array/1d/allocate.h"

namespace mysimulator {

  void allocate(PDBObject& O, const unsigned int& n=1) {
    release(O);
    allocate(O.Model,n);
  }

}

#endif

