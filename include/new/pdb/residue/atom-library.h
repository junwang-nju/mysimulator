
#ifndef _PDB_Residue_AtomLibrary_H_
#define _PDB_Residue_AtomLibrary_H_

#include "pdb/residue/name.h"

namespace mysimulator {

  static const unsigned int
  AtomStart4Residue[NumberResidueNames] = {
    0
  };

}

#include "pdb/atom/name.h"

namespace mysimulator {

  static const PDBAtomName Atoms4Residue[] = {
    AtomCA,       // Start Gly
    AtomN,
    AtomC,
    AtomO,
    AtomH,
    AtomHA2,
    AtomHA3       // End Gly
  };

}

#endif

