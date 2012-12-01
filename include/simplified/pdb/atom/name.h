
#ifndef _PDB_Atom_Name_H_
#define _PDB_Atom_Name_H_

namespace mysimulator {

  enum class PDBAtomName : unsigned int {
    AtomCA      = 0,
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
    NumberHeavyAtomName,
    AtomH           = NumberHeavyAtomName,
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
    NumberAtomName,
    Unknown
  };

  static const unsigned int NumberHeavyAtomName =
    (unsigned int)(PDBAtomName::NumberHeavyAtomName);

  static const unsigned int NumberAtomName =
    (unsigned int)(PDBAtomName::NumberAtomName);

  bool __is_heavy_atom(const PDBAtomName& AN) {
    return AN<PDBAtomName::NumberHeavyAtomName;
  }

  bool __is_backbone(const PDBAtomName& AN) {
    bool fg;
    switch(AN) {
      case PDBAtomName::AtomCA:
      case PDBAtomName::AtomN:
      case PDBAtomName::AtomC:
      case PDBAtomName::AtomO:
      case PDBAtomName::AtomOXT:
      case PDBAtomName::AtomH:
      case PDBAtomName::AtomH1:
      case PDBAtomName::AtomH2:
      case PDBAtomName::AtomH3:
      case PDBAtomName::AtomHA:
      case PDBAtomName::AtomHA2:
      case PDBAtomName::AtomHA3:
        fg=true;
        break;
      default:
        fg=false;
    }
    return fg;
  }

}

#endif

