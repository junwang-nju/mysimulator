
#ifndef _PDB_Property_Atom_Parse_H_
#define _PDB_Property_Atom_Parse_H_

#include "pdb/property/atom/interface.h"
#include "pdb/property/identify.h"
#include "pdb/property/atom/get-type.h"
#include "intrinsic-type/string.h"
#include <cstdlib>

namespace mysimulator {

  void parse(PDBAtom& A, const char* line) {
    assert(identifyPDBProperty(line)==PDBATOM);
    char tmstr[80],tmstr1[80];
    SubString(tmstr,line,6,10);
    A.AtomID=atoi(tmstr);
    SubString(tmstr,line,12,15);
    SubString(tmstr1,line,17,19);
    A.AtomType=GetAtomName(tmstr,tmstr1);
    SubString(tmstr,line,30,37);
    A.Position.X=atof(tmstr);
    SubString(tmstr,line,38,45);
    A.Position.Y=atof(tmstr);
    SubString(tmstr,line,46,53);
    A.Position.Z=atof(tmstr);
    SubString(tmstr,line,60,65);
    A.BFactor=atof(tmstr);
  }

  void parse(PDBAtom& A, const Array1DContent<char>& line) {
    parse(A,line.start);
  }

}

#endif

