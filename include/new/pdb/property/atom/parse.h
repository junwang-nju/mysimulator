
#ifndef _PDB_Property_Atom_Parse_H_
#define _PDB_Property_Atom_Parse_H_

#include "pdb/property/atom/interface.h"
#include "pdb/property/identify.h"

namespace mysimulator {

  void parse(PDBAtom& A, const char* line) {
    assert(identifyPDBProperty(line)==PDBATOM);
  }

  void parse(PDBAtom& A, const Array1DContent<char>& line) {
    parse(A,line.start);
  }

}

#endif

