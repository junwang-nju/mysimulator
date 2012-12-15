
#ifndef _PDB_IO_Atom_Name_H_
#define _PDB_IO_Atom_Name_H_

#include "pdb/atom/name.h"
#include <cstring>

namespace mysimulator {

  struct AtomNameLibraryItem {
    char Key[5];
    PDBAtomName Value;
  };

  static const AtomNameLibraryItem AtomNameLibrary[] = {
    { " CA ",   PDBAtomName::CA    },
    { " N  ",   PDBAtomName::N     },
    { " C  ",   PDBAtomName::C     },
    { " O  ",   PDBAtomName::O     },
    { " OXT",   PDBAtomName::OXT   },
    { " CB ",   PDBAtomName::CB    },
    { " CG ",   PDBAtomName::CG    },
    { " CG1",   PDBAtomName::CG1   },
    { " CG2",   PDBAtomName::CG2   },
    { " OG ",   PDBAtomName::OG    },
    { " OG1",   PDBAtomName::OG1   },
    { " SG ",   PDBAtomName::SG    },
    { " CD ",   PDBAtomName::CD    },
    { " CD1",   PDBAtomName::CD1   },
    { " CD2",   PDBAtomName::CD2   },
    { " ND1",   PDBAtomName::ND1   },
    { " ND2",   PDBAtomName::ND2   },
    { " OD1",   PDBAtomName::OD1   },
    { " OD2",   PDBAtomName::OD2   },
    { " SD ",   PDBAtomName::SD    },
    { " CE ",   PDBAtomName::CE    },
    { " CE1",   PDBAtomName::CE1   },
    { " CE2",   PDBAtomName::CE2   },
    { " CE3",   PDBAtomName::CE3   },
    { " NE ",   PDBAtomName::NE    },
    { " NE1",   PDBAtomName::NE1   },
    { " NE2",   PDBAtomName::NE2   },
    { " OE1",   PDBAtomName::OE1   },
    { " OE2",   PDBAtomName::OE2   },
    { " CZ ",   PDBAtomName::CZ    },
    { " CZ2",   PDBAtomName::CZ2   },
    { " CZ3",   PDBAtomName::CZ3   },
    { " NZ ",   PDBAtomName::NZ    },
    { " CH2",   PDBAtomName::CH2   },
    { " NH1",   PDBAtomName::NH1   },
    { " NH2",   PDBAtomName::NH2   },
    { " OH ",   PDBAtomName::OH    },
    { " H  ",   PDBAtomName::H     },
    { " H1 ",   PDBAtomName::H1    },
    { " H2 ",   PDBAtomName::H2    },
    { " H3 ",   PDBAtomName::H3    },
    { " HA ",   PDBAtomName::HA    },
    { " HA2",   PDBAtomName::HA2   },
    { " HA3",   PDBAtomName::HA3   },
    { " HB ",   PDBAtomName::HB    },
    { " HB1",   PDBAtomName::HB1   },
    { " HB2",   PDBAtomName::HB2   },
    { " HB3",   PDBAtomName::HB3   },
    { " HG ",   PDBAtomName::HG    },
    { " HG1",   PDBAtomName::HG1   },
    { "HG11",   PDBAtomName::HG11  },
    { "HG12",   PDBAtomName::HG12  },
    { "HG13",   PDBAtomName::HG13  },
    { " HG2",   PDBAtomName::HG2   },
    { "HG21",   PDBAtomName::HG21  },
    { "HG22",   PDBAtomName::HG22  },
    { "HG23",   PDBAtomName::HG23  },
    { " HG3",   PDBAtomName::HG3   },
    { " HD1",   PDBAtomName::HD1   },
    { "HD11",   PDBAtomName::HD11  },
    { "HD12",   PDBAtomName::HD12  },
    { "HD13",   PDBAtomName::HD13  },
    { " HD2",   PDBAtomName::HD2   },
    { "HD21",   PDBAtomName::HD21  },
    { "HD22",   PDBAtomName::HD22  },
    { "HD23",   PDBAtomName::HD23  },
    { " HD3",   PDBAtomName::HD3   },
    { " HE ",   PDBAtomName::HE    },
    { " HE1",   PDBAtomName::HE1   },
    { " HE2",   PDBAtomName::HE2   },
    { "HE21",   PDBAtomName::HE21  },
    { "HE22",   PDBAtomName::HE22  },
    { " HE3",   PDBAtomName::HE3   },
    { " HZ ",   PDBAtomName::HZ    },
    { " HZ1",   PDBAtomName::HZ1   },
    { " HZ2",   PDBAtomName::HZ2   },
    { " HZ3",   PDBAtomName::HZ3   },
    { " HH ",   PDBAtomName::HH    },
    { "HH11",   PDBAtomName::HH11  },
    { "HH12",   PDBAtomName::HH12  },
    { " HH2",   PDBAtomName::HH2   },
    { "HH21",   PDBAtomName::HH21  },
    { "HH22",   PDBAtomName::HH22  }
  };

  static const unsigned int AtomNameLibrarySize =
    sizeof(AtomNameLibrary) / sizeof(AtomNameLibraryItem);

}

#include "pdb/io/record-name.h"
#include "basic/util/string.h"
#include <cassert>

namespace mysimulator {

  PDBAtomName _AtomName(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    char str[6];
    SubString(str,_rec,12,15);
    for(unsigned int i=0;i<AtomNameLibrarySize;++i)
      if(strncmp(str,AtomNameLibrary[i].Key,4)==0)
        return AtomNameLibrary[i].Value;
    return PDBAtomName::Unknown;
  }

}

#endif

