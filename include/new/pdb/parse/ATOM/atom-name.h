
#ifndef _PDB_Parse_ATOM_Atom_Name_H_
#define _PDB_Parse_ATOM_Atom_Name_H_

#include "pdb/parse/line-name.h"
#include "pdb/atom/str-2-name.h"
#include "intrinsic-type/string.h"

namespace mysimulator {

  PDBAtomName AtomName4ATOM(const char* line) {
    assert(LineName(line)==PDBATOM);
    char astr[6];
    SubString(astr,line,12,15);
    return String2AtomName(astr);
  }

  PDBAtomName AtomName4ATOM(const Array1DContent<char>& line) {
    assert(IsValid(line));
    return AtomName4ATOM(line.start);
  }

}

#endif

