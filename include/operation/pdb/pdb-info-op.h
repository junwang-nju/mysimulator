
#ifndef _PDB_Information_Operation_H_
#define _PDB_Information_Operation_H_

#include "data/pdb/pdb-info.h"
#include "data/basic/file-input.h"
#include "data/basic/console-output.h"
#include <cstring>

namespace std {

  bool PDBLinePropertyMatch(const char* line, const char* signature) {
    return strncmp(line,signature,6)==0;
  }

  void ImportPDBInfo(PDBInfo& PI, const char* pdbfname) {
    FileInput FI;
    unsigned int nmodel,nmodelend, natom,naminoacid;
    char buff[1024], oldpat[6]="XXXXX";
    bool flag;
    allocate(FI,pdbfname);
    nmodel=nmodelend=0;
    natom=naminoacid=0;
    flag=true;
    while(!isFail(FI)) {
      getline(buff,1024,FI);
      if(PDBLinePropertyMatch(buff,"MODEL ")) ++nmodel;
      else if(PDBLinePropertyMatch(buff,"ENDMDL")) { ++nmodelend; flag=false; }
      if(flag&&PDBLinePropertyMatch(buff,"ATOM  ")) {
        ++natom;
        if(strncmp(oldpat,buff+22,5)!=0) {
          strncpy(oldpat,buff+22,5);
          ++naminoacid;
        }
      }
    }
    assert(nmodel==nmodelend);
    release(FI);
    if(nmodel==0) nmodel=1;
    COut<<nmodel<<"\t"<<natom<<"\t"<<naminoacid<<Endl;
  }

}

#endif

