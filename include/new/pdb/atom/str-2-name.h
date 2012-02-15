
#ifndef _PDB_Atom_String2Name_H_
#define _PDB_Atom_String2Name_H_

#include "pdb/atom/name.h"
#include <cstring>

#define ASSIGN(str,name) if(strncmp(AtmStr,str,4)==0) return name;

namespace mysimulator {

  PDBAtomName String2AtomName(const char* AtmStr) {
    PDBAtomName PAN=UnknownAtom;
    ASSIGN(" CA ",AtomCA)
    ASSIGN(" N  ",AtomN)
    ASSIGN(" C  ",AtomC)
    ASSIGN(" O  ",AtomO)
    ASSIGN(" OXT",AtomOXT)
    ASSIGN(" CB ",AtomCB)
    ASSIGN(" CG ",AtomCG)
    ASSIGN(" CG2",AtomCG2)
    ASSIGN(" OG1",AtomOG1)
    ASSIGN(" CD ",AtomCD)
    ASSIGN(" CD1",AtomCD1)
    ASSIGN(" CD2",AtomCD2)
    ASSIGN(" OD1",AtomOD1)
    ASSIGN(" OD2",AtomOD2)
    ASSIGN(" CE ",AtomCE)
    ASSIGN(" NE ",AtomNE)
    ASSIGN(" OE1",AtomOE1)
    ASSIGN(" OE2",AtomOE2)
    ASSIGN(" CZ ",AtomCZ)
    ASSIGN(" NZ ",AtomNZ)
    ASSIGN(" NH1",AtomNH1)
    ASSIGN(" NH2",AtomNH2)
    ASSIGN(" H  ",AtomH)
    ASSIGN(" HA ",AtomHA)
    ASSIGN(" HA2",AtomHA2)
    ASSIGN(" HA3",AtomHA3)
    ASSIGN(" HB ",AtomHB)
    return PAN;
  }

}

#undef ASSIGN

#endif

