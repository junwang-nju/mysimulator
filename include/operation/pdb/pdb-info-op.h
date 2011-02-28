
#ifndef _PDB_Information_Operation_H_
#define _PDB_Information_Operation_H_

#include "data/pdb/pdb-info.h"
#include "data/basic/file-input.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
#include <cstring>

namespace std {

  bool PDBLinePropertyMatch(const char* line, const char* signature) {
    return strncmp(line,signature,6)==0;
  }

  /*
  unsigned int GetAtomName(const char* resname, const char* atomname) {
    if(strncmp(atomname," CA ",4)==0)  return CAlpha;
    else if(strncmp(atomname," C  ",4)==0)  return CCarbonyl;
    else if(strncmp(atomname," O  ",4)==0)  return OCarbonyl;
    else if(strncmp(atomname," OXT",4)==0)  return OCarboxyl;
    else if(strncmp(atomname," N  ",4)==0)  return NAmino;
    else if(strncmp(atomname," HA ",4)==0)  return HAlpha;
    else if(strncmp(atomname," HXT",4)==0)  return HOCarboxyl;
    else if((strncmp(atomname," H  ",4)==0)||(strncmp(atomname," H1 ",4)==0))
      return H1NAmino;
    else if(strncmp(atomname," H2 ",4)==0)  return H2NAmino;
    else if(strncmp(resname,"ALA",3)==0) {
      if(strncmp(atomname," CB ")==0)   return AlaCBeta;
      else if(strncmp(atomname," HB1")==0)  return AlaH1Beta;
      else if(strncmp(atomname," HB2")==0)  return AlaH1Beta;
      else if(strncmp(atomname," HB3")==0)  return AlaH1Beta;
      else if(strncmp(atomname," H3 ")==0)  return AlaH3NAmino;
      else Error("Unknown atom type for Ala");
    } else if(strncmp(resname,"ARG",3)==0) {
      if(strncmp(atomname," CB ",4)==0) return ArgCBeta;
      else if(strncmp(atomname," CG ",4)==0)  return ArgCGamma;
      else if(strncmp(atomname," CD ",4)==0)  return ArgCDelta;
      else if(strncmp(atomname," NE ",4)==0)  return ArgNEpsilon;
      else if(strncmp(atomname," CZ ",4)==0)  return ArgCZeta;
      else if(strncmp(atomname," NH1",4)==0)  return ArgN1Eta;
      else if(strncmp(atomname," NH2",4)==0)  return ArgN2Eta;
    }
  }
  */

  void ImportPDBInfo(PDBInfo& PI, const char* pdbfname) {
    FileInput FI;
    unsigned int nmodel,nmodelend, natom,naminoacid,nbond;
    char buff[1024], oldpat[6]="XXXXX";
    bool flag;
    allocate(FI,pdbfname);
    nmodel=nmodelend=0;
    natom=naminoacid=nbond=0;
    flag=true;
    while(!isFail(FI)) {
      getline(buff,1024,FI);
      if(PDBLinePropertyMatch(buff,"MODEL ")) ++nmodel;
      else if(PDBLinePropertyMatch(buff,"ENDMDL")) { ++nmodelend; flag=false; }
      if(flag) {
        if(PDBLinePropertyMatch(buff,"ATOM  ")) {
          ++natom;
          if(strncmp(oldpat,buff+22,5)!=0) {
            strncpy(oldpat,buff+22,5);
            ++naminoacid;
          }
        } else if(PDBLinePropertyMatch(buff,"TER   "))  ++nbond;
      }
    }
    assert(nmodel==nmodelend);
    release(FI);
    if(nmodel==0) flag=true;
    if(nmodel==0) nmodel=1;
    nbond=naminoacid-nbond;

    Vector<unsigned int> usize;
    int paa;
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
    while(!isFail(FI)) {
      getline(buff,1024,FI);
      if(PDBLinePropertyMatch(buff,"MODEL ")) {
        flag=true;
        natom=naminoacid=nbond=0;
        paa=-1;
        strncpy(oldpat,"XXXXX",5);
      } else if(PDBLinePropertyMatch(buff,"ENDMDL")) {
        ++nmodel;
        flag=false;
      } else if(flag) {
        if(PDBLinePropertyMatch(buff,"ATOM  ")) {
          if(nmodel==0) {
            if(strncmp(oldpat,buff+22,5)!=0) {
              strncpy(oldpat,buff+22,5);
              for(unsigned int i=0;i<NumberAminoAcids;++i)
                if(strncmp(AminoAcidStringName[i],buff+17,3)==0) {
                  PI.UnitName[naminoacid]=i;
                  break;
                }
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
            //buff+12,4
          }
        } else if(PDBLinePropertyMatch(buff,"TER   ")&&(nmodel==0)) paa=-1;
      }
    }
    PI.UnitBond.update();
    release(FI);
  }

}

#endif

