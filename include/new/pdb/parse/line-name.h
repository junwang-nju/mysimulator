
#ifndef _PDB_Parse_Line_Name_H_
#define _PDB_Parse_Line_Name_H_

#include "pdb/line-name.h"
#include <cstring>

namespace mysimulator {

  PDBLineName LineName(const char* line) {
    PDBLineName LN;
    if(strncmp(line,"ATOM  ",6)==0)       LN=PDBATOM;
    else if(strncmp(line,"MODEL ",6)==0)  LN=PDBMODEL;
    else if(strncmp(line,"ENDMDL",6)==0)  LN=PDBENDMDL;
    else if(strncmp(line,"TER   ",6)==0)  LN=PDBTER;
    else LN=PDBNotImplemented;
    return LN;
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  PDBLineName LineName(const Array1DContent<char>& line) {
    assert(IsValid(line));
    return LineName(line.start);
  }

}

#endif

