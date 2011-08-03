
#ifndef _Key_To_Hash_H_
#define _Key_To_Hash_H_

#include "map/hash/func.h"

namespace mysimulator {

  void _key2hash_3element(const char* const& key, const unsigned int& nkey,
                          unsigned int hash[3]) {
    hash[0]=hash_ap(key,nkey);
    hash[1]=hash_dek(key,nkey);
    hash[2]=hash_bp(key,nkey);
  }

}

#endif

