
#ifndef _PDB_ATOM_Name_H_
#define _PDB_ATOM_Name_H_

namespace mysimulator {

  enum PDBAtomName {
    AtomCA=0,       // 0
    AtomN,          // 1
    AtomC,          // 2
    AtomO,          // 3
    AtomOXT,        // 4
    AtomCB,         // 5
    AtomCG,         // 6
    AtomCG1,        // 7
    AtomCG2,        // 8
    AtomOG,         // 9
    AtomOG1,        // 10
    AtomSG,         // 11
    AtomCD,         // 12
    AtomCD1,        // 13
    AtomCD2,        // 14
    AtomND1,        // 15
    AtomND2,        // 16
    AtomOD1,        // 17
    AtomOD2,        // 18
    AtomSD,         // 19
    AtomCE,         // 20
    AtomCE1,        // 21
    AtomCE2,        // 22
    AtomCE3,        // 23
    AtomNE,         // 24
    AtomNE1,        // 25
    AtomNE2,        // 26
    AtomOE1,        // 27
    AtomOE2,        // 28
    AtomCZ,         // 29
    AtomCZ2,        // 30
    AtomCZ3,        // 31
    AtomNZ,         // 32
    AtomCH2,        // 33
    AtomNH1,        // 34
    AtomNH2,        // 35
    AtomOH,         // 36
    NumberHeavyAtomNames,
    AtomH=NumberHeavyAtomNames,     //  37
    AtomH1,                         //  38
    AtomH2,                         //  39
    AtomH3,                         //  40
    AtomHA,                         //  41
    AtomHA2,                        //  42
    AtomHA3,                        //  43
    AtomHB,                         //  44
    AtomHB1,                        //  45
    AtomHB2,                        //  46
    AtomHB3,                        //  47
    AtomHG,                         //  48
    AtomHG1,                        //  49
    AtomHG11,                       //  50
    AtomHG12,                       //  51
    AtomHG13,                       //  52
    AtomHG2,                        //  53
    AtomHG21,                       //  54
    AtomHG22,                       //  55
    AtomHG23,                       //  56
    AtomHG3,                        //  57
    AtomHD1,                        //  58
    AtomHD11,                       //  59
    AtomHD12,                       //  60
    AtomHD13,                       //  61
    AtomHD2,                        //  62
    AtomHD21,                       //  63
    AtomHD22,                       //  64
    AtomHD23,                       //  65
    AtomHD3,                        //  66
    AtomHE,                         //  67
    AtomHE1,                        //  68
    AtomHE2,                        //  69
    AtomHE21,                       //  70
    AtomHE22,                       //  71
    AtomHE3,                        //  72
    AtomHZ,                         //  73
    AtomHZ1,                        //  74
    AtomHZ2,                        //  75
    AtomHZ3,                        //  76
    AtomHH,                         //  77
    AtomHH11,                       //  78
    AtomHH12,                       //  79
    AtomHH2,                        //  80
    AtomHH21,                       //  81
    AtomHH22,                       //  82
    AtomHXT,                        //  83
    NumberAtomNames,
    UnknownAtom
  };

  bool IsHeavyAtom(const PDBAtomName& PAN) { return PAN<NumberHeavyAtomNames; }

}

#endif

