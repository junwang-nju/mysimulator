
#ifndef _PDB_Residue_Key_Library_H_
#define _PDB_Residue_Key_Library_H_

#include "pdb-atom/name.h"

namespace mysimulator {

  static const unsigned int NumberResidueKey=(NumberAtomNames-1)/32+1;
  //static const unsigned int ResidueKeyLibrarySize=63;

  static const unsigned int
  ResidueKeyLibrary[][NumberResidueKey] = {
      {   0x2F,         0xE220,       0x0   },      // Ala
      {   0x2100106F,   0x4220C22C,   0x6C00C   },  // Arg
      {   0x3006F,      0x8000C220,   0x1   },      // Asn
      {   0x6006F,      0xC220,       0x0   },      // Asp
      {   0x82F,        0x1C220,      0x0   },      // Cys
      {   0xC00106F,    0x220C220,    0xC0  },      // Gln
      {   0x1800106F,   0x220C220,    0x0   },      // Glu
      {   0xF,          0xC20,        0x0   },      // Gly
      {   0x420C06F,    0x4400C220,   0x10  },      // His
      {   0x420C06F,    0x4000C220,   0x30  },      // His
      {   0x21AF,       0x39D81220,   0x0   },      // Ile
      {   0x606F,       0xB801C220,   0x3   },      // Leu
      {   0x10106F,     0x4220C221,   0x1D24},      // Lys
      {   0x18006F,     0x220C220,    0x130 },      // Met
      {   0x18006F,     0x220C240,    0x130 },      // Met
      {   0x2060606F,   0x4400C220,   0x230 },      // Phe
      {   0x106F,       0x4220C200,   0x4   },      // Pro
      {   0x22F,        0x1C220,      0x0   },      // Ser
      {   0x52F,        0x1C21220,    0x0   },      // Thr
      {   0xC2C0606F,   0x400C222,    0x11910   },  // Trp
      {   0x2060606F,   0x4400C230,   0x2030},      // Tyr
      {   0x1AF,        0x1DC1220,    0x0   },      // Val
      {   0x3F,         0xE220,       0x0   },      // ctAla
      {   0x2100107F,   0x4220C22C,   0x6C00C   },  // ctArg
      {   0x3007F,      0x8000C220,   0x1   },      // ctAsn
      {   0x6007F,      0xC220,       0x0   },      // ctAsp
      {   0x83F,        0x1C220,      0x0   },      // ctCys
      {   0xC00107F,    0x220C220,    0xC0  },      // ctGln
      {   0x1800107F,   0x220C220,    0x0   },      // ctGlu
      {   0x1F,         0x0,          0x0   },      // ctGly
      {   0x420C07F,    0x4400C220,   0x10  },      // ctHis
      {   0x420C07F,    0x4000C220,   0x30  },      // ctHis
      {   0x21BF,       0x39D81220,   0x0   },      // ctIle
      {   0x607F,       0xB801C220,   0x3   },      // ctLeu
      {   0x10107F,     0x4220C221,   0x1D24},      // ctLys
      {   0x18007F,     0x220C220,    0x130 },      // ctMet
      {   0x18007F,     0x220C240,    0x130 },      // ctMet
      {   0x2060607F,   0x4400C220,   0x230 },      // ctPhe
      {   0x107F,       0x4220C200,   0x4   },      // ctPro
      {   0x23F,        0x1C220,      0x0   },      // ctSer
      {   0x53F,        0x1C21220,    0x0   },      // ctThr
      {   0xC2C0607F,   0x400C222,    0x11910   },  // ctTrp
      {   0x2060607F,   0x4400C230,   0x2030},      // ctTyr
      {   0x1BF,        0x1DC1220,    0x0   },      // ctVal
      {   0x2F,         0xE3C0,       0x0   },      // ntAla
      {   0x2100106F,   0x4220C3CC,   0x6C00C   },  // ntArg
      {   0x3006F,      0x8000C3C0,   0x1   },      // ntAsn
      {   0x6006F,      0xC3C0,       0x0   },      // ntAsp
      {   0x82F,        0x1C3C0,      0x0   },      // ntCys
      {   0xC00106F,    0x220C3C0,    0xC0  },      // ntGln
      {   0x1800106F,   0x220C3C0,    0x0   },      // ntGlu
      {   0xF,          0xDC0,        0x0   },      // ntGly
      {   0x420C06F,    0x4400C3C0,   0x10  },      // ntHis
      {   0x420C06F,    0x4000C3C0,   0x30  },      // ntHis
      {   0x21AF,       0x39D813C0,   0x0   },      // ntIle
      {   0x606F,       0xB801C3C0,   0x3   },      // ntLeu
      {   0x10106F,     0x4220C3C1,   0x1D24},      // ntLys
      {   0x18006F,     0x220C3C0,    0x130 },      // ntMet
      {   0x2060606F,   0x4400C3C0,   0x230 },      // ntPhe
      {   0x22F,        0x1C3C0,      0x0   },      // ntSer
      {   0x52F,        0x1C213C0,    0x0   },      // ntThr
      {   0xC2C0606F,   0x400C3C2,    0x11910   },  // ntTrp
      {   0x2060606F,   0x4400C3D0,   0x2030},      // ntTyr
      {   0x1AF,        0x1DC13C0,    0x0   }       // ntVal
  };

}

#endif

