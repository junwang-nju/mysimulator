
#ifndef _PDB_Information_Operation_H_
#define _PDB_Information_Operation_H_

#include "data/pdb/pdb-info.h"
#include "data/basic/file-input.h"
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
    if((!IsAvailable(UnitNameLibrary))||(!IsAvailable(UnitAtomNameLibrary)))
      InitNameLibrary();
    if(!IsAvailable(AminoAcidNumberAtoms))  InitAminoAcidNumberAtoms();
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
    if(nmodel==0) nmodel=1;
    nbond=naminoacid-nbond;

    int paa;
    char tmname[9];
    unsigned int *tname;
    Vector<unsigned int> usize;

    allocate(usize,natom);
    copy(usize,3);
    allocate(PI.Coordinate,nmodel);
    for(unsigned int i=0;i<nmodel;++i)  allocate(PI.Coordinate[i],usize);
    allocate(PI.AtomName,natom);
    allocate(PI.UnitName,naminoacid);
    allocate(PI.UnitBond,nbond);
    allocate(PI.UnitAtomID,naminoacid);

    strncpy(oldpat,"XXXXX",5);
    paa=-1;
    nmodel=natom=naminoacid=nbond=0;
    tmname[8]='\0';
    flag=true;

    allocate(FI,pdbfname);
    while(!isFail(FI)) {
      getline(buff,1024,FI);
      if(IfLineProperty(buff,"ENDMDL")) {
        ++nmodel;
        natom=0;
        flag=false;
      } else if(IfLineProperty(buff,"ATOM  ")) {
        if(flag) {
          if(!CompareResidueID(oldpat,buff+22)) {
            SetResidueID(oldpat,buff+22);
            strncpy(tmname,buff+17,3);
            strncpy(tmname+3,"    ",4);
            tname=const_cast<unsigned int*>(get(UnitNameLibrary,tmname));
            if(tname!=NULL) PI.UnitName[naminoacid]=*tname;
            else Error("Unknown Amino Acid");
            allocate(PI.UnitAtomID[naminoacid],
                     AminoAcidNumberAtoms[PI.UnitName[naminoacid]]);
            copy(PI.UnitAtomID[naminoacid],-1);
            if(paa!=-1) {
              Set(PI.UnitBond,nbond,paa,naminoacid);
              ++nbond;
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
          PI.UnitAtomID[naminoacid-1][PI.AtomName[natom]]=natom;
        }
        strncpy(tmname,buff+30,8);
        PI.Coordinate[nmodel][natom][0]=atof(tmname);
        strncpy(tmname,buff+38,8);
        PI.Coordinate[nmodel][natom][1]=atof(tmname);
        strncpy(tmname,buff+46,8);
        PI.Coordinate[nmodel][natom][2]=atof(tmname);
        ++natom;
      } else if(IfLineProperty(buff,"TER   ")&&flag) paa=-1;
    }
    PI.UnitBond.update();
    release(FI);
  }

}

#endif

