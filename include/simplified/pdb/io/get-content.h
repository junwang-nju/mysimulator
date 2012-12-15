
#ifndef _PDB_IO_Get_Content_H_
#define _PDB_IO_Get_Content_H_

#include "pdb/io/record-name.h"
#include "pdb/io/tag-property.h"
#include "pdb/io/atom-property.h"
#include "pdb/interface.h"

namespace mysimulator {

  void _GetMoleculeTag(const char* _rec, PDB& F) {
    char *run = const_cast<char*>(_rec);
    unsigned int nl=0,nmol=0,ntag=0;
    PDBRecordName RN;
    while(true) {
      nl=LineSize(run);
      RN=_RecordName(run);
      if(RN==PDBRecordName::ENDMDL)   break;
      else if(RN==PDBRecordName::TER) { F[0][nmol].SetTag(ntag);  ++nmol; }
      else if(RN==PDBRecordName::ATOM)  ntag=_ChainTag(run);
      if(run[nl]=='\0') break;
      run+=nl+1;
    }
    for(unsigned int i=1;i<F.NumberModel();++i)
    for(unsigned int j=0;j<F[i].NumberMolecule();++j)
      F[i][j].SetTag(F[0][j].Tag());  // assume model share same molecule tag
  }

  void _GetAltAtomInf(const char* _rec, PDB& F) {
    char *run = const_cast<char*>(_rec);
    unsigned int nl=0, nmodel=0, nset=0,numset=0;
    bool isHaveENDMDL=false;
    PDBRecordName RN;
    char AltFlagSet[256],AltFlag;
    while(true) {
      nl=LineSize(run);
      RN=_RecordName(run);
      if(RN==PDBRecordName::ENDMDL) {
        isHaveENDMDL=true;
        F[nmodel].AlternativeInfoTable().reset();
        if(numset>0) {
          F[nmodel].AlternativeInfoTable().allocate(numset);
          for(unsigned int i=0;i<numset;++i)
            F[nmodel].AlternativeInfoTable()[i]=AltFlagSet[i];
        }
        ++nmodel;
        numset=0;
      } else if(RN==PDBRecordName::ATOM) {
        AltFlag=_AltLocationFlag(run);
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
      F[nmodel].AlternativeInfoTable().reset();
      if(numset>0) {
        F[nmodel].AlternativeInfoTable().allocate(numset);
        for(unsigned int i=0;i<numset;++i)
          F[nmodel].AlternativeInfoTable()[i]=AltFlagSet[i];
      }
    }
    bool isHaveAlt=false;
    unsigned int nmol=0,nres=0,tres,rres=0,n;
    nmodel=0;
    run = const_cast<char*>(_rec);
    while(true) {
      nl=LineSize(run);
      RN=_RecordName(run);
      if(RN==PDBRecordName::ENDMDL) {
        ++nmodel;
        nmol=0;
        nres=0;
      } else if(RN==PDBRecordName::TER) {
        n = (isHaveAlt ? F[nmodel].AlternativeInfoTable().size() : 1);
        F[nmodel][nmol][nres].allocate(n);
        isHaveAlt=false;
        nres=0;
        rres=0;
      } else if(RN==PDBRecordName::ATOM) {
        tres=_ResidueID(run);
        if(rres==0)   rres=tres;
        if(tres!=rres) {
          n = (isHaveAlt ? F[nmodel].AlternativeInfoTable().size() : 1);
          F[nmodel][nmol][nres].allocate(n);
          isHaveAlt=false;
          ++nres;
          rres=tres;
        }
        isHaveAlt = isHaveAlt || (_AltLocationFlag(run)!=' ');
      }
      if(run[nl]=='\0') break;
      run+=nl+1;
    }
  }

}

#include "pdb/io/atom-name.h"
#include "pdb/io/residue-name.h"

namespace mysimulator {

  void _GetResidue(const char* _rec, PDB& F) {
    char *run = const_cast<char*>(_rec);
    char AltFlag;
    unsigned int nl=0,nmodel=0,nmol=0,nres=0,rres=0,tres,n;
    PDBRecordName RN;
    PDBAtomName AN;
    Array<PDBResidueName> RNV;
    Array2D<UInt> Key;
    n=F[nmodel].AlternativeInfoTable().size();
    n=(n==0?1:n);
    Key.allocate(n,ResidueKeySize); Key=0;
    RNV.allocate(n);
    RNV=PDBResidueName::Unknown;
    while(true) {
      nl=LineSize(run);
      RN=_RecordName(run);
      if(RN==PDBRecordName::ENDMDL) {
        ++nmodel; nmol=0; nres=0; rres=0; Key.reset();
      } else if(RN==PDBRecordName::MODEL) {
        n=F[nmodel].AlternativeInfoTable().size();
        n=(n==0?1:n);
        Key.allocate(n,ResidueKeySize); Key=0;
        RNV.allocate(n);
        RNV=PDBResidueName::Unknown;
      } else if(RN==PDBRecordName::TER) {
        n=F[nmodel][nmol][nres].size();
        for(unsigned int i=0;i<n;++i) {
          if((bool)(F[nmodel].AlternativeInfoTable()))
            AltFlag=F[nmodel].AlternativeInfoTable()[i];
          else AltFlag=' ';
          assert(RNV[i]==ResidueName(Key[i].head()) ||
                 CTerminusResidueName(RNV[i])==ResidueName(Key[i].head()));
          //assert(__key_residue_consistency(RNV[i],Key[i].head()) ||
          //       __key_residue_consistency(CTerminusResidueName(RNV[i]),
          //                                 Key[i].head()));
          F[nmodel].Residue(nmol,nres,AltFlag).allocate(Key[i].head());
          F[nmodel].Residue(nmol,nres,AltFlag).Index()=rres;
        }
        ++nmol; nres=0; rres=0; Key=0;
        RNV=PDBResidueName::Unknown;
      } else if(RN==PDBRecordName::ATOM) {
        tres=_ResidueID(run);
        if(rres==0)   rres=tres;
        if(tres!=rres) {
          n=F[nmodel][nmol][nres].size();
          for(unsigned int i=0;i<n;++i) {
            if((bool)(F[nmodel].AlternativeInfoTable()))
              AltFlag=F[nmodel].AlternativeInfoTable()[i];
            else AltFlag=' ';
            assert(RNV[i]==ResidueName(Key[i].head()) ||
                   ( nres==0 &&
                     NTerminusResidueName(RNV[i])==ResidueName(Key[i].head())));
            //assert(
            //    __key_residue_consistency(RNV[i],Key[i].head()) ||
            //    ( nres==0 &&
            //      __key_residue_consistency(NTerminusResidueName(RNV[i]),
            //                                Key[i].head())));
            F[nmodel].Residue(nmol,nres,AltFlag).allocate(Key[i].head());
            F[nmodel].Residue(nmol,nres,AltFlag).Index()=rres;
          }
          ++nres;
          rres=tres;
          Key=0;
          RNV=PDBResidueName::Unknown;
        }
        AN=_AtomName(run);
        if(AN==PDBAtomName::Unknown)  fprintf(stderr,"Unknown Atom Type\n");
        else {
          AltFlag=_AltLocationFlag(run);
          if(AltFlag==' ')
            for(unsigned int i=0;i<Key.size();++i) {
              _AddAtom2Key(Key[i].head(),AN);
              if(RNV[i]==PDBResidueName::Unknown) RNV[i]=_ResidueName(run);
            }
          else {
            n=F[nmodel].AlternativeInfoTable()(AltFlag);
            _AddAtom2Key(Key[n].head(),AN);
            RNV[n]=_ResidueName(run);
          }
        }
      }
      if(run[nl]=='\0')   break;
      run+=nl+1;
    }
  }

  void _GetAtom(const char* _rec, PDB& F) {
    char *run = const_cast<char*>(_rec);
    char AltFlag;
    PDBRecordName RN;
    PDBAtomName AN;
    unsigned int nl,nmodel=0,nmol=0,nres=0,tres,rres=0,nalt;
    nalt=F[nmodel][nmol][nres].size();
    while(true) {
      nl=LineSize(run);
      RN=_RecordName(run);
      if(RN==PDBRecordName::MODEL) { ++nmodel; nmol=0; nres=0; rres=0; }
      else if(RN==PDBRecordName::TER) { ++nmol; nres=0; rres=0; }
      else if(RN==PDBRecordName::ATOM) {
        tres=_ResidueID(run);
        if(rres==0) { rres=tres; nalt=F[nmodel][nmol][nres].size(); }
        if(rres!=tres) { ++nres; rres=tres; nalt=F[nmodel][nmol][nres].size(); }
        AltFlag=_AltLocationFlag(run);
        AN=_AtomName(run);
        if(AltFlag==' ')
          for(unsigned int i=0;i<nalt;++i) {
            F[nmodel][nmol][nres][i].Atom(AN).BFactor()=_BFactor(run);
            F[nmodel][nmol][nres][i].Atom(AN).X()=_PositionX(run);
            F[nmodel][nmol][nres][i].Atom(AN).Y()=_PositionY(run);
            F[nmodel][nmol][nres][i].Atom(AN).Z()=_PositionZ(run);
          }
        else {
          F[nmodel].Residue(nmol,nres,AltFlag).Atom(AN).BFactor()=_BFactor(run);
          F[nmodel].Residue(nmol,nres,AltFlag).Atom(AN).X()=_PositionX(run);
          F[nmodel].Residue(nmol,nres,AltFlag).Atom(AN).Y()=_PositionY(run);
          F[nmodel].Residue(nmol,nres,AltFlag).Atom(AN).Z()=_PositionZ(run);
        }
      }
      if(run[nl]=='\0')   break;
      run+=nl+1;
    }
  }

}

#endif

