
#ifndef _Model_GO_PDB2ID_H_
#define _Model_GO_PDB2ID_H_

#include "pdb/contact/analyse.h"

namespace mysimulator {

  void _CreateID4PDB(const PDBObject& PO, Array1D<Array1D<int> >& ID) {
    assert(IsValid(PO));
  }

  void PDB2IDList(const PDBObject& PO, Array1D<Array1D<int> > ID) {
  }

}

#endif

