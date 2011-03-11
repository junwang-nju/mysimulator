
#ifndef _Map_Element_H_
#define _Map_Element_H_

#include "operation/basic/build-hash.h"

namespace std {

  template <typename KeyType, typename ValueType>
  struct MapElement {

    typedef MapElement<KeyType,ValueType> Type;

    KeyType key;
    ValueType value;
    Hash hash;

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
    return IsAvailable(ME.key)&&IsAvailable(ME.value)&&IsAvailable(ME.hash);
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
  void imprint(MapElement<KeyType,ValueType>& ME,
               const MapElement<KeyType,ValueType>& cME) {
    assert(IsAvailable(cME));
    release(ME);
    imprint(ME.key,cME.key);
    imprint(ME.value,cME.value);
    allocate(ME.hash);
  }

}

#endif

