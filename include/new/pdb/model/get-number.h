
#ifndef _PDB_Model_GetNumber_H_
#define _PDB_Model_GetNumber_H_

#include "pdb/parse/line-name.h"
#include "intrinsic-type/string.h"

namespace mysimulator {

  unsigned int NumberModels(const char* file) {
    bool rflag=true;
    char* run=const_cast<char*>(file);
    unsigned int nl=0,nmodel=0;
    while(rflag) {
      nl=LineSize(run);
      rflag=(run[nl]!='\0');
      if(LineName(run)==PDBMODEL) ++nmodel;
      run=run+nl+1;
    }
    return (nmodel==0?1:nmodel);
  }

  unsigned int NumberModels(const Array1DContent<char>& file) {
    assert(IsValid(file));
    return NumberModels(file.start);
  }

}

#endif

