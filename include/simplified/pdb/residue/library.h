
#ifndef _PDB_Residue_Library_H_
#define _PDB_Residue_Library_H_

#include "pdb/atom/name.h"

namespace mysimulator {

  static const unsigned int ResidueKeySize = ((NumberAtomName-1)>>5)+1;

}

#include "pdb/residue/name.h"

namespace mysimulator {

  struct ResidueLibraryItem {
    unsigned int Key[ResidueKeySize];
    PDBResidueName Value;
  };

  static const ResidueLibraryItem ResidueLibrary[] = {
    { { 0x2F,         0xE220,           0x0       },  PDBResidueName::Ala   },
    { { 0x2100106F,   0x4220C22C,       0x6C00C   },  PDBResidueName::Arg   },
    { { 0x3006F,      0x8000C220,       0x1       },  PDBResidueName::Asn   },
    { { 0x6006F,      0xC220,           0x0       },  PDBResidueName::Asp   },
    { { 0x82F,        0x1C220,          0x0       },  PDBResidueName::Cys   },
    { { 0xC00106F,    0x220C220,        0xC0      },  PDBResidueName::Gln   },
    { { 0x1800106F,   0x220C220,        0x0       },  PDBResidueName::Glu   },
    { { 0xF,          0xC20,            0x0       },  PDBResidueName::Gly   },
    { { 0x420C06F,    0x4400C220,       0x10      },  PDBResidueName::His   },
    { { 0x420C06F,    0x4000C220,       0x30      },  PDBResidueName::His   },
    { { 0x21AF,       0x39D81220,       0x0       },  PDBResidueName::Ile   },
    { { 0x606F,       0xB801C220,       0x3       },  PDBResidueName::Leu   },
    { { 0x10106F,     0x4220C221,       0x1D24    },  PDBResidueName::Lys   },
    { { 0x18006F,     0x220C220,        0x130     },  PDBResidueName::Met   },
    { { 0x18006F,     0x220C240,        0x130     },  PDBResidueName::Met   },
    { { 0x2060606F,   0x4400C220,       0x230     },  PDBResidueName::Phe   },
    { { 0x106F,       0x4220C200,       0x4       },  PDBResidueName::Pro   },
    { { 0x22F,        0x1C220,          0x0       },  PDBResidueName::Ser   },
    { { 0x52F,        0x1C21220,        0x0       },  PDBResidueName::Thr   },
    { { 0xC2C0606F,   0x400C222,        0x11910   },  PDBResidueName::Trp   },
    { { 0x2060606F,   0x4400C230,       0x2030    },  PDBResidueName::Tyr   },
    { { 0x1AF,        0x1DC1220,        0x0       },  PDBResidueName::Val   },
    { { 0x3F,         0xE220,           0x0       },  PDBResidueName::ctAla },
    { { 0x2100107F,   0x4220C22C,       0x6C00C   },  PDBResidueName::ctArg },
    { { 0x3007F,      0x8000C220,       0x1       },  PDBResidueName::ctAsn },
    { { 0x6007F,      0xC220,           0x0       },  PDBResidueName::ctAsp },
    { { 0x83F,        0x1C220,          0x0       },  PDBResidueName::ctCys },
    { { 0xC00107F,    0x220C220,        0xC0      },  PDBResidueName::ctGln },
    { { 0x1800107F,   0x220C220,        0x0       },  PDBResidueName::ctGlu },
    { { 0x1F,         0x0,              0x0       },  PDBResidueName::ctGly },
    { { 0x420C07F,    0x4400C220,       0x10      },  PDBResidueName::ctHis },
    { { 0x420C07F,    0x4000C220,       0x30      },  PDBResidueName::ctHis },
    { { 0x21BF,       0x39D81220,       0x0       },  PDBResidueName::ctIle },
    { { 0x607F,       0xB801C220,       0x3       },  PDBResidueName::ctLeu },
    { { 0x10107F,     0x4220C221,       0x1D24    },  PDBResidueName::ctLys },
    { { 0x18007F,     0x220C220,        0x130     },  PDBResidueName::ctMet },
    { { 0x18007F,     0x220C240,        0x130     },  PDBResidueName::ctMet },
    { { 0x2060607F,   0x4400C220,       0x230     },  PDBResidueName::ctPhe },
    { { 0x107F,       0x4220C200,       0x4       },  PDBResidueName::ctPro },
    { { 0x23F,        0x1C220,          0x0       },  PDBResidueName::ctSer },
    { { 0x53F,        0x1C21220,        0x0       },  PDBResidueName::ctThr },
    { { 0xC2C0607F,   0x400C222,        0x11910   },  PDBResidueName::ctTrp },
    { { 0x2060607F,   0x4400C230,       0x2030    },  PDBResidueName::ctTyr },
    { { 0x1BF,        0x1DC1220,        0x0       },  PDBResidueName::ctVal },
    { { 0x2F,         0xE3C0,           0x0       },  PDBResidueName::ntAla },
    { { 0x2100106F,   0x4220C3CC,       0x6C00C   },  PDBResidueName::ntArg },
    { { 0x3006F,      0x8000C3C0,       0x1       },  PDBResidueName::ntAsn },
    { { 0x6006F,      0xC3C0,           0x0       },  PDBResidueName::ntAsp },
    { { 0x82F,        0x1C3C0,          0x0       },  PDBResidueName::ntCys },
    { { 0xC00106F,    0x220C3C0,        0xC0      },  PDBResidueName::ntGln },
    { { 0x1800106F,   0x220C3C0,        0x0       },  PDBResidueName::ntGlu },
    { { 0xF,          0xDC0,            0x0       },  PDBResidueName::ntGly },
    { { 0x420C06F,    0x4400C3C0,       0x10      },  PDBResidueName::ntHis },
    { { 0x420C06F,    0x4000C3C0,       0x30      },  PDBResidueName::ntHis },
    { { 0x21AF,       0x39D813C0,       0x0       },  PDBResidueName::ntIle },
    { { 0x606F,       0xB801C3C0,       0x3       },  PDBResidueName::ntLeu },
    { { 0x10106F,     0x4220C3C1,       0x1D24    },  PDBResidueName::ntLys },
    { { 0x18006F,     0x220C3C0,        0x130     },  PDBResidueName::ntMet },
    { { 0x2060606F,   0x4400C3C0,       0x230     },  PDBResidueName::ntPhe },
    { { 0x22F,        0x1C3C0,          0x0       },  PDBResidueName::ntSer },
    { { 0x52F,        0x1C213C0,        0x0       },  PDBResidueName::ntThr },
    { { 0xC2C0606F,   0x400C3C2,        0x11910   },  PDBResidueName::ntTrp },
    { { 0x2060606F,   0x4400C3D0,       0x2030    },  PDBResidueName::ntTyr },
    { { 0x1AF,        0x1DC13C0,        0x0       },  PDBResidueName::ntVal }
  };

  static const unsigned int ResidueLibrarySize =
    sizeof(ResidueLibrary) / sizeof(ResidueLibraryItem);

  int __residue_library_id(const unsigned int Key[ResidueKeySize]) {
    bool fg=true;
    unsigned int _mask;
    for(unsigned int i=0;i<ResidueLibrarySize;++i) {
      fg=true;
      for(unsigned int k=0;k<ResidueKeySize;++k) {
        _mask=ResidueLibrary[i].Key[k];
        if((Key[i]|_mask)^_mask)  { fg=false; break; }
      if(fg)  return i;
    }
    return -1;
  }

    int __residue_library_id(const PDBResidueName RN) {
      for(unsigned int i=0;i<ResidueLibrarySize;++i)
        if(ResidueLibrary[i].Value == RN)   return i;
      return -1;
    }

  PDBResidueName ResidueName() (const unsigned int Key[ResidueKeySize]) {
    int id=__residue_library_id(Key);
    return id==-1 ? PDBResidueName::Unknown : ResidueLibrary[id].Value;
  }

}

#endif

