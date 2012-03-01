
#ifndef _PDB_Residue_AtomLibrary_H_
#define _PDB_Residue_AtomLibrary_H_

#include "pdb/residue/name.h"

namespace mysimulator {

  static const unsigned int
  AtomStart4Residue[NumberResidueNames] = {
    0,
    10,
    34
  };

}

#include "pdb/atom/name.h"

namespace mysimulator {

  static const PDBAtomName Atoms4Residue[] = {
    AtomCA,       // Start Ala
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomH,
    AtomHA,
    AtomHB1,
    AtomHB2,
    AtomHB3,
    AtomCA,
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomNE,
    AtomCZ,
    AtomNH1,
    AtomNH2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,
    AtomHE,
    AtomHH11,
    AtomHH12,
    AtomHH21,
    AtomHH22,
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

