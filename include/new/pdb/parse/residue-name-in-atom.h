
#ifndef _PDB_Parse_Residue_Name_In_Atom_H_
#define _PDB_Parse_Residue_Name_In_Atom_H_

#include "pdb/parse/file-line-name.h"
#include "pdb/residue/str-2-name.h"
#include "intrinsic-type/string.h"
#include <cassert>

namespace mysimulator {

  PDBResidueName ResidueNameInAtom(const char* line) {
    assert(FileLineName(line)==PDBATOM);
    char tmstr[5];
    SubString(tmstr,line,17,19);
    return String2ResidueName(tmstr);
  }

}

#endif

