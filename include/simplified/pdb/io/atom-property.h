
#ifndef _PDB_IO_Atom_Property_H_
#define _PDB_IO_Atom_Property_H_

#include "pdb/io/record-name.h"
#include "basic/util/string.h"
#include <cassert>
#include <cstdlib>

namespace mysimulator {

  double _BFactor(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    char str[9];
    SubString(str,_rec,60,65);
    return atof(str);
  }

  double _PositionX(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    char str[9];
    SubString(str,_rec,30,37);
    return atof(str);
  }

  double _PositionY(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    char str[9];
    SubString(str,_rec,38,45);
    return atof(str);
  }

  double _PositionZ(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    char str[9];
    SubString(str,_rec,46,53);
    return atof(str);
  }

  char _AltLocationFlag(const char* _rec) {
    assert(_RecordName(_rec) == PDBRecordName::ATOM);
    return _rec[16];
  }

}

#endif

