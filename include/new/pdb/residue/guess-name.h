
#ifndef _PDB_Residue_GuessName_H_
#define _PDB_Residue_GuessName_H_

#include "pdb/atom/interface.h"
#include "pdb/residue/name.h"
#include "pdb/residue/key-library.h"

namespace mysimulator {

  PDBResidueName GuessName(const Array1DContent<PDBAtom*>& Atoms) {
    assert(Atoms.size==NumberAtomNames);
    PDBResidueName RN=UnknownResidue;
    unsigned int key[KeySize4Residue];
    for(unsigned int i=0;i<KeySize4Residue;++i) key[i]=0;
    for(unsigned int i=0;i<NumberAtomNames;++i)
      if(Atoms[i]!=NULL)  key[i/32]+=(1<<(i%32));
    bool flag;
    for(unsigned int i=0;i<KeyLibrarySize;++i) {
      flag=true;
      for(unsigned int k=0;k<KeySize4Residue;++k)
        if(key[k]!=KeyLibrary4Residue[i][k]) { flag=false; break; }
      if(flag) { RN=Residue4Key[i]; break; }
    }
    return RN;
  }

}

#endif

