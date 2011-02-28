
#ifndef _PDB_Unit_Name_Mapper_H_
#define _PDB_Unit_Name_Mapper_H_

#include "data/basic/mapper.h"
#include "operation/basic/hash-func.h"

namespace std {

  struct PDBUnitKey : public Vector<char> {
    Vector<unsigned int> hash;

    typedef Vector<char>  ParentType;

    PDBUnitKey() : ParentType(NULL), hash(3) {}
    PDBUnitKey(const PDBUnitKey&) { Error("Cannot create PDB Unit Key"); }
    PDBUnitKey& operator=(const PDBUnitKey&) {
      Error("Cannot copy PDB Unit Key");
      return *this;
    }
    ~PDBUnitKey() { release(*this); }
    void update() {
      hash[0]=hash_ap(data,7);
      hash[1]=hash_dek(data,7);
      hash[2]=hash_bp(data,7);
    }
  };

  bool IsAvailable(const PDBUnitKey& K) {
    return IsAvailable(static_cast<const Vector<char>&>(K));
  }
  void release(PDBUnitKey& K) {
    release(K.hash);
    release(static_cast<Vector<char>&>(K));
  }
  void copy(PDBUnitKey& K, const PDBUnitKey& cK) {
    assert(IsAvailable(K));
    assert(IsAvailable(cK));
    copy(static_cast<Vector<char>&>(K),static_cast<const Vector<char>&>(cK));
    copy(K.hash,cK.hash);
  }
  void refer(PDBUnitKey&K, const PDBUnitKey& rK) {
    assert(IsAvailable(rK));
    release(K);
    refer(static_cast<Vector<char>&>(K),static_cast<const Vector<char>&>(rK));
    refer(K.hash,rK.hash);
  }

  void allocate(PDBUnitKey& K) {
    release(K);
    allocate(static_cast<Vector<char>&>(K),8);
    copy(K,'\0');
    allocate(K.hash,3);
    copy(K.hash,0);
  }
  void imprint(PDBUnitKey& K, const PDBUnitKey& cK) { allocate(K); }

  int compare(const PDBUnitKey& K1, const PDBUnitKey& K2) {
    for(unsigned int i=0;i<3;++i)
      if(K1.hash[i]!=K2.hash[i]) return (K1.hash[i]>K2.hash[i]?1:-1);
    return 0;
  }

  void Set(PDBUnitKey& K, const char* resname) {
    strncpy(K.data,resname,3);
  }

  void Set(PDBUnitKey& K, const char *resname, const char *atomname) {
    strncpy(K.data,resname,3);
    strncpy(K.data+3,atomname,4);
  }

  typedef unsigned int  PDBUnitNameValueType;

  typedef Mapper<PDBUnitKey,PDBUnitNameValueType>  PDBUnitNameMapper;

  void allocate(PDBUnitNameMapper& M, const unsigned int nitem) {
    M.size=nitem;
    M.key=new PDBUnitKey[nitem];
    for(unsigned int i=0;i<nitem;++i) allocate(M.key[i]);
    M.value=new PDBUnitNameValueType[nitem];
  }

}

#endif

