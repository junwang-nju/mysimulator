
#ifndef _PDB_Contact_Map_H_
#define _PDB_Contact_Map_H_

#include "data/derived/parameter-key.h"
#include "data/basic/mapper.h"

namespace std {

  typedef Mapper<ParameterKey,char>   ContactMap;

  void allocate(ContactMap& CM, const unsigned int nc) {
    release(CM);
    typedef BTree<ParameterKey,char> TreeType;
    allocate(static_cast<Vector<TreeType>&>(CM),0xFFFFU);
    CM.size=nc;
    CM.key=new ParameterKey[nc];
    for(unsigned int i=0;i<nc;++i)  allocate(CM.key[i],2);
    CM.value=new char[nc];
  }

  void imprint(ContactMap& CM, const ContactMap& cCM) {
    allocate(CM,cCM.size);
  }

  const char* get(const ContactMap& CM,
                  const unsigned int id1, const unsigned int id2) {
    char* name;
    static ParameterKey K;
    allocate(K,2);
    K[0]=id1;
    K[1]=id2;
    K.update();
    name=const_cast<char*>(get(CM,K));
    if(name==NULL) {
      K[0]=id1;
      K[1]=id2;
      K.update();
      name=const_cast<char*>(get(CM,K));
    }
    return name;
  }

  const char* get(const ContactMap& CM, const unsigned int* idx,
                  const unsigned int offset=0, const unsigned int step=1) {
    return get(CM,idx[offset],idx[offset+step]);
  }

  const char* get(ContactMap& CM, const Vector<unsigned int>& idx) {
    return get(CM,idx.data);
  }

  void Set(const ContactMap& CM, const unsigned int n,
           const unsigned int id1, const unsigned int id2) {
    CM.key[n][0]=id1;
    CM.key[n][1]=id2;
    CM.key[n].update();
  }

}

#endif

