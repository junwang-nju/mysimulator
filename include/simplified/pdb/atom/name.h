
#ifndef _PDB_Atom_Name_H_
#define _PDB_Atom_Name_H_

namespace mysimulator {

  enum class PDBAtomName : unsigned int {
    CA      = 0,
    N,
    C,
    O,
    OXT,
    CB,
    CG,
    CG1,
    CG2,
    OG,
    OG1,
    SG,
    CD,
    CD1,
    CD2,
    ND1,
    ND2,
    OD1,
    OD2,
    SD,
    CE,
    CE1,
    CE2,
    CE3,
    NE,
    NE1,
    NE2,
    OE1,
    OE2,
    CZ,
    CZ2,
    CZ3,
    NZ,
    CH2,
    NH1,
    NH2,
    OH,
    NumberHeavyAtomName,
    H           = NumberHeavyAtomName,
    H1,
    H2,
    H3,
    HA,
    HA2,
    HA3,
    HB,
    HB1,
    HB2,
    HB3,
    HG,
    HG1,
    HG11,
    HG12,
    HG13,
    HG2,
    HG21,
    HG22,
    HG23,
    HG3,
    HD1,
    HD11,
    HD12,
    HD13,
    HD2,
    HD21,
    HD22,
    HD23,
    HD3,
    HE,
    HE1,
    HE2,
    HE21,
    HE22,
    HE3,
    HZ,
    HZ1,
    HZ2,
    HZ3,
    HH,
    HH11,
    HH12,
    HH2,
    HH21,
    HH22,
    HXT,
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
      case PDBAtomName::CA:
      case PDBAtomName::N:
      case PDBAtomName::C:
      case PDBAtomName::O:
      case PDBAtomName::OXT:
      case PDBAtomName::H:
      case PDBAtomName::H1:
      case PDBAtomName::H2:
      case PDBAtomName::H3:
      case PDBAtomName::HA:
      case PDBAtomName::HA2:
      case PDBAtomName::HA3:
        fg=true;
        break;
      default:
        fg=false;
    }
    return fg;
  }

}

#endif

