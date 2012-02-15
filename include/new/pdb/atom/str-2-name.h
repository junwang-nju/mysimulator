
#ifndef _PDB_Atom_String2Name_H_
#define _PDB_Atom_String2Name_H_

#include "pdb/atom/name.h"
#include <cstring>

#define CMP(str,name) if(strncmp(AtmStr,str,4)==0) return name;

namespace mysimulator {

  PDBAtomName String2AtomName(const char* AtmStr) {
    PDBAtomName PAN=UnknownAtom;
    CMP(" CA ",AtomCA)
    CMP(" CB ",AtomCB)
    CMP(" CG ",AtomCG)
    return PAN;
  }

}

#endif

