
#ifndef _PDB_Property_Atom_Import_H_
#define _PDB_Property_Atom_Import_H_

#include "pdb/property/atom/interface.h"
#include "pdb/property/identify.h"

namespace mysimulator {

  void import(PDBAtom& A, const char* content) {
    unsigned int natom;
    natom=0;
    char* line=content;
    unsigned int lsize;
    lsize=LineSize(line);
    while(line!=NULL) {
      if(identifyPDBProperty(line)==PDBATOM)  ++natom;
    }
  }

}

#endif

