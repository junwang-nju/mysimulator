
#ifndef _PDB_IO_Tag_Property_H_
#define _PDB_IO_Tag_Property_H_

#include "pdb/io/record-name.h"
#include "basic/util/string.h"

namespace mysimulator {

  unsigned int ChainTag(const char* _rec) {
    assert(RecordName() == PDBRecordName::ATOM);
    return (unsigned int)(_rec[21]);
  }

  unsigned int ResidueID(const char* _rec) {
    assert(RecordName() == PDBRecordName::ATOM);
    char str[6];
    SubString(str,_rec,22,25);
    return (unsigned int)atoi(str);
  }

}

#endif

