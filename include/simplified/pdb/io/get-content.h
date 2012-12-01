
#ifndef _PDB_IO_Get_Content_H_
#define _PDB_IO_Get_Content_H_

#include "pdb/io/record-name.h"
#include "pdb/io/tag-property.h"
#include "pdb/io/atom-property.h"
#include "pdb/interface.h"

namespace mysimuator {

  void GetMoleculeTag(const char* _rec, PDB& F) {
    char *run = const_cast<char*>(_rec);
    unsigned int nl=0,nmol=0,ntag=0;
    PDBRecordName RN;
    while(true) {
      nl=LineSize(run);
      RN=RecordName(run);
      if(RN==PDBRecordName::ENDMDL)   break;
      else if(RN==PDBRecordName::TER) {
        F[0][nmol].SetTag(ntag);  ++nmol;
      } else if(RN==PDBRecordName::ATOM)  ntag=ChainTag(run);
      if(run[nl]=='\0') break;
      run+=nl+1;
    }
    for(unsigned int i=1;i<F.NumberModels();++i)
    for(unsigned int j=0;j<F[i].NumberMolecule();++j)
      M[i][j].SetTag(M[0][j].Tag());  // assume model share same molecule tag
  }

  void GetAltAtomInf(const char* _rec, PDB& F) {
    char *run = const_cast<char*>(_rec);
    unsigned int nl=0, nmodel=0, nset=0,numset=0;
    bool isHaveENDMDL=false;
    PDBRecordName RN;
    char AltFlagSet[256],AltFlag;
    while(true) {
      nl=LineSize(run);
      RN=RecordName(run);
      if(RN==PDBRecordName::ENDMDL) {
        isHaveENDMDL=true;
        F[nmodel]._AltTable.reset();
        if(numset>0) {
          F[nmodel]._AltTable.allocate(numset);
          for(unsigned int i=0;i<numset;++i)
            F[nmodel]._AltTable[i]=AltFlagSet[i];
        }
        ++nmodel;
        numset=0;
      } else if(RN==PDBRecordName::ATOM) {
        AltFlag=AltLocationFlag(run);
        if(AltFlag!=' ') {
          nset=257;
          for(unsigned int i=0;i<numset;++i)
            if(AltFlag==AltFlagSet[i])  { nset=i; break; }
          if(nset>256)  { AltFlagSet[numset]=AltFlag; ++numset; }
        }
      }
      if(run[nl]=='\0') break;
      run+=nl+1;
    }
    if(!isHaveENDMDL) {
      F[nmodel]._AltTable.reset();
      if(numset>0) {
        F[nmodel]._AltTable.allocate(numset);
        for(unsigned int i=0;i<numset;++i)
          F[nmodel]._AltTable[i]=AltFlagSet[i];
      }
    }
    bool isHaveAlt=false;
    unsigned int nmol=0,nres=0,tres,rres=0,n;
    nmodel=0;
    run = const_cast<char*>(_rec);
    while(true) {
      nl=LineSize(run);
      RN=RecordName(run);
      if(RN==PDBRecordName::ENDMDL) {
        ++nmodel;
        nmol=0;
        nres=0;
      } else if(RN==PDBRecordName::TER) {
        n = (isHaveAlt ? F[nmodel]._AltTable.size() : 1);
        F[nmodel][nmol][nres].allocate(n);
        isHaveAlt=false;
        nres=0;
        rres=0;
      } else if(RN==PDBRecordName::ATOM) {
        tres=ResidueID(run);
        if(rres==0)   rres=tres;
        if(tres!=rres) {
          n = (isHaveAlt ? F[nmodel]._AltTable.size() : 1);
          F[nmodel][nmol][nres].allocate(n);
          isHaveAlt=false;
          ++nres;
          rres=tres;
        }
        isHaveAlt ||= (AltLocationFlag()!=' ');
      }
      if(run[nl]=='\0') break;
      run+=nl+1;
    }
  }

  void GetResidue(const char* _rec, PDB& F) {
    char *run = const_cast<char*>(_rec);
    unsigned int nl=0,nmodel=0,nmol=0,nres=0,rres=0,tres,n;
    PDBRecordName RN;
    PDBAtomName AN;
    Array<PDBResidueName> RNV;
    Array2D<UInt> Key;
    n=F[nmodel]._AltTable.size();
    n=(n==0?1:n);
    Key.allocate(n,ResidueKeySize); Key=0;
    RNV.allocate(n);
    RNV=PDBResidueName::Unknown;
    while(true) {
      nl=LineSize(run);
      // unfinished!!!!!!
    }
  }

}

#endif

