
#ifndef _Build_Hash_H_
#define _Build_Hash_H_

#include "operation/basic/hash-func.h"
#include "data/basic/hash.h"

namespace std {

  void buildHash(const Vector<unsigned int>& key, unsigned int* hash) {
    unsigned int hsize=key.size*4;
    hash[0]=hash_ap(reinterpret_cast<const char*>(key.data),hsize);
    hash[1]=hash_dek(reinterpret_cast<const char*>(key.data),hsize);
    hash[2]=hash_bp(reinterpret_cast<const char*>(key.data),hsize);
  }

  void buildHash(const Vector<unsigned int>& key, Vector<unsigned int>& hash) {
    assert(hash.size==3);
    buildHash(key,hash.data);
  }

  void buildHash(const Vector<unsigned int>& key, Hash& hash) {
    buildHash(key,static_cast<Vector<unsigned int>&>(hash));
  }

}

#endif

