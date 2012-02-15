
#ifndef _PDB_Parse_ATOM_altLoc_Flag_H_
#define _PDB_Parse_ATOM_altLoc_Flag_H_

#include "pdb/parse/line-name.h"

namespace mysimulator {

  bool AltLocationFlag4ATOM(const char* line) {
    assert(LineName(line)==PDBATOM);
    return (line[16]!=' ')&&(line[16]!='A');
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  bool AltLocationFlag4ATOM(const Array1DContent<char>& line) {
    assert(IsValid(line));
    return AltLocationFlag4ATOM(line.start);
  }

}

#endif

