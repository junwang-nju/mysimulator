
#ifndef _PDB_Operation_H_
#define _PDB_Operation_H_

#include <fstream>
#include <cstring>
#include <cctype>
#include <vector>
#include "property-list.h"
#include "var-vector.h"

namespace std {

  enum PDBFileType {
    PDBFile=0,
    ENTFile
  };

  enum PDBCoordinateType {
    CAlphaType=0,
    HeavyAtomType
  };

  template <template <typename> class VecType>
  void pdb2coordinate(
      const char* pdbid, PropertyList<double,VecType>& Coordinate,
      const unsigned int CoorMode=CAlphaType,
      const unsigned int PdbType=PDBFile) {
    char* lbuff=new char[1024];
    lbuff[1023]=0;
    char* pdbfname=new char[64];
    char* cpdbid=new char[5];
    for(unsigned int i=0;i<4;++i) cpdbid[i]=toupper(pdbid[i]);
    cpdbid[4]=0;
    strcpy(pdbfname,cpdbid);
    if(PdbType==PDBFile)  strcpy(pdbfname+4,".pdb");
    else                  myError("Unknown Type of PDB data");
    ifstream ifs(pdbfname);
    vector<double> tmpdata;
    if(!ifs.fail()) {
      while(!ifs.eof()) {
        ifs.getline(lbuff,1023);
        if(strncmp(lbuff,"ATOM  ",6)==0) {
          if(CoorMode==CAlphaType) {
            if(strncmp(lbuff+13,"CA",2)==0) {
              tmpdata.push_back(atof(lbuff+30));
              tmpdata.push_back(atof(lbuff+38));
              tmpdata.push_back(atof(lbuff+46));
            }
          } else if(CoorMode==HeavyAtomType) {
            if((lbuff[13]!='H')&&(lbuff[13]!=' ')) {
              tmpdata.push_back(atof(lbuff+30));
              tmpdata.push_back(atof(lbuff+38));
              tmpdata.push_back(atof(lbuff+46));
            }
          }
        }
      }
    }
    varVector<unsigned int> Sz;
    Sz.allocate(tmpdata.size()/3);
    Sz=3;
    Coordinate.allocate(Sz);
    for(unsigned int i=0,n=0;i<Coordinate.size();++i)
    for(unsigned int j=0;j<3;++j,++n)
      Coordinate[i][j]=tmpdata[n];
    ifs.close();
  }

}

#endif

