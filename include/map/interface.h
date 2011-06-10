
#ifndef _Map_Interface_H_
#define _Map_Interface_H_

#include "btree/interface.h"
#include "chain/interface.h"
#include "chain/node/copy.h"
#include "vector/interface.h"
#include "map/element/allocate.h"
#include "map/element/copy.h"
#include "map/hash/compare.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct Map {

    typedef Map<KeyType,ValueType>    Type;
    typedef MapElement<KeyType,ValueType>   ElementType;

    Chain<ElementType> data;
    BTree<MapHash<3>,ChainNode<ElementType> > mesh[0xFFFF];

    Map() : data(), mesh() {}
    Map(const Type&) { Error("Copier of Map Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Map Disabled!");
      return *this;
    }
    ~Map() { clearData(); }

    void clearData() {
      for(unsigned int i=0;i<0xFFFF;++i)  release(mesh[i]);
      release(data);
    }
    void update() {
      for(unsigned int i=0;i<0xFFFF;++i)  release(mesh[i]);
      unsigned int n;
      Object<ChainNode<ElementType> >  nd;
      Object<ElementType> e;
      refer(nd,data.root.child);
      while(!IsSameObject(nd,data.head)) {
        refer(e,nd().content);
        e().update();
        n=(e().hash(0)&0xFFFF0000)>>16;
        mesh[n].insert(e().hash,nd(),Referred,Referred);
        refer(nd,nd().child);
      }
    }
    const ValueType* _find(const ElementType& E) {
      unsigned int n=(E.hash(0)&0xFFFF0000U)>>16;
      ChainNode<ElementType>* pnd=mesh[n].getValue(E.hash);
      return pnd==NULL?NULL:&(pnd->content().value());
    }
    const ValueType* find(const KeyType& key) {
      MapHash<3>  hash;
      allocate(hash);
      key2hash(key,hash);
      unsigned int n=(hash(0)&0xFFFF0000U)>>16;
      const ChainNode<ElementType>* pnd=mesh[n].getValue(hash);
      return pnd==NULL?NULL:&(pnd->content().value());
    }
    bool IsHaveKey(const KeyType& key) { return find(key)!=NULL; }

    void add(const MapElement<KeyType,ValueType>& E,
             const ObjectStateName& flag=Referred) {
      assert(!IsHaveKey(E.key()));
      data.append(E,flag);
      Object<ChainNode<ElementType> > now;
      refer(now,data.head.parent);
      now().content().update();
      unsigned int n=(now().content().hash(0)&0xFFFF0000U)>>16;
      mesh[n].insert(now().content().hash,now(),Referred,Referred);
    }
    void add(const KeyType& key, const ValueType& value,
             const ObjectStateName& kflag=Referred,
             const ObjectStateName& vflag=Referred) {
      assert(!IsHaveKey(key));
      static ElementType E;
      allocate(E);
      data.append(E,Allocated);
      Object<ChainNode<ElementType> > now;
      refer(now,data.head.parent);
      Object<ElementType> e;
      refer(e,now().content);
      allocate(e().hash);
      copy(e().key,key,kflag);
      copy(e().value,value,vflag);
      e().update();
      unsigned int n=(e().hash(0)&0xFFFF0000U)>>16;
      mesh[n].insert(e().hash,now(),Referred,Referred);
    }

    void remove(const KeyType& key) {
      MapHash<3> hash;
      allocate(hash);
      key2hash(key,hash);
      unsigned int n=(hash(0)&0xFFFF0000U)>>16;
      const BTreeNode<MapHash<3>,ChainNode<ElementType> >* pN=
        mesh[n]._getNode(hash);
      ChainNode<ElementType> *pnd=(pN==NULL?NULL:pN->value.pdata);
      mesh[n]._remove(pN);
      if(pnd!=NULL) data._remove(pnd);
    }

  };

  template <typename ktype, typename vtype>
  bool IsValid(const Map<ktype,vtype>& M) {
    return IsValid(M.data)&&IsValid(M.mesh);
  }
  template <typename ktype, typename vtype>
  void release(Map<ktype,vtype>& M) { M.clearData(); }

}

#endif

