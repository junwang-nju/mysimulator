
#ifndef _Map_Operation_H_
#define _Map_Operation_H_

#include "data/basic/map.h"
#include "data/basic/console-output.h"

namespace std {

  template <typename KeyType, typename ValueType>
  const ValueType* get(const Map<KeyType,ValueType>& M,
                       const MapElement<KeyType,ValueType>& ME) {
    unsigned int n=(ME.hash[0]&0xFFFF0000U)>>16;
    ChainNode<MapElement<KeyType,ValueType> > pTV=get(M[n],ME.hash);
    return (pTV==NULL?NULL:&(pTV->content->value));
  }

  template <typename KeyType, typename ValueType>
  const ValueType* get(const Map<KeyType,ValueType>& M, const KeyType& K) {
    Hash hash;
    allocate(hash);
    buildHash(K,hash);
    unsigned int n=(hash[0]&0xFFFF0000U)>>16;
    const ChainNode<MapElement<KeyType,ValueType> > *pTV=get(M[n],hash);
    return (pTV==NULL?NULL:&(pTV->content->value));
  }

  template <typename KeyType, typename ValueType>
  bool IsHaveKey(const Map<KeyType,ValueType>& M, const KeyType& K) {
    return get(M,K)!=NULL;
  }

  template <typename KeyType, typename ValueType>
  void add(Map<KeyType,ValueType>& M, const MapElement<KeyType,ValueType>& ME,
           const unsigned int cflag=Reference) {
    assert(!IsHaveKey(M,ME.key));
    append(M.MapData,ME,cflag);
    ChainNode<MapElement<KeyType,ValueType> > *now=M.MapData.head->parent;
    now->content->update();
    unsigned int n=(now->content->hash[0]&0xFFFF0000U)>>16;
    insert(M[n],now->content->hash,*now);
  }

  template <typename KeyType, typename ValueType>
  void add(Map<KeyType,ValueType>& M, const KeyType& K, const ValueType& V,
           const unsigned int kflag=Reference,
           const unsigned int vflag=Reference) {
    assert(!IsHaveKey(M,K));
    static MapElement<KeyType,ValueType> ME;
    append(M.MapData,ME,Allocated);
    ChainNode<MapElement<KeyType,ValueType> > *now=M.MapData.head->parent;
    MapElement<KeyType,ValueType> *pME=now->content;
    allocate(pME->hash);
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
    pME->update();
    unsigned int n=(pME->hash[0]&0xFFFF0000U)>>16;
    insert(M[n],pME->hash,*now);
  }

  template <typename KeyType, typename ValueType>
  void remove(Map<KeyType,ValueType>& M, const KeyType& key) {
    Hash hash;
    allocate(hash);
    buildHash(key,hash);
    unsigned int n=(hash[0]&0xFFFF0000U)>>16;
    const ChainNode<MapElement<KeyType,ValueType> > *pTV=get(M[n],hash);
    if(pTV==NULL) return;
    removeNode(M[n],hash);
    remove(M.MapData,pTV);
  }

}

#endif

