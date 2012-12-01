
#ifndef _PDB_IO_Atom_Name_H_
#define _PDB_IO_Atom_Name_H_

#include "pdb/atom/name.h"
#include <cstring>

namespace mysimulator {

  struct AtomNameLibraryItem {
    char Key[5];
    PDBAtomName Value;
  };

  static const AtomNameLibrary[] = {
    { " CA ",   AtomCA    },
    { " N  ",   AtomN     },
    { " C  ",   AtomC     },
    { " O  ",   AtomO     },
    { " OXT",   AtomOXT   },
    { " CB ",   AtomCB    },
    { " CG ",   AtomCG    },
    { " CG1",   AtomCG1   },
    { " CG2",   AtomCG2   },
    { " OG ",   AtomOG    },
    { " OG1",   AtomOG1   },
    { " SG ",   AtomSG    },
    { " CD ",   AtomCD    },
    { " CD1",   AtomCD1   },
    { " CD2",   AtomCD2   },
    { " ND1",   AtomND1   },
    { " ND2",   AtomND2   },
    { " OD1",   AtomOD1   },
    { " OD2",   AtomOD2   },
    { " SD ",   AtomSD    },
    { " CE ",   AtomCE    },
    { " CE1",   AtomCE1   },
    { " CE2",   AtomCE2   },
    { " CE3",   AtomCE3   },
    { " NE ",   AtomNE    },
    { " NE1",   AtomNE1   },
    { " NE2",   AtomNE2   },
    { " OE1",   AtomOE1   },
    { " OE2",   AtomOE2   },
    { " CZ ",   AtomCZ    },
    { " CZ2",   AtomCZ2   },
    { " CZ3",   AtomCZ3   },
    { " NZ ",   AtomNZ    },
    { " CH2",   AtomCH2   },
    { " NH1",   AtomNH1   },
    { " NH2",   AtomNH2   },
    { " OH ",   AtomOH    },
    { " H  ",   AtomH     },
    { " H1 ",   AtomH1    },
    { " H2 ",   AtomH2    },
    { " H3 ",   AtomH3    },
    { " HA ",   AtomHA    },
    { " HA2",   AtomHA2   },
    { " HA3",   AtomHA3   },
    { " HB ",   AtomHB    },
    { " HB1",   AtomHB1   },
    { " HB2",   AtomHB2   },
    { " HB3",   AtomHB3   },
    { " HG ",   AtomHG    },
    { " HG1",   AtomHG1   },
    { "HG11",   AtomHG11  },
    { "HG12",   AtomHG12  },
    { "HG13",   AtomHG13  },
    { " HG2",   AtomHG2   },
    { "HG21",   AtomHG21  },
    { "HG22",   AtomHG22  },
    { "HG23",   AtomHG23  },
    { " HG3",   AtomHG3   },
    { " HD1",   AtomHD1   },
    { "HD11",   AtomHD11  },
    { "HD12",   AtomHD12  },
    { "HD13",   AtomHD13  },
    { " HD2",   AtomHD2   },
    { "HD21",   AtomHD21  },
    { "HD22",   AtomHD22  },
    { "HD23",   AtomHD23  },
    { " HD3",   AtomHD3   },
    { " HE ",   AtomHE    },
    { " HE1",   AtomHE1   },
    { " HE2",   AtomHE2   },
    { "HE21",   AtomHE21  },
    { "HE22",   AtomHE22  },
    { " HE3",   AtomHE3   },
    { " HZ ",   AtomHZ    },
    { " HZ1",   AtomHZ1   },
    { " HZ2",   AtomHZ2   },
    { " HZ3",   AtomHZ3   },
    { " HH ",   AtomHH    },
    { "HH11",   AtomHH11  },
    { "HH12",   AtomHH12  },
    { " HH2",   AtomHH2   },
    { "HH21",   AtomHH21  },
    { "HH22",   AtomHH22  }
  };

  static const unsigned int AtomNameLibrarySize =
    sizeof(AtomNameLibrary) / sizeof(AtomNameLibraryItem);

}

#include "pdb/io/record-name.h"
#include "basic/util/string.h"

namespace mysimulator {

  PDBAtomName AtomName(const char* _rec) {
    assert(RecordName(_rec) == PDBRecordName::ATOM);
    char str[6];
    SubString(str,_rec,12,15);
    for(unsigned int i=0;i<AtomNameLibrarySize;++i)
      if(strncmp(str,AtomNameLibrary[i].Key,4)==0)
        return AtomNameLibrary[i].Value;
    return PDBAtomName::Unknown;
  }

}

#endif

