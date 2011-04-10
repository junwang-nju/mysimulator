
#ifndef _Map_Element_Interface_H_
#define _Map_Element_Interface_H_

#include "map/hash/interface.h"

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

  };

  template <typename ktype, typename vtype>
  void release(MapElement<ktype,vtype>& E) { E.clearData(); }

}

#endif

