
#ifndef _PDB_Parse_ATOM_Position_H_
#define _PDB_Parse_ATOM_Position_H_

#include "pdb/parse/line-name.h"
#include "pdb/atom/position/interface.h"
#include "intrinsic-type/string.h"
#include <cstdlib>

namespace mysimulator {

  void Position(PDBAtomPosition& P, const char* line) {
    assert(LineName(line)==PDBATOM);
    char tmstr[10];
    SubString(tmstr,line,30,37);
    P.X=atof(tmstr);
    SubString(tmstr,line,38,45);
    P.Y=atof(tmstr);
    SubString(tmstr,line,46,53);
    P.Z=atof(tmstr);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  void Position(PDBAtomPosition& P, const Array1DContent<char>& line) {
    assert(IsValid(line));
    Position(P,line.start);
  }

}

#endif

