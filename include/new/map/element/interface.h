
#ifndef _Map_Element_Interface_H_
#define _Map_Element_Interface_H_

#include "map/hash/interface.h"
#include "object/interface.h"

namespace mysimulator {

  template <typename KeyType, typename ValueType>
  struct MapElement {

    public:

      typedef MapElement<KeyType,ValueType>   Type;

      Object<KeyType> key;
      Object<ValueType> value;
      HashTable<3> hash;

      MapElement() : key(), value(), hash() {}
      ~MapElement() { clearData(); }

      void clearData() { release(key); release(value); release(hash); }
      bool isvalid() const { return IsValid(key)&&IsValid(value); }

      void update() { hash.create(key()); }

    private:

      MapElement(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename KT, typename VT>
  bool IsValid(const MapElement<KT,VT>& E) { return E.isvalid(); }

  template <typename KT, typename VT>
  void release(MapElement<KT,VT>& E) { E.clearData(); }

}

#endif

