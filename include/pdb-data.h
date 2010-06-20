
#ifndef _PDB_Data_H_
#define _PDB_Data_H_

#include "pdb-id.h"
#include "pdb-model.h"

namespace std {

  struct PDBData;
  
  void assign(PDBData&, const PDBData&);

  struct PDBData {
    PDBID id;
    vector<ModelType> model;
    
    typedef PDBData   Type;
    
    PDBData() : id(), model() {}
    PDBData(const Type&) { myError("Cannot create from PDB Data"); }
    Type& operator=(const Type& PD) { assign(*this,PD); return *this; }
  };

  void assign(PDBData& dest, const PDBData& src) {
    dest.id=src.id;
    dest.model=src.model;
  }

}

#include <fstream>

namespace std{

  enum PDBFileTypeName {
    PDBFile=0,
    ENtFile
  };

  void Import(const char* pdbcode, PDBData& pdb, const char* dataRoot="./",
              const unsigned int ftype=PDBFile) {
    char runname[256];
    char runid[5]="    ";
    toupper(runid,pdbcode,4);
    Set(pdb.id,runid);
    strcpy(runname,dataRoot);
    strcat(runname,runid);
    if(ftype==PDBFile)  strcat(runname,".pdb");
    else myError("Unknown PDB File Type!");
    ifstream ifs(runname);
    if(ifs.fail())  myError("Something Wrong with Input data)");
    char lbuff[1024];
    lbuff[1023]=0;
    int modelCount=0;
    int nowResID=-1, AACount=-1, AtomCount;
  }

}

#endif

