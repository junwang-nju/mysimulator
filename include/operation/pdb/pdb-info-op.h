
#ifndef _PDB_Information_Operation_H_
#define _PDB_Information_Operation_H_

#include "data/pdb/pdb-info.h"
#include "data/basic/file-input.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
#include <cstring>

namespace std {

  bool IfLineProperty(const char* line, const char* signature) {
    return strncmp(line,signature,6)==0;
  }
  
  bool CompareResidueID(const char* rid1, const char* rid2) {
    return strncmp(rid1,rid2,5)==0;
  }
  
  void SetResidueID(char* res, const char* rid) { strncpy(res,rid,5); }

  void ImportPDBInfo(PDBInfo& PI, const char* pdbfname) {
    if(IsAvailable(UnitNameLibrary)||IsAvailable(UnitAtomNameLibrary))
      InitNameLibrary();
    FileInput FI;
    unsigned int nmodel,nmodelend,natom,naminoacid,nbond;
    char buff[1024], oldpat[6]="XXXXX";
    bool flag;
    allocate(FI,pdbfname);
    nmodel=nmodelend=natom=naminoacid=nbond=0;
    flag=true;
    while(!isFail(FI)) {
      getline(buff,1024,FI);
      if(IfLineProperty(buff,"MODEL ")) ++nmodel;
      else if(IfLineProperty(buff,"ENDMDL")) { ++nmodelend; flag=false; }
      if(flag) {
        if(IfLineProperty(buff,"ATOM  ")) {
          ++natom;
          if(CompareResidueID(oldpat,buff+22)!=0) ++naminoacid;
          SetResidueID(oldpat,buff+22);
        } else if(IfLineProperty(buff,"TER   "))  ++nbond;
      }
    }
    release(FI);
    if(nmodel!=nmodelend) Error("MODEL & ENDMDL are not compatible");
    if(nmodel==0) flag=true;
    if(nmodel==0) nmodel=1;
    nbond=naminoacid-nbond;

    Vector<unsigned int> usize;
    int paa;
    char tmname[9];
    unsigned int *tname;
    allocate(usize,natom);
    copy(usize,3);
    allocate(PI.Coordinate,nmodel);
    for(unsigned int i=0;i<nmodel;++i)  allocate(PI.Coordinate[i],usize);
    allocate(PI.AtomName,natom);
    allocate(PI.UnitName,naminoacid);
    allocate(PI.UnitBond,2,1,nbond*2);
    allocate(usize,naminoacid);
    strncpy(oldpat,"XXXXX",5);
    paa=-1;
    allocate(FI,pdbfname);
    nmodel=natom=naminoacid=nbond=0;
    tmname[8]='\0';
    while(!isFail(FI)) {
      getline(buff,1024,FI);
      if(IfLineProperty(buff,"MODEL ")) {
        flag=true;
        natom=naminoacid=nbond=0;
        paa=-1;
        strncpy(oldpat,"XXXXX",5);
      } else if(IfLineProperty(buff,"ENDMDL")) {
        ++nmodel;
        flag=false;
      } else if(flag) {
        if(IfLineProperty(buff,"ATOM  ")) {
          if(nmodel==0) {
            if(strncmp(oldpat,buff+22,5)!=0) {
              strncpy(oldpat,buff+22,5);
              strncpy(tmname,buff+17,3);
              strncpy(tmname+3,"    ",4);
              tname=const_cast<unsigned int*>(get(UnitNameLibrary,tmname));
              if(tname!=NULL) PI.UnitName[naminoacid]=*tname;
              else Error("Unknown Amino Acid");
              usize[naminoacid]=AminoAcidNumberAtoms[PI.UnitName[naminoacid]];
              if(paa!=-1) {
                PI.UnitBond.key[nbond][0]=paa;
                PI.UnitBond.key[nbond][1]=naminoacid;
                PI.UnitBond.key[nbond+1][0]=naminoacid;
                PI.UnitBond.key[nbond+1][1]=paa;
                nbond+=2;
              }
              paa=naminoacid;
              ++naminoacid;
            }
            strncpy(tmname,"   ",3);
            strncpy(tmname+3,buff+12,4);
            tname=const_cast<unsigned int*>(get(UnitAtomNameLibrary,tmname));
            if(tname!=NULL) PI.AtomName[natom]=*tname;
            else {
              strncpy(tmname,buff+17,3);
              tname=const_cast<unsigned int*>(get(UnitAtomNameLibrary,tmname));
              if(tname!=NULL) PI.AtomName[natom]=*tname;
              else Error("Unknown Atom");
            }
          }
          strncpy(tmname,buff+30,8);
          PI.Coordinate[nmodel][natom][0]=atof(tmname);
          strncpy(tmname,buff+38,8);
          PI.Coordinate[nmodel][natom][1]=atof(tmname);
          strncpy(tmname,buff+46,8);
          PI.Coordinate[nmodel][natom][2]=atof(tmname);
          ++natom;
        } else if(IfLineProperty(buff,"TER   ")&&(nmodel==0)) paa=-1;
      }
    }
    PI.UnitBond.update();
    release(FI);
    allocate(PI.UnitAtomID,usize);
    flag=true;
    strncpy(oldpat,"XXXXX",5);
    naminoacid=natom=0;
    copy(PI.UnitAtomID,-1);
    allocate(FI,pdbfname);
    while(!isFail(FI)) {
      getline(buff,1024,FI);
      if(IfLineProperty(buff,"ENDMDL"))   break;
      if(flag&&IfLineProperty(buff,"ATOM  ")) {
        if(strncmp(oldpat,buff+22,5)!=0) {
          strncpy(oldpat,buff+22,5);
          ++naminoacid;
        }
        PI.UnitAtomID[naminoacid-1][PI.AtomName[natom]]=natom;
        ++natom;
      }
    }
    release(FI);
  }

}

#endif

