
#ifndef _PDB_Parse_ATOM_Residue_Name_H_
#define _PDB_Parse_ATOM_Residue_Name_H_

#include "pdb/parse/line-name.h"
#include "pdb/residue/str-2-name.h"
#include "intrinsic-type/string.h"

namespace mysimulator {

  PDBResidueName ResidueName4ATOM(const char* line) {
    assert(LineName(line)==PDBATOM);
    char tmstr[5];
    SubString(tmstr,line,17,19);
    return String2ResidueName(tmstr);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  PDBResidueName ResidueName4ATOM(const Array1DContent<char>& line) {
    assert(IsValid(line));
    return ResidueName4ATOM(line.start);
  }

}

#endif

