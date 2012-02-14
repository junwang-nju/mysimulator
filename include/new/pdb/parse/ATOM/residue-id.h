
#ifndef _PDB_Parse_ATOM_ResidueID_H_
#define _PDB_Parse_ATOM_ResidueID_H_

#include "pdb/parse/line-name.h"
#include "intrinsic-type/string.h"

namespace mysimulator {

  unsigned int ResidueID4ATOM(const char* line) {
    assert(LineName(line)==PDBATOM);
    char tmstr[6];
    SubString(tmstr,line,22,25);
    return atoi(tmstr);
  }

  unsigned int ResidueID4ATOM(const Array1DContent<char>& line) {
    assert(IsValid(line));
    return ResidueID4ATOM(line.start);
  }

}

#endif

