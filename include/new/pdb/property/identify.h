
#ifndef _PDB_Property_Identify_H_
#define _PDB_Property_Identify_H_

#include "pdb/property/name.h"
#include <cstring>

namespace mysimulator {

  PDBPropertyName identifyPDBProperty(const char* line) {
    PDBPropertyName PPN;
    if(strncmp(line,"ATOM  ",6)==0)         PPN=PDBATOM;
    else if(strncmp(line,"MODEL ",6)==0)    PPN=PDBMODEL;
    else if(strncmp(line,"ENDMDL",6)==0)    PPN=PDBENDMDL;
    else if(strncmp(line,"TER   ",6)==0)    PPN=PDBTER;
    else PPN=PDBNotImplemented;
    return PPN;
  }

}

#endif

