
#ifndef _Map_Operation_H_
#define _Map_Operation_H_

#include "data/basic/map.h"

namespace std {

  template <typename KeyType, typename ValueType>
  const ValueType* get(const Map<KeyType,ValueType>& M,
                       const MapElement<KeyType,ValueType>& ME) {
    unsigned int n=(ME.hash[0]&0xFFFF0000U)>>16;
    return get(M[n],ME.key);
  }

  template <typename KeyType, typename ValueType>
  const ValueType* get(const Map<KeyType,ValueType>& M, const KeyType& K) {
    unsigned int hash[3];
    buildHash(K,hash);
    unsigned int n=(hash[0]&0xFFFF0000U)>>16;
    return get(M[n],K);
  }

}

#endif

