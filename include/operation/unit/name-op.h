
#ifndef _Unit_Name_Operation_H_
#define _Unit_Name_Operation_H_

#include "data/unit/name.h"
#include "operation/basic/str-util.h"

namespace std {

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

  bool IsRegisteredUnit(const Vector<char>& uname) {
    return getUnitID(uname)!=NULL;
  }

  const Vector<char>* getUnitName(const unsigned int id) {
    return get(UnitIDResolver,id);
  }

  const Vector<char>* getUnitName(const char* vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:getUnitName(*pID));
  }

  const Vector<char>* getUnitName(const Vector<char>& vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:getUnitName(*pID));
  }

  bool IsRegisteredUnit(const unsigned int id){ return getUnitName(id)==NULL; }

  const Vector<char>* getUnitSimpleName(const unsigned int id) {
    return get(UnitNameSimplifier,id);
  }

  const Vector<char>* getUnitSimpleName(const Vector<char>& vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:getUnitSimpleName(*pID));
  }

  const Vector<char>* getUnitSimpleName(const char* vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:getUnitSimpleName(*pID));
  }

  const char* getUnitCode(const unsigned int id) {
    return get(UnitNameCoder,id);
  }

  const char* getUnitCode(const char* vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:getUnitCode(*pID));
  }

  const char* getUnitCode(const Vector<char>& vname) {
    const unsigned int* pID=getUnitID(vname);
    return (pID==NULL?NULL:getUnitCode(*pID));
  }

}

#endif

