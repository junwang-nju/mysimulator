
#ifndef _Build_Hash_H_
#define _Build_Hash_H_

#include "operation/basic/hash-func.h"
#include "data/basic/hash.h"

namespace std {

  template <typename T>
  void buildHash(const T& key, Hash& hash) {
    buildHash(key,static_cast<Vector<unsigned int>&>(hash));
  }

  void buildHash(const char* key, const unsigned int nkey, unsigned int* hash){
    hash[0]=hash_ap(key,nkey);
    hash[1]=hash_dek(key,nkey);
    hash[2]=hash_bp(key,nkey);
  }

  void buildHash(const Vector<unsigned int>& key, unsigned int* hash) {
    unsigned int hsize=key.size*4;
    buildHash(reinterpret_cast<const char*>(key.data),hsize,hash);
  }

  void buildHash(const Vector<unsigned int>& key, Vector<unsigned int>& hash) {
    assert(hash.size==3);
    buildHash(key,hash.data);
  }

  void buildHash(const Vector<char>& key, unsigned int* hash) {
    buildHash(key.data,key.size,hash);
  }

  void buildHash(const Vector<char>& key, Vector<unsigned int>& hash) {
    assert(hash.size==3);
    buildHash(key,hash.data);
  }

  void buildHash(const unsigned int& key, unsigned int* hash) {
    const char* pkey=reinterpret_cast<const char*>(&key);
    buildHash(pkey,4,hash);
  }

  void buildHash(const unsigned int& key, Vector<unsigned int>& hash) {
    assert(hash.size==3);
    buildHash(key,hash.data);
  }

}

#endif

