
#ifndef _PDB_IO_Residue_Name_H_
#define _PDB_IO_Residue_Name_H_

#include "pdb/residue/name.h"

namespace mysimulator {

  struct ResidueNameLibraryItem {
    char Key[4];
    PDBResidueName Value;
  };

  static const ResidueNameLibraryItem ResidueNameLibrary[] = {
    { "ALA",    PDBResidueName::Ala   },
    { "ARG",    PDBResidueName::Arg   },
    { "ASN",    PDBResidueName::Asn   },
    { "ASP",    PDBResidueName::Asp   },
    { "CYS",    PDBResidueName::Cys   },
    { "GLN",    PDBResidueName::Gln   },
    { "GLU",    PDBResidueName::Glu   },
    { "GLY",    PDBResidueName::Gly   },
    { "HIS",    PDBResidueName::His   },
    { "ILE",    PDBResidueName::Ile   },
    { "LEU",    PDBResidueName::Leu   },
    { "LYS",    PDBResidueName::Lys   },
    { "MET",    PDBResidueName::Met   },
    { "PHE",    PDBResidueName::Phe   },
    { "PRO",    PDBResidueName::Pro   },
    { "SER",    PDBResidueName::Ser   },
    { "THR",    PDBResidueName::Thr   },
    { "TRP",    PDBResidueName::Trp   },
    { "TYR",    PDBResidueName::Tyr   },
    { "VAL",    PDBResidueName::Val   }
  };

  static const unsigned int ResidueNameLibrarySize =
    sizeof(ResidueNameLibrary) / sizeof(ResidueNameLibraryItem);

}

#include "pdb/io/record-name.h"
#include "basic/util/string.h"
#include <cassert>

namespace mysimulator {

  PDBResidueName _ResidueName(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    char str[5];
    SubString(str,_rec,17,19);
    for(unsigned int i=0;i<ResidueNameLibrarySize;++i)
      if(strncmp(str,ResidueNameLibrary[i].Key,3)==0)
        return ResidueNameLibrary[i].Value;
    return PDBResidueName::Unknown;
  }

}

#endif

