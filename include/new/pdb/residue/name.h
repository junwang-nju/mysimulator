
#ifndef _PDB_Residue_Name_H_
#define _PDB_Residue_Name_H_

namespace mysimulator {

  enum PDBResidueName {
    Gly=0,
    NumberResidueNames,
    UnknownResidue
  };

}

#include "pdb/atom/name.h"

namespace mysimulator {

  enum PDBResidueAtomRange {
    GlyStart=GlyCA,
    GlyEnd=GlyHA3
  };

  static const PDBResidueAtomRange ResidueStart[NumberResidueNames]= {
    GlyAStart
  };
  static const PDBResidueAtomRange ResidueEnd[NumberResidueNames]= {
    GlyEnd
  };

}

#endif

