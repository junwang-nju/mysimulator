
#ifndef _PDB_Molecule_GetNumber_H_
#define _PDB_Molecule_GetNumber_H_

#include "pdb/parse/line-name.h"
#include "intrinsic-type/string.h"

namespace mysimulator {

  unsigned int NumberMolecules(const char* file) {
    bool rflag=true;
    char* run=const_cast<char*>(file);
    unsigned int nl=0, nmol=0;
    PDBLineName PLN;
    while(rflag) {
      nl=LineSize(run);
      rflag=(run[nl]!='\0');
      PLN=LineName(run);
      if(PLN==PDBTER) ++nmol;
      else if(PLN==PDBENDMDL) rflag=false;
      run=run+nl+1;
    }
    return nmol;
  }

  unsigned int NumberMolecules(const Array1DContent<char>& file) {
    assert(IsValid(file));
    return NumberMolecules(file.start);
  }

}

#endif

