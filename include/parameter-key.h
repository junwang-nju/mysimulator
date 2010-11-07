
#ifndef _Parameter_Key_H_
#define _Parameter_Key_H_

#include "hash-func.h"
#include "vector.h"

namespace std {

  struct ParameterKey : public Vector<unsigned int> {
    unsigned int hsize;
    Vector<unsigned int> hash;
    
    typedef ParameterKey  Type;
    typedef Vector<unsigned int> ParentType;
    
    ParameterKey() : ParentType(), hsize(0), hash(3) { copy(hash,0); }
    ParameterKey(const Type& K) { myError("Cannot create Parameter Key"); }
    Type& operator=(const Type& K) {
      myError("Cannot copy Parameter Key");
      return *this;
    }
    ~ParameterKey() { release(*this); }
    
    void update() {
      hash[0]=hash_ap(reinterpret_cast<char*>(this->data),hsize);
      hash[1]=hash_dek(reinterpret_cast<char*>(this->data),hsize);
      hash[2]=hash_bp(reinterpret_cast<char*>(this->data),hsize);
    }
  };

  bool IsAvailable(const ParameterKey& K) {
    return IsAvailable(static_cast<const Vector<unsigned int>&>(K));
  }

  void copy(ParameterKey& K, const ParameterKey& cK) {
    assert(IsAvailable(K));
    assert(IsAvailable(cK));
    copy(static_cast<Vector<unsigned int>&>(K),
         static_cast<const Vector<unsigned int>&>(cK));
    copy(K.hsize,cK.hsize);
    copy(K.hash,cK.hash);
  }

  void release(ParameterKey& K) {
    K.hsize=0;
    release(K.hash);
    release(static_cast<Vector<unsigned int>&>(K));
  }

  void allocate(ParameterKey& K, const unsigned int nidx) {
    release(K);
    allocate(static_cast<Vector<unsigned int>&>(K),nidx);
    copy(K,0);
    K.hsize=4*nidx;
    allocate(K.hash,3);
    copy(K.hash,0);
  }

  void refer(ParameterKey& K, const ParameterKey& rK) {
    assert(IsAvailable(rK));
    release(K);
    refer(static_cast<Vector<unsigned int>&>(K),
          static_cast<const Vector<unsigned int>&>(rK));
    K.hsize=rK.hsize;
    refer(K.hash,rK.hash);
  }

  istream& operator>>(istream& is, ParameterKey& K) {
    is>>static_cast<Vector<unsigned int>&>(K); K.update(); return is;
  }

  int compare(const ParameterKey& KA, const ParameterKey& KB) {
    for(int i=0;i<3;++i)
      if(KA.hash[i]!=KB.hash[i]) return (KA.hash[i]>KB.hash[i]?1:-1);
    return 0;
  }

}

#endif
