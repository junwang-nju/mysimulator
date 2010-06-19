
#ifndef _PDB_Data_ID_H_
#define _PDB_Data_ID_H_

#include "error-proc.h"
#include <cstring>

namespace std {

  struct PDBID;

  void assign(PDBID&,const PDBID&);

  struct PDBID {
    char name[5];
    PDBID() { name[4]=0; }
    PDBID(const PDBID&) { myError("Cannot create from PDB ID"); }
    PDBID& operator=(const PDBID& pid) { assign(*this,pid); return *this; }
    const char* operator()() const { return name; }
  };

  void assign(PDBID& dest, const PDBID& src) { strncpy(dest.name,src.name,4); }

  void Set(PDBID& pid, const char* name) { strncpy(pid.name,name,4); }

}

#endif

