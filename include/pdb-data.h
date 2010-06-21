
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

  bool IsPDBProperty(const char* line, const char* signature) {
    return strncmp(line,signature,6)==0;
  }

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
    unsigned int modelCount=0;
    int nowResID=-1, AACount=-1, AtomCount;
    pdb.model.push_back(ModelType());
    while(!ifs.eof()) {
      ifs.getline(lbuff,1023);
      if(IsPDBProperty(lbuff,"MODEL ")) {
      } else if(IsPDBProperty(lbuff,"ENDMDL")) {
        ++modelCount;
        AACount=-1;
      } else if(IsPDBProperty(lbuff,"ATOM  ")) {
        if(nowResID!=atoi(lbuff+22)) {
          nowResID=atoi(lbuff+22);
          pdb.model[modelCount].push_back(AminoAcidType());
          ++AACount;
          Set(pdb.model[modelCount][AACount].name,lbuff+17);
        }
        pdb.model[modelCount][AACount].data.push_back(AtomType());
        Set(pdb.model[modelCount][AACount].data[AtomCount],lbuff+12);
        Set(pdb.model[modelCount][AACount].data[AtomCount],
            atoi(lbuff+30),atoi(lbuff+38),atoi(lbuff+46));
        pdb.model[modelCount][AACount].data[AtomCount].TempFactor=
            (strncmp(lbuff+60,"      ",6)!=0?atoi(lbuff+0):0.);
        ++AtomCount;
      }
    }
    ifs.close();
  }

}

#endif

