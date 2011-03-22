
#ifndef _Unit_Property_Operation_H_
#define _Unit_Property_Operation_H_

#include "data/unit/property.h"

namespace std {

  bool IsHeavyAtom(const unsigned int id) {
    const bool* fg=get(HeavyAtomFlag,id);
    if(fg==NULL)  { Warn("Unknown Atom ID"); return false; }
    return *fg;
  }

  bool IsHeavyAtom(const char* name) {
    const unsigned int* id=getCompositionID(name);
    if(id==NULL) { Warn("Unknown Atom Name"); return false; }
    else return IsHeavyAtom(*id);
  }

}

#endif

