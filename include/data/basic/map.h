
#ifndef _Map_H_
#define _Map_H_

#include "data/basic/btree.h"
#include "data/basic/chain.h"
#include "data/basic/map-element.h"

namespace std {

  template <typename KeyType, typename ValueType>
  struct Map : public Vector<BTree<KeyType,ValueType> > {

    typedef Map<KeyType,ValueType>  Type;
    typedef BTree<KeyType,ValueType>  MapTreeType;
    typedef Vector<MapTreeType> ParentType;

    Chain<MapElement<KeyType,ValueType> > MapData;

    Map() : ParentType(), MapData() {}
    Map(Type&) { Error("Cannot create Map"); }
    Map(const Type&) {
      Error("Cannot copy map");
      return *this;
    }
    ~Map() { release(*this); }
    void update() {
      unsigned int n;
      MapElement<KeyType,ValueType> *pME=MapData.root->child;
      while(pME!=MapData.head) {
        pME->update();
        n=(pME->hash[0]&0xFFFF0000U)>>16;
        insert(this->operator[](n),pME->key,pME->value);
        pME=pME->child;
      }
    }

  };

  template <typename KeyType, typename ValueType>
  bool IsAvailable(const Map<KeyType,ValueType>& M) {
    typedef Vector<BTree<KeyType,ValueType> >  Type;
    return IsAvailable(static_cast<const Type&>(M))&&IsAvailable(M.MapData);
  }

  template <typename KeyType, typename ValueType>
  void release(Map<KeyType,ValueType>& M) {
    typedef Vector<BTree<KeyType,ValueType> >  Type;
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
    release(M.MapData,rM.MapData);
    typedef Vector<BTree<KeyType,ValueType> >  Type;
    refer(static_cast<Type&>(M),static_cast<const Type&>(rM));
  }

}

#endif

