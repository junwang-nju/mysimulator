
#ifndef _PDB_IO_Record_Name_H_
#define _PDB_IO_Record_Name_H_

#include <cstring>

namespace mysimulator {

  enum class PDBRecordName {
    ATOM,
    MODEL,
    ENDMDL,
    TER,
    NotImplemented
  };

  PDBRecordName RecordName(const char* _rec) {
    if(strncmp(_rec,"ATOM  ",6)==0)         return PDBRecordName::ATOM;
    else if(strncmp(_rec,"MODEL ",6)==0)    return PDBRecordName::MODEL;
    else if(strncmp(_rec,"ENDMDL",6)==0)    return PDBRecordName::ENDMDL;
    else if(strncmp(_rec,"TER   ",6)==0)    return PDBRecordName::TER;
    return PDBRecordName::NotImplemented;
  }

}

#endif

