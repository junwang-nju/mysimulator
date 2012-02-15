
#ifndef _PDB_Residue_Key_Library_H_
#define _PDB_Residue_Key_Library_H_

#include "pdb/atom/name.h"
#include "pdb/residue/name.h"

namespace mysimulator {

  static const unsigned int KeySize4Residue=(NumberAtomNames-1)/32+1;

  static const unsigned int KeyLibrarySize=1;

  static const unsigned int
  KeyLibrary4Residue[KeyLibrarySize][KeySize4Residue] = {
    { 37,  45 }
  };

  static const PDBResidueName
  Residue4Key[KeyLibrarySize] = {
    Gly
  };

}

#endif

