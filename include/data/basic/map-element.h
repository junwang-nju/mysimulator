
#ifndef _Map_Element_H_
#define _Map_Element_H_

#include "data/basic/vector.h"

namespace std {

  template <typename KeyType, typename ValueType>
  struct MapElement {

    typedef MapElement<KeyType,ValueType> Type;

    KeyType key;
    ValueType value;
    Vector<unsigned int> hash;

    MapElement() : key(), value(), hash() {}
    MapElement(const Type&) { Error("Cannot create Map Element"); }
    Type& operator=(const Type&) {
      Error("Cannot copy Map Element");
      return *this;
    }
    ~MapElement() { release(*this); }

    void update() { buildHash(key,hash); }

  };

  template <typename KeyType, typename ValueType>
  bool IsAvailable(const MapElement<KeyType,ValueType>& ME) {
    return IsAvailable(ME.key)&&IsAvailable(ME.value);
  }

  template <typename KeyType, typename ValueType>
  void release(MapElement<KeyType,ValueType>& ME) {
    release(ME.key);
    release(ME.value);
    release(ME.hash);
  }

  template <typename KeyType, typename ValueType>
  void copy(MapElement<KeyType,ValueType>& ME,
            const MapElement<KeyType,ValueType>& cME) {
    assert(IsAvailable(ME));
    assert(IsAvailable(cME));
    copy(ME.key,cME.key);
    copy(ME.value,cME.value);
    copy(ME.hash,cME.hash);
  }

  template <typename KeyType, typename ValueType>
  void refer(MapElement<KeyType,ValueType>& ME,
             const MapElement<KeyType,ValueType>& rME) {
    assert(IsAvailable(rME));
    release(ME);
    refer(ME.key,rME.key);
    refer(ME.value,rME.value);
    refer(ME.hash,rME.hash);
  }

  template <typename KeyType, typename ValueType>
  void allocateHash(MapElement<KeyType,ValueType>& ME) {
    allocate(ME.hash,3);
    copy(ME.hash,0);
  }

  template <typename KeyType, typename ValueType>
  void imprint(MapElement<KeyType,ValueType>& ME,
               const MapElement<KeyType,ValueType>& cME) {
    assert(IsAvailable(cME));
    release(ME);
    imprint(ME.key,cME.key);
    imprint(ME.value,cME.value);
    allocateHash(ME);
  }

  template <typename KeyType, typename ValueType>
  int compare(const MapElement<KeyType,ValueType>& MEa,
              const MapElement<KeyType,ValueType>& MEb) {
    assert(MEa.hash.size==3);
    assert(MEb.hash.size==3);
    for(unsigned int i=0;i<3;++i)
      if(MEa.hash[i]!=MEb.hash[i])  return (MEa.hash[i]>MEb.hash[i]?1:-1);
    return 0;
  }

}

#endif

