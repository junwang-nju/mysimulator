
#ifndef _PDB_Residue_AtomLibrary_H_
#define _PDB_Residue_AtomLibrary_H_

#include "pdb/residue/name.h"

namespace mysimulator {

  static const unsigned int
  AtomStart4Residue[NumberResidueNames] = {
    0,    10,   34,   48,   60,   71,   88,   103,  110,  128,
    147,  166,  188,  206,  226,  240,  251,  265,  288,  309,
    325,  337,  363,  379,  393,  406,  425,  442,  451,  471,
    492,  513,  537,  557,  579,  595,  608,  624,  649,  672,
    690,  702,  728,  744,  758,  771,  790,  807,  816,  836,
    857,  878,  902,  922,  944,  960,  973,  989,  1014, 1037
  };

  static const unsigned int ResidueSize[NumberResidueNames] = {
    10,   24,   14,   12,   11,   17,   15,   7,    18,   19,
    19,   22,   18,   20,   14,   11,   14,   23,   21,   16,
    12,   26,   16,   14,   13,   19,   17,   9,    20,   21,
    21,   24,   20,   22,   16,   13,   16,   25,   23,   18,
    12,   26,   16,   14,   13,   19,   17,   9,    20,   21,
    21,   24,   20,   22,   16,   13,   16,   25,   23,   18
  };

}

#include "pdb/atom/name.h"

namespace mysimulator {

  static const PDBAtomName Atoms4Residue[] = {
    AtomCA,       // Start Ala
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomH,
    AtomHA,
    AtomHB1,
    AtomHB2,
    AtomHB3,      // End Ala
    AtomCA,       // Start Arg
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomNE,
    AtomCZ,
    AtomNH1,
    AtomNH2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,
    AtomHE,
    AtomHH11,
    AtomHH12,
    AtomHH21,
    AtomHH22,     // End Arg
    AtomCA,       // Start Asn
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomOD1,
    AtomND2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD21,
    AtomHD22,     // End Asn
    AtomCA,       // Start Asp
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomOD1,
    AtomOD2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,      // End Asp
    AtomCA,       // Start Cys
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomSG,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,       // End Cys
    AtomCA,       // Start Gln,
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomOE1,
    AtomNE2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHE21,
    AtomHE22,     // End Gln
    AtomCA,       // Start Glu
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomOE1,
    AtomOE2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,      //End Glu,
    AtomCA,       // Start Gly
    AtomN,
    AtomC,
    AtomO,
    AtomH,
    AtomHA2,
    AtomHA3,      // End Gly
    AtomCA,       // Start His
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomND1,
    AtomND2,
    AtomCE1,
    AtomNE2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,      // End His
    AtomCA,       // Start ILE
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG1,
    AtomCG2,
    AtomCD1,
    AtomH,
    AtomHA,
    AtomHB,
    AtomHG12,
    AtomHG13,
    AtomHG21,
    AtomHG22,
    AtomHG23,
    AtomHD11,
    AtomHD12,
    AtomHD13,     // End ILE
    AtomCA,       // Start LEU
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,
    AtomHD11,
    AtomHD12,
    AtomHD13,
    AtomHD21,
    AtomHD22,
    AtomHD23,     // End Leu
    AtomCA,       // Start Lys
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomCE,
    AtomNZ,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,
    AtomHE2,
    AtomHE3,
    AtomHZ1,
    AtomHZ2,
    AtomHZ3,      // End Lys
    AtomCA,       // Start Met
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomSD,
    AtomCE,
    AtomH,
    AtomH1,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHE1,
    AtomHE2,
    AtomHE3,      // End Met
    AtomCA,       // Start Phe,
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomCE1,
    AtomCE2,
    AtomCZ,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,
    AtomHZ,       // End Phe
    AtomCA,       // Start Pro
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,      // End Pro
    AtomCA,       // Start Ser
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomOG,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,       // End Ser
    AtomCA,       // Start Thr
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomOG1,
    AtomCG2,
    AtomH,
    AtomHA,
    AtomHB,
    AtomHG1,
    AtomHG21,
    AtomHG22,
    AtomHG23,     // End Thr
    AtomCA,       // Start Trp
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomNE1,
    AtomCE2,
    AtomCZ2,
    AtomCZ3,
    AtomCH2,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHE1,
    AtomHE3,
    AtomHZ2,
    AtomHZ3,
    AtomHH2,        // End Trp
    AtomCA,         // Start Tyr
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomCE1,
    AtomCE2,
    AtomCZ,
    AtomOH,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,
    AtomHH,         // End Tyr
    AtomCA,         // Start Val
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG1,
    AtomCG2,
    AtomH,
    AtomHA,
    AtomHB,
    AtomHG11,
    AtomHG12,
    AtomHG13,
    AtomHG21,
    AtomHG22,
    AtomHG23,       // End Val
    AtomCA,         // Start ctAla
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB1,
    AtomHB2,
    AtomHB3,      // End ctAla
    AtomCA,       // Start ctArg
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomNE,
    AtomCZ,
    AtomNH1,
    AtomNH2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,
    AtomHE,
    AtomHH11,
    AtomHH12,
    AtomHH21,
    AtomHH22,     // End ctArg
    AtomCA,       // Start ctAsn
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomOD1,
    AtomND2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD21,
    AtomHD22,     // End ctAsn
    AtomCA,       // Start ctAsp
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomOD1,
    AtomOD2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,      // End ctAsp
    AtomCA,       // Start ctCys
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomSG,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,       // End ctCys
    AtomCA,       // Start ctGln,
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomOE1,
    AtomNE2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHE21,
    AtomHE22,     // End ctGln
    AtomCA,       // Start ctGlu
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomOE1,
    AtomOE2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,      //End ctGlu,
    AtomCA,       // Start ctGly
    AtomN,
    AtomC,
    AtomO,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA2,
    AtomHA3,      // End ctGly
    AtomCA,       // Start ctHis
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomND1,
    AtomND2,
    AtomCE1,
    AtomNE2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,      // End ctHis
    AtomCA,       // Start ctILE
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG1,
    AtomCG2,
    AtomCD1,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB,
    AtomHG12,
    AtomHG13,
    AtomHG21,
    AtomHG22,
    AtomHG23,
    AtomHD11,
    AtomHD12,
    AtomHD13,     // End ctILE
    AtomCA,       // Start ctLEU
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,
    AtomHD11,
    AtomHD12,
    AtomHD13,
    AtomHD21,
    AtomHD22,
    AtomHD23,     // End ctLeu
    AtomCA,       // Start ctLys
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomCE,
    AtomNZ,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,
    AtomHE2,
    AtomHE3,
    AtomHZ1,
    AtomHZ2,
    AtomHZ3,      // End ctLys
    AtomCA,       // Start ctMet
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomSD,
    AtomCE,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomH1,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHE1,
    AtomHE2,
    AtomHE3,      // End ctMet
    AtomCA,       // Start ctPhe,
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomCE1,
    AtomCE2,
    AtomCZ,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,
    AtomHZ,       // End ctPhe
    AtomCA,       // Start ctPro
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomOXT,
    AtomHXT,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,      // End ctPro
    AtomCA,       // Start ctSer
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomOG,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,       // End ctSer
    AtomCA,       // Start ctThr
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomOG1,
    AtomCG2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB,
    AtomHG1,
    AtomHG21,
    AtomHG22,
    AtomHG23,     // End ctThr
    AtomCA,       // Start ctTrp
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomNE1,
    AtomCE2,
    AtomCZ2,
    AtomCZ3,
    AtomCH2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHE1,
    AtomHE3,
    AtomHZ2,
    AtomHZ3,
    AtomHH2,        // End ctTrp
    AtomCA,         // Start ctTyr
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomCE1,
    AtomCE2,
    AtomCZ,
    AtomOH,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,
    AtomHH,         // End ctTyr
    AtomCA,         // Start ctVal
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG1,
    AtomCG2,
    AtomOXT,
    AtomHXT,
    AtomH,
    AtomHA,
    AtomHB,
    AtomHG11,
    AtomHG12,
    AtomHG13,
    AtomHG21,
    AtomHG22,
    AtomHG23,       // End ctVal
    AtomCA,       // Start ntAla
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB1,
    AtomHB2,
    AtomHB3,      // End ntAla
    AtomCA,       // Start ntArg
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomNE,
    AtomCZ,
    AtomNH1,
    AtomNH2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,
    AtomHE,
    AtomHH11,
    AtomHH12,
    AtomHH21,
    AtomHH22,     // End ntArg
    AtomCA,       // Start ntAsn
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomOD1,
    AtomND2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD21,
    AtomHD22,     // End ntAsn
    AtomCA,       // Start ntAsp
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomOD1,
    AtomOD2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,      // End ntAsp
    AtomCA,       // Start ntCys
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomSG,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,       // End ntCys
    AtomCA,       // Start ntGln,
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomOE1,
    AtomNE2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHE21,
    AtomHE22,     // End ntGln
    AtomCA,       // Start ntGlu
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomOE1,
    AtomOE2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,      //End ntGlu,
    AtomCA,       // Start ntGly
    AtomN,
    AtomC,
    AtomO,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA2,
    AtomHA3,      // End ntGly
    AtomCA,       // Start ntHis
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomND1,
    AtomND2,
    AtomCE1,
    AtomNE2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,      // End ntHis
    AtomCA,       // Start ntILE
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG1,
    AtomCG2,
    AtomCD1,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB,
    AtomHG12,
    AtomHG13,
    AtomHG21,
    AtomHG22,
    AtomHG23,
    AtomHD11,
    AtomHD12,
    AtomHD13,     // End ntILE
    AtomCA,       // Start ntLEU
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,
    AtomHD11,
    AtomHD12,
    AtomHD13,
    AtomHD21,
    AtomHD22,
    AtomHD23,     // End ntLeu
    AtomCA,       // Start ntLys
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomCE,
    AtomNZ,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,
    AtomHE2,
    AtomHE3,
    AtomHZ1,
    AtomHZ2,
    AtomHZ3,      // End ntLys
    AtomCA,       // Start ntMet
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomSD,
    AtomCE,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomH1,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHE1,
    AtomHE2,
    AtomHE3,      // End ntMet
    AtomCA,       // Start ntPhe,
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomCE1,
    AtomCE2,
    AtomCZ,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,
    AtomHZ,       // End ntPhe
    AtomCA,       // Start ntPro
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD,
    AtomH1,
    AtomH2,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG2,
    AtomHG3,
    AtomHD2,
    AtomHD3,      // End ntPro
    AtomCA,       // Start ntSer
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomOG,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHG,       // End ntSer
    AtomCA,       // Start ntThr
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomOG1,
    AtomCG2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB,
    AtomHG1,
    AtomHG21,
    AtomHG22,
    AtomHG23,     // End ntThr
    AtomCA,       // Start ntTrp
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomNE1,
    AtomCE2,
    AtomCZ2,
    AtomCZ3,
    AtomCH2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHE1,
    AtomHE3,
    AtomHZ2,
    AtomHZ3,
    AtomHH2,        // End ntTrp
    AtomCA,         // Start ntTyr
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG,
    AtomCD1,
    AtomCD2,
    AtomCE1,
    AtomCE2,
    AtomCZ,
    AtomOH,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB2,
    AtomHB3,
    AtomHD1,
    AtomHD2,
    AtomHE1,
    AtomHE2,
    AtomHH,         // End ntTyr
    AtomCA,         // Start ntVal
    AtomN,
    AtomC,
    AtomO,
    AtomCB,
    AtomCG1,
    AtomCG2,
    AtomH1,
    AtomH2,
    AtomH3,
    AtomHA,
    AtomHB,
    AtomHG11,
    AtomHG12,
    AtomHG13,
    AtomHG21,
    AtomHG22,
    AtomHG23        // End ntVal
  };

}

#endif

