
#ifndef _PDB_Data_Structure_Operation_H_
#define _PDB_Data_Structure_Operation_H_

#include <fstream>
#include "pdb-data-structure.h"
#include "var-matrix-triangle.h"
#include "util.h"

namespace std {

  enum PDBFileType {
    PDBFile=0,
    ENTFile
  };

  bool IsPDBProperty(const char* line, const char* Signature) {
    return strncmp(line,Signature,6)==0;
  }

  void ImportPDB(const char* pdbid, const unsigned int FileType,
                 PDBDataStructure& pdb, const char* dataRoot) {
    char* pdbfname=new char[256];
    char* cpdbid=new char[5];
    toupper(cpdbid,pdbid,4);  cpdbid[4]=0;
    pdb.Id.SetAs(cpdbid);
    strcpy(pdbfname,dataRoot);
    strcat(pdbfname,cpdbid);
    if(FileType==PDBFile)  strcat(pdbfname,".pdb");
    else                   myError("Unknown Type of PDB data");
    ifstream ifs(pdbfname);
    if(ifs.fail())  myError("Something Wrong with Input PDB File");
    char *lbuff=new char[1024];
    int ModelCount=0,nowResID=-1,AACount=-1,AtomCount;
    lbuff[1023]=0;
    pdb.Model.push_back(ModelType());
    while(!ifs.eof()) {
      ifs.getline(lbuff,1023);
      if(IsPDBProperty(lbuff,"MODEL ")) {
      } else if(IsPDBProperty(lbuff,"ENDMDL")) {
        ++ModelCount;
        AACount=-1;
      } else if(IsPDBProperty(lbuff,"ATOM  ")) {
        if(nowResID!=atoi(lbuff+22)) {
          nowResID=atoi(lbuff+22);
          pdb.Model[ModelCount].push_back(AminoAcidType());
          ++AACount;
          AtomCount=0;
          pdb.Model[ModelCount][AACount].Name.SetAs(lbuff+17);
        }
        pdb.Model[ModelCount][AACount].Data.push_back(AtomType());
        pdb.Model[ModelCount][AACount].Data[AtomCount].SetNameAs(lbuff+12);
        pdb.Model[ModelCount][AACount].Data[AtomCount].SetCoordinateAs(
            atof(lbuff+30),atof(lbuff+38),atof(lbuff+46));
        pdb.Model[ModelCount][AACount].Data[AtomCount].TempFactor=
          (strncmp(lbuff+60,"      ",6)!=0?atof(lbuff+60):0.);
        ++AtomCount;
      }
    }
    ifs.close();
  }

  enum PDBCoordinateType {
    CAlphaType=0,
    HeavyAtomType
  };

  static const double DistThreshold4Contact[]={8.0,5.0};

  void CalcContactMap(
      const PDBDataStructure& pdb,
      varMatrixTriangle<unsigned int>::Type& ContactMap,
      const unsigned int CoorMode, const double dThreshold=-1.) {
    double rThreshold=dThreshold;
    if(rThreshold<0)  rThreshold=DistThreshold4Contact[CoorMode];
    ContactMap.allocate(pdb.Model[0].size(),
                        COrder,NoTranspose,UpperPart,true,false);
  }

}

#endif

