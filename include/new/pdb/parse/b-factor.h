
#ifndef _PDB_Parse_BFactor_H_
#define _PDB_Parse_BFactor_H_

#include "pdb/parse/file-line-name.h"
#include "intrinsic-type/string.h"
#include <cassert>
#include <cstdlib>

namespace mysimulator {

  double BFactor(const char* line) {
    assert(FileLineName(line)==PDBATOM);
    char tmstr[8];
    SubString(tmstr,line,60,65);
    return atof(tmstr);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  double BFactor(const Array1DContent<char>& line) {
    assert(IsValid(line));
    return BFactor(line.start);
  }

}

#endif

