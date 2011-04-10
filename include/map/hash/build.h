
#ifndef _Map_Element_Hash_Build_H_
#define _Map_Element_Hash_Build_H_

#include "map/hash/interface.h"

namespace mysimulator {

  template <typename T, unsigned int nhash>
  void key2hash(const T& key, MapHash<nhash>& hash) {
    Error("Key2Hash for Hash with this size Not Implemented!");
  }

}

#include "hash/func.h"

namespace mysimulator {

  void _key2hash(const char* const& key, const unsigned int nkey, MapHash<3>& h) {
    h(0)=hash_ap(key,nkey);
    h(1)=hash_dek(key,nkey);
    h(2)=hash_bp(key,nkey);
  }

}

#include "vector/interface.h"

namespace mysimulator {

  void key2hash(const Vector<char>& key, MapHash<3>& h) {
    _key2hash(key.pdata,key.size,h);
  }

  void key2hash(const Vector<unsigned int>& key, MapHash<3>& h) {
    _key2hash(reinterpret_cast<char* const&>(key.pdata),key.size*4,h);
  }

  void key2hash(const Vector<int>& key, MapHash<3>& h) {
    _key2hash(reinterpret_cast<char* const&>(key.pdata),key.size*4,h);
  }

  void key2hash(const unsigned int& key, MapHash<3>& h) {
    unsigned int* pkey=const_cast<unsigned int*>(&key);
    _key2hash(reinterpret_cast<char* const&>(pkey),4,h);
  }

  void key2hash(const int& key, MapHash<3>& h) {
    int* pkey=const_cast<int*>(&key);
    _key2hash(reinterpret_cast<char* const&>(pkey),4,h);
  }

}

#endif

