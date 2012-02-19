
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
    ASSIGN(" CG1",AtomCG1)
    ASSIGN(" CG2",AtomCG2)
    ASSIGN(" OG ",AtomOG)
    ASSIGN(" OG1",AtomOG1)
    ASSIGN(" SG ",AtomSG)
    ASSIGN(" CD ",AtomCD)
    ASSIGN(" CD1",AtomCD1)
    ASSIGN(" CD2",AtomCD2)
    ASSIGN(" ND1",AtomND1)
    ASSIGN(" ND2",AtomND2)
    ASSIGN(" OD1",AtomOD1)
    ASSIGN(" OD2",AtomOD2)
    ASSIGN(" SD ",AtomSD)
    ASSIGN(" CE ",AtomCE)
    ASSIGN(" CE1",AtomCE1)
    ASSIGN(" CE2",AtomCE2)
    ASSIGN(" CE3",AtomCE3)
    ASSIGN(" NE ",AtomNE)
    ASSIGN(" NE1",AtomNE1)
    ASSIGN(" NE2",AtomNE2)
    ASSIGN(" OE1",AtomOE1)
    ASSIGN(" OE2",AtomOE2)
    ASSIGN(" CZ ",AtomCZ)
    ASSIGN(" CZ2",AtomCZ2)
    ASSIGN(" CZ3",AtomCZ3)
    ASSIGN(" NZ ",AtomNZ)
    ASSIGN(" CH2",AtomCH2)
    ASSIGN(" NH1",AtomNH1)
    ASSIGN(" NH2",AtomNH2)
    ASSIGN(" OH ",AtomOH)
    ASSIGN(" H  ",AtomH)
    ASSIGN(" H1 ",AtomH1)
    ASSIGN(" H2 ",AtomH2)
    ASSIGN(" H3 ",AtomH3)
    ASSIGN(" HA ",AtomHA)
    ASSIGN(" HA2",AtomHA2)
    ASSIGN(" HA3",AtomHA3)
    ASSIGN(" HB ",AtomHB)
    ASSIGN(" HB1",AtomHB1)
    ASSIGN(" HB2",AtomHB2)
    ASSIGN(" HB3",AtomHB3)
    ASSIGN(" HG ",AtomHG)
    ASSIGN(" HG1",AtomHG1)
    ASSIGN("HG11",AtomHG11)
    ASSIGN("HG12",AtomHG12)
    ASSIGN("HG13",AtomHG13)
    ASSIGN(" HG2",AtomHG2)
    ASSIGN("HG21",AtomHG21)
    ASSIGN("HG22",AtomHG22)
    ASSIGN("HG23",AtomHG23)
    ASSIGN(" HG3",AtomHG3)
    ASSIGN(" HD1",AtomHD1)
    ASSIGN("HD11",AtomHD11)
    ASSIGN("HD12",AtomHD12)
    ASSIGN("HD13",AtomHD13)
    ASSIGN(" HD2",AtomHD2)
    ASSIGN("HD21",AtomHD21)
    ASSIGN("HD22",AtomHD22)
    ASSIGN("HD23",AtomHD23)
    ASSIGN(" HD3",AtomHD3)
    ASSIGN(" HE ",AtomHE)
    ASSIGN(" HE1",AtomHE1)
    ASSIGN(" HE2",AtomHE2)
    ASSIGN("HE21",AtomHE21)
    ASSIGN("HE22",AtomHE22)
    ASSIGN(" HE3",AtomHE3)
    ASSIGN(" HZ ",AtomHZ)
    ASSIGN(" HZ1",AtomHZ1)
    ASSIGN(" HZ2",AtomHZ2)
    ASSIGN(" HZ3",AtomHZ3)
    ASSIGN(" HH ",AtomHH)
    ASSIGN("HH11",AtomHH11)
    ASSIGN("HH12",AtomHH12)
    ASSIGN(" HH2",AtomHH2)
    ASSIGN("HH21",AtomHH21)
    ASSIGN("HH22",AtomHH22)
    return PAN;
  }

}

#undef ASSIGN

#endif

