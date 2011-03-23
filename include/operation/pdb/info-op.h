
#ifndef _PDB_Information_Operation_H_
#define _PDB_Information_Operation_H_

#include "data/pdb/info.h"
#include "operation/unit/name-op.h"

namespace std {

  bool CheckLineProperty(const char* lflag, const char* signature) {
    return strncmp(lflag,signature,6)==0;
  }

}

#endif

