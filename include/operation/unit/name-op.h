
#ifndef _Unit_Name_Operation_H_
#define _Unit_Name_Operation_H_

#include "data/unit/name.h"

namespace std {

  void normalize(char* name, const unsigned int size) {
    if(islower(name[0]))  name[0]=toupper(name[0]);
    for(unsigned int i=1;i<size;++i) {
      if((name[i-1]=='-')&&islower(name[i]))  name[i]=toupper(name[i]);
      else name[i]=tolower(name[i]);
    }
  }

  void normalize(Vector<char>& name) { normalize(name.data,name.size); }

  const unsigned int* getUnitID(const char* uname) {
    Vector<char> name;
    allocate(name,strlen(uname));
    strncpy(name.data,uname,strlen(uname));
    normalize(name);
    return get(UnitNameResolver,name);
  }

  const unsigned int* getUnitID(const Vector<char>& uname) {
    Vector<char> name;
    imprint(name,uname);
    copy(name,uname);
    normalize(name);
    return get(UnitNameResolver,name);
  }

  bool IsRegisteredUnit(const char* uname) { return getUnitID(uname)!=NULL; }

  const Vector<char>* getUnitName(const unsigned int id) {
    return get(UnitIDResolver,id);
  }

  const Vector<char>* getUnitName(const char* vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:get(UnitIDResolver,*pID));
  }

  const Vector<char>* getUnitName(const Vector<char>& vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:get(UnitIDResolver,*pID));
  }

  const Vector<char>* getUnitSimpleName(const unsigned int id) {
    return get(UnitNameSimplifier,id);
  }

  const Vector<char>* getUnitSimpleName(const Vector<char>& vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:get(UnitNameSimplifier,*pID));
  }

  const Vector<char>* getUnitSimpleName(const char* vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:get(UnitNameSimplifier,*pID));
  }

}

#endif

