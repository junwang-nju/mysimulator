
#ifndef _PDB_Residue_GetNumber_H_
#define _PDB_Residue_GetNumber_H_

#include "pdb/molecule/get-number.h"
#include "pdb/parse/ATOM/alt-loc-flag.h"
#include "pdb/parse/ATOM/residue-id.h"

namespace mysimulator {

  void NumberResidues(Array1DContent<unsigned int>& NRes, const char* file) {
    assert(NRes.size>=NumberMolecules(file));
    bool rflag=true;
    char* run=const_cast<char*>(file);
    unsigned int nl=0, nmol=0, nres=0, rres=0, tres=0;
    PDBLineName PLN;
    while(rflag) {
      nl=LineSize(run);
      rflag=(run[nl]!='\0');
      PLN=LineName(run);
      if((PLN==PDBATOM)&&(!AltLocationFlag4ATOM(run))) {
        tres=ResidueID4ATOM(run);
        if(tres!=rres) { ++nres; rres=tres; }
      }
      else if(PLN==PDBTER) { NRes[nmol]=nres; ++nmol; nres=0; }
      else if(PLN==PDBENDMDL) rflag=false;
      run+=nl+1;
    }
  }

  void NumberResidues(Array1DContent<unsigned int>& NRes,
                      const Array1DContent<char>& file) {
    assert(IsValid(file));
    NumberResidues(NRes,file.start);
  }

}

#endif

