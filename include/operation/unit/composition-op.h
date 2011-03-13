
#ifndef _Unit_Composition_Operation_H_
#define _Unit_Composition_Operation_H_

#include "data/unit/composition.h"

namespace std {

  const unsigned int* getCompositionID(const char* cname) {
    Vector<char> name;
    allocate(name,strlen(cname));
    strncpy(name.data,cname,strlen(cname));
    normalize(name);
    return get(CompositionNameResolver,name);
  }

  const unsigned int* getCompositionID(const Vector<char>& cname) {
    Vector<char> name;
    imprint(name,cname);
    copy(name,cname);
    normalize(name);
    return get(CompositionNameResolver,name);
  }

  const unsigned int* _getCompositionID(const char* rname, const char* cname,
                                        const unsigned int rsize,
                                        const unsigned int csize) {
    Vector<char> name;
    allocate(name,rsize+csize+1);
    strncpy(name.data,rname,rsize);
    name[rsize]=' ';
    strncpy(name.data+rsize+1,cname,csize);
    capitalize(name);
    return get(CompositionNameResolver,name);
  }

  const unsigned int* getCompositionID(const char* rname, const char* cname) {
    return _getCompositionID(rname,cname,strlen(rname),strlen(cname));
  }

  const unsigned int* getCompositionID(const Vector<char>& rname,
                                       const char* cname) {
    return _getCompositionID(rname.data,cname,rname.size,strlen(cname));
  }

  const unsigned int* getCompositionID(const char* rname,
                                       const Vector<char>& cname) {
    return _getCompositionID(rname,cname.data,strlen(rname),cname.size);
  }

  const unsigned int* getCompositionID(const Vector<char>& rname,
                                       const Vector<char>& cname) {
    return _getCompositionID(rname.data,cname.data,rname.size,cname.size);
  }

  bool IsRegisteredComposition(const char* cname) {
    return getCompositionID(cname)!=NULL;
  }

  bool IsRegisteredComposition(const Vector<char>& cname) {
    return getCompositionID(cname)!=NULL;
  }

  bool IsRegisteredComposition(const char* rname, const char* cname) {
    return getCompositionID(rname,cname)!=NULL;
  }

  bool IsRegisteredComposition(const Vector<char>& rname, const char* cname) {
    return getCompositionID(rname,cname)!=NULL;
  }

  bool IsRegisteredComposition(const char* rname, const Vector<char>& cname) {
    return getCompositionID(rname,cname)!=NULL;
  }

  bool IsRegisteredComposition(const Vector<char>& rname,
                               const Vector<char>& cname) {
    return getCompositionID(rname,cname)!=NULL;
  }

  const Vector<char>* getCompositionName(const unsigned int id) {
    return get(CompositionIDResolver,id);
  }

  template <typename ResNameType, typename AtomNameType>
  const Vector<char>* getCompositionName(
      const ResNameType& rname, const AtomNameType& cname) {
    const unsigned int* pID=getCompositionID(rname,cname);
    return (pID==NULL?NULL:getCompositionName(*pID));
  }

  const Vector<char>* getCompositionPDBName(const unsigned int id) {
    return get(CompositionPDBNameResolver,id);
  }

  const Vector<char>* getCompositionPDBName(const char* name) {
    const unsigned int* pID=getCompositionID(name);
    return (pID==NULL?NULL:getCompositionPDBName(*pID));
  }

}

#endif

