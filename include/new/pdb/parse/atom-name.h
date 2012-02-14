
#ifndef _PDB_Parse_Atom_Name_H_
#define _PDB_Parse_Atom_Name_H_

#include "pdb/parse/file-line-name.h"
#include "pdb/atom/str-2-name.h"
#include "intrinsic-type/string.h"
#include <cassert>

namespace mysimulator {

  PDBAtomName AtomName(const char* line) {
    assert(FileLineName(line)==PDBATOM);
    char rstr[5],astr[6];
    SubString(rstr,line,17,19);
    SubString(astr,line,12,15);
    return String2AtomName(rstr,astr);
  }

}

#endif

