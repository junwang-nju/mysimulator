
#ifndef _PDB_IO_Get_Number_H_
#define _PDB_IO_Get_Number_H_

#include "pdb/io/record-name.h"
#include "basic/util/string.h"

namespace mysimulator {

  unsigned int NumberModel(const char* _rec) {
    char *run = const_cast<char*>(_rec);
    unsigned int nl=0,nmodel=0;
    PDBRecordName RN;
    while(true) {
      nl=LineSize(run);
      if(RecordName()==PDBRecordName::MODEL)  ++nmodel;
      if(run[nl]=='\0')   break;
      run+=nl+1;
    }
    return nmodel==0 ? 1 : nmodel;
  }

  unsigned int NumberMolecule(const char* _rec) {
    char *run = const_cast<char*>(_rec);
    unsigned int nl=0,  nmol=0;
    PDBRecordName RN;
    while(true) {
      nl=LineSize(run);
      RN=RecordName(run);
      if(RN==PDBRecordName::TER)  ++nmol;
      else if(RN==PDBRecordName::ENDMDL)  break;
      if(run[nl]=='\0')   break;
      run+=nl+1;
    }
    return nmol;
  }

}

#include "array/interface.h"
#include "pdb/io/tag-property.h"

namespace mysimulator {

  template <ArrayKernelName K>
  void NumberResidue(Array<UInt,K>& NumberRes, unsigned int nmodel=0) {
    assert(NumberRes.size()==NumberMolecule());
    char *run = const_cast<char*>(_rec);
    unsigned int nl=0,rmodel=0;
    while(rmodel<nmodel) {
      nl=LineSize(run);
      if(RecordName()==PDBRecordName::ENDMDL) ++rmodel;
      if(run[nl]=='\0')   break;
      run+=nl+1;
    }
    if(rmodel<nmodel) { fprintf(stderr,"Expect Model Not Exist!\n"); return; }
    unsigned int nmol=0, nres=0, tres=0, rres=0;
    PDBRecordName RN;
    while(true) {
      nl=LineSize(run);
      RN=RecordName();
      if(RN==PDBRecordName::ATOM) {
        tres=ResidueID();
        if(tres!=rres)  { ++nres; rres=tres; }
      } else if(RN==PDBRecordName::TER) {
        NumberRes[nmol]=nres;
        ++nmol;
        nres=0;
      } else if(RN==PDBRecordName::ENDMDL)  break;
      if(run[nl]=='\0')   break;
      run+=nl+1;
    }
  }

}

#endif

