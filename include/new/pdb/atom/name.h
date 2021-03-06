
#ifndef _PDB_Atom_Name_H_
#define _PDB_Atom_Name_H_

namespace mysimulator {

  enum PDBAtomName {
    AtomCA=0,
    AtomN,
    AtomC,
    AtomO,
    AtomOXT,
    AtomCB,
    AtomCG,
    AtomCG1,
    AtomCG2,
    AtomOG,
    AtomOG1,
    AtomSG,
    AtomCD,
    AtomCD1,
    AtomCD2,
    AtomND1,
    AtomND2,
    AtomOD1,
    AtomOD2,
    AtomSD,
    AtomCE,
    AtomCE1,
    AtomCE2,
    AtomCE3,
    AtomNE,
    AtomNE1,
    AtomNE2,
    AtomOE1,
    AtomOE2,
    AtomCZ,
    AtomCZ2,
    AtomCZ3,
    AtomNZ,
    AtomCH2,
    AtomNH1,
    AtomNH2,
    AtomOH,
    NumberHeavyAtomNames,
    AtomH=NumberHeavyAtomNames,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHA2,
    AtomHA3,
    AtomHB,
    AtomHB1,
    AtomHB2,
    AtomHB3,
    AtomHG,
    AtomHG1,
    AtomHG11,
    AtomHG12,
    AtomHG13,
    AtomHG2,
    AtomHG21,
    AtomHG22,
    AtomHG23,
    AtomHG3,
    AtomHD1,
    AtomHD11,
    AtomHD12,
    AtomHD13,
    AtomHD2,
    AtomHD21,
    AtomHD22,
    AtomHD23,
    AtomHD3,
    AtomHE,
    AtomHE1,
    AtomHE2,
    AtomHE21,
    AtomHE22,
    AtomHE3,
    AtomHZ,
    AtomHZ1,
    AtomHZ2,
    AtomHZ3,
    AtomHH,
    AtomHH11,
    AtomHH12,
    AtomHH2,
    AtomHH21,
    AtomHH22,
    AtomHXT,
    NumberAtomNames,
    UnknownAtom
  };

  bool IsHeavyAtom(const PDBAtomName& PAN) { return PAN<NumberHeavyAtomNames; }

}

#endif

