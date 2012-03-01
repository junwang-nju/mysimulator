
#ifndef _PDB_Residue_Get_Name_H_
#define _PDB_Residue_Get_Name_H_

#include "pdb/residue/key-library.h"

namespace mysimulator {

  PDBResidueName GetResidueName(const unsigned int* Key) {
    bool flag;
    unsigned int n;
    for(unsigned int i=0;i<KeyLibrarySize;++i) {
      flag=true;
      for(unsigned int k=0;k<KeySize4Residue;++k)
        if(Key[k]!=KeyLibrary4Residue[i][k])  { flag=false; break; }
      if(flag)  { n=i; break; }
    }
    return (flag?Residue4Key[n]:UnknownResidue);
  }

}

#endif

