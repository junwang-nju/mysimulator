
#ifndef _Map_Element_Interface_H_
#define _Map_Element_Interface_H_

#include "map/hash/build.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct MapElement {

    typedef MapElement<KeyType,ValueType>   Type;

    KeyType key;
    ValueType value;
    MapHash<3>  hash;

    MapElement() : key(), value(), hash() {}
    MapElement(const Type&) { Error("Copier of MapElement Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for MapElement Disabled!");
      return *this;
    }
    ~MapElement() { clearData(); }

    void clearData() {
      release(key);
      release(value);
      release(hash);
    }
    void update() { key2hash(key,hash); }

  };

  template <typename ktype, typename vtype>
  void IsValid(const MapElement<ktype,vtype>& E) {
    return IsValid(E.key)&&IsValid(E.value)&&IsValid(E.hash);
  }
  template <typename ktype, typename vtype>
  void release(MapElement<ktype,vtype>& E) { E.clearData(); }

}

#endif

