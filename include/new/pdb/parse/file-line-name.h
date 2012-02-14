
#ifndef _PDB_Parse_File_Line_Name_H_
#define _PDB_Parse_File_Line_Name_H_

#include "pdb/file-line-name.h"
#include <cstring>

namespace mysimulator {

  PDBFileLineName FileLineName(const char* line) {
    PDBFileLineName FLN;
    if(strncmp(line,"ATOM  ",6)==0)       FLN=PDBATOM;
    else if(strncmp(line,"MODEL ",6)==0)  FLN=PDBMODEL;
    else if(strncmp(line,"ENDMDL",6)==0)  FLN=PDBENDMDL;
    else if(strncmp(line,"TER   ",6)==0)  FLN=PDBTER;
    else FLN=PDBNotImplemented;
    return FLN;
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  PDBFileLineName FileLineName(const Array1DContent<char>& line) {
    assert(IsValid(line));
    return FileLineName(line.start);
  }

}

#endif

