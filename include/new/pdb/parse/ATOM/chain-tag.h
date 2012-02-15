
#ifndef _PDB_Parse_ATOM_Chain_Tag_H_
#define _PDB_Parse_ATOM_Chain_Tag_H_

#include "pdb/parse/line-name.h"

namespace mysimulator {

  unsigned int ChainTag4ATOM(const char* line) {
    assert(LineName(line)==PDBATOM);
    return static_cast<unsigned int>(line[21]);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  unsigned int ChainTag4ATOM(const Array1DContent<char>& line) {
    assert(IsValid(line));
    return ChainTag4ATOM(line.start);
  }

}

#endif

