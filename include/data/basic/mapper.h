
#ifndef _Mapper_H_
#define _Mapper_H_

#include "data/basic/btree.h"
#include "data/basic/vector.h"

namespace std {

  template <typename KeyType, typename ValueType>
  struct Mapper : public Vector<BTree<KeyType,ValueType> > {
    typedef Mapper<KeyType,ValueType> Type;
    typedef BTree<KeyType,ValueType>  MapTreeType;
    typedef Vector<MapTreeType> ParentType;

    unsigned int size;
    KeyType* key;
    ValueType* value;

    Mapper() : ParentType(), size(0), key(NULL), value(NULL) {}
    Mapper(const Type&) { Error("Cannot create Mapper"); }
    Type& operator=(const Type&) {
      Error("Cannotcopy Mapper");
      return *this;
    }
    ~Mapper() { release(*this); }

    void update() {
      IsAvailable(static_cast<ParentType&>(*this));
      for(unsigned int i=0;i<0xFFFFU;++i) release(this->operator[](i));
      for(unsigned int i=0,n;i<size;++i) {
        key[i].update();
        n=(key[i].hash[0]&0xFFFF0000U)>>16;
        insert(this->operator[](n),key[i],value[i]);
      }
    }
  };

  template <typename KeyType, typename ValueType>
  bool IsAvailable(const Mapper<KeyType,ValueType>& L) {
    typedef typename Mapper<KeyType,ValueType>::ParentType  Type;
    return IsAvailable(static_cast<const Type&>(L));
  }

  template <typename KeyType, typename ValueType>
  void release(Mapper<KeyType,ValueType>& L) {
    L.size=0;
    if(L.state==Allocated) {
      safe_delete_array(L.key);
      safe_delete_array(L.value);
    } else {
      L.key=NULL;
      L.value=NULL;
    }
    typedef typename Mapper<KeyType,ValueType>::ParentType  Type;
    release(static_cast<Type&>(L));
  }

  template <typename KeyType, typename ValueType>
  void copy(Mapper<KeyType,ValueType>& L, const Mapper<KeyType,ValueType>& cL){
    assert(IsAvailable(L));
    assert(IsAvailable(cL));
    unsigned int n=(L.size<cL.size?L.size:cL.size);
    for(unsigned int i=0;i<n;++i) {
      copy(L.key[i],cL.key[i]);
      copy(L.value[i],cL.value[i]);
    }
    L.update();
  }

  template <typename KeyType, typename ValueType>
  void refer(Mapper<KeyType,ValueType>& L,const Mapper<KeyType,ValueType>& rL){
    assert(IsAvailable(rL));
    release(L);
    L.size=rL.size;
    L.key=rL.key;
    L.value=rL.value;
    typedef typename Mapper<KeyType,ValueType>::ParentType  Type;
    refer(static_cast<Type&>(L),static_cast<const Type&>(rL));
  }

  template <typename KeyType, typename ValueType>
  const ValueType* get(const Mapper<KeyType,ValueType>& L, const KeyType& K) {
    unsigned int n=(K.hash[0]&0xFFFF0000U)>>16;
    return get(L[n],K);
  }

}

#endif

