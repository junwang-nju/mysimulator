
#ifndef _PDB_Residue_Guess_ResidueName_H_
#define _PDB_Residue_Guess_ResidueName_H_

#include "pdb-residue/key-library.h"

namespace mysimulator {

  PDBResidueName GuessResidueName(const ArrayData<unsigned int>& Key) {
    assert(Key.IsValid());
    bool flag;
    PDBResidueName PRN;
    for(unsigned int i=0;i<ResidueKeyLibrarySize;++i) {
      flag=true;
      for(unsigned int k=0;k<NumberResidueKey;++k)
        if(Key[k]!=ResidueKeyLibrary[i][k]) { flag=false; break; }
      if(flag)  { RRN=Residue4Key[i]; break; }
    }
    return PRN;
  }

}

#endif

