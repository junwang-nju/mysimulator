
#ifndef _Map_H_
#define _Map_H_

#include "data/basic/btree.h"
#include "data/basic/chain.h"
#include "data/basic/map-element.h"

namespace std {

  template <typename KeyType, typename ValueType>
  struct Map : public Vector<
                        BTree<KeyType,
                              ChainNode<MapElement<KeyType,ValueType> > > > {

    typedef Map<KeyType,ValueType>  Type;
    typedef ChainNode<MapElement<KeyType,ValueType> >  TreeValueType;
    typedef BTree<KeyType,TreeValueType>  MapTreeType;
    typedef Vector<MapTreeType> ParentType;

    Chain<MapElement<KeyType,ValueType> > MapData;

    Map() : ParentType(), MapData() {}
    Map(Type&) { Error("Cannot create Map"); }
    Type& operator=(const Type&) {
      Error("Cannot copy map");
      return *this;
    }
    ~Map() { release(*this); }
    void update() {
      unsigned int n;
      TreeValueType *pTV=MapData.root->child;
      MapElement<KeyType,ValueType> *pME;
      while(pTV!=MapData.head) {
        pME=pTV->content;
        pME->update();
        n=(pME->hash[0]&0xFFFF0000U)>>16;
        insert(this->operator[](n),pME->key,*pTV);
        pTV=pTV->child;
      }
    }

  };

  template <typename KeyType, typename ValueType>
  bool IsAvailable(const Map<KeyType,ValueType>& M) {
    typedef typename Map<KeyType,ValueType>::ParentType Type;
    return IsAvailable(static_cast<const Type&>(M))&&IsAvailable(M.MapData);
  }

  template <typename KeyType, typename ValueType>
  void release(Map<KeyType,ValueType>& M) {
    typedef typename Map<KeyType,ValueType>::ParentType Type;
    release(static_cast<Type&>(M));
    release(M.MapData);
  }

  template <typename KeyType, typename ValueType>
  void copy(Map<KeyType,ValueType>& M, const Map<KeyType,ValueType>& cM) {
    assert(IsAvailable(M));
    assert(IsAvailable(cM));
    copy(M.MapData,cM.MapData);
    M.update();
  }

  template <typename KeyType, typename ValueType>
  void refer(Map<KeyType,ValueType>& M, Map<KeyType,ValueType>& rM) {
    assert(IsAvailable(rM));
    release(M);
    refer(M.MapData,rM.MapData);
    typedef typename Map<KeyType,ValueType>::ParentType Type;
    refer(static_cast<Type&>(M),static_cast<const Type&>(rM));
  }

}

#endif

