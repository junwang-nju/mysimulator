
#ifndef _Map_Operation_H_
#define _Map_Operation_H_

#include "data/basic/map.h"

namespace std {

  template <typename KeyType, typename ValueType>
  const ValueType* get(const Map<KeyType,ValueType>& M,
                       const MapElement<KeyType,ValueType>& ME) {
    unsigned int n=(ME.hash[0]&0xFFFF0000U)>>16;
    ChainNode<MapElement<KeyType,ValueType> > pTV=get(M[n],ME.key);
    return (pTV==NULL?NULL:&(pTV->content->value));
  }

  template <typename KeyType, typename ValueType>
  const ValueType* get(const Map<KeyType,ValueType>& M, const KeyType& K) {
    unsigned int hash[3];
    buildHash(K,hash);
    unsigned int n=(hash[0]&0xFFFF0000U)>>16;
    ChainNode<MapElement<KeyType,ValueType> > pTV=get(M[n],K);
    return (pTV==NULL?NULL:&(pTV->content->value));
  }

  template <typename KeyType, typename ValueType>
  bool IsHaveKey(const Map<KeyType,ValueType>& M, const KeyType& K) {
    return get(M,K)!=NULL;
  }

  template <typename KeyType, typename ValueType>
  void add(Map<KeyType,ValueType>& M, const MapElement<KeyType,ValueType>& ME,
           const unsigned int cflag=Reference) {
    assert(!IsHaveKey(ME,ME.key));
    append(M.MapData,ME,cflag);
    ChainNode<MapElement<KeyType,ValueType> > *now=ME.MapData.head->parent;
    now->content->update();
    unsigned int n=(now->content->hash[0]&0xFFFF0000U)>>16;
    insert(MP[n],now->content->key,now);
  }

  template <typename KeyType, typename ValueType>
  void add(Map<KeyType,ValueType>& M, const KeyType& K, const ValueType& V,
           const unsigned int kflag=Reference,
           const unsigned int vflag=Reference) {
    assert(!IsHaveKey(M,K));
    MapElement<KeyType,ValueType> *pME=new MapElement<KeyType,ValueType>;
    if(kflag==Allocated) {
      imprint(pME->key,K);
      copy(pME->key,K);
    } else if(kflag==Reference) refer(pME->key,K);
    else Error("Unknown element assign mode!");
    if(vflag==Allocated) {
      imprint(pME->value,V);
      copy(pME->value,V);
    } else if(vflag==Reference) refer(pME->value,V);
    else Error("Unknown element assign mode!");
    add(M,*pME);
  }

  template <typename KeyType, typename ValueType>
  void remove(Map<KeyType,ValueType>& M, const KeyType& key) {
    unsigned int hash[3];
    buildHash(key,hash);
    unsigned int n=(hash[0]&0xFFFF0000U)>>16;
    ChainNode<MapElement<KeyType,ValueType> > *pTV=get(M[n],key);
    if(pTV==NULL) return;
    remove(M.MapData,pTV);
    removeNode(M[n],key);
  }

}

#endif

