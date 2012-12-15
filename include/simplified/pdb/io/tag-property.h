
#ifndef _PDB_IO_Tag_Property_H_
#define _PDB_IO_Tag_Property_H_

#include "pdb/io/record-name.h"
#include "basic/util/string.h"
#include <cassert>

namespace mysimulator {

  unsigned int _ChainTag(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    return (unsigned int)(_rec[21]);
  }

  int _ResidueID(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    char str[6];
    SubString(str,_rec,22,25);
    return atoi(str);
  }

}

#endif

