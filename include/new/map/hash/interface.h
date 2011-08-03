
#ifndef _Map_Hash_Interface_H_
#define _Map_Hash_Interface_H_

#include "intrinsic-type/constant.h"
#include "array/1d/content/interface.h"

namespace mysimulator {

  template <unsigned int NHashElement>
  struct HashTable {

    public:

      typedef HashTable<NHashElement>   Type;

      unsigned int elem[NHashElement];

      HashTable() { clearData(); }
      ~HashTable() { clearData(); }

      void clearData() {
        unsigned int* p=elem;
        unsigned int* e=p+NHashElement;
        for(;p!=e;) *(p++)=uZero;
      }
      bool isvalid() const { return true; }

      unsigned int& operator[](const unsigned int& I) {
        assert(I<NHashElement); return elem[I];
      }
      const unsigned int& operator[](const unsigned int& I) const {
        assert(I<NHashElement); return elem[I];
      }

      void create(const int&) { Error("Default Creation Disabled!"); }
      void create(const unsigned int&) { Error("Default Creation Disabled!"); }
      void create(const Array1DContent<char>&) {
        Error("Default Creation Disabled!");
      }
      void create(const Array1DContent<int>&) {
        Error("Default Creation Disabled!");
      }
      void create(const Array1DContent<unsigned int>&) {
        Error("Default Creation Disabled!");
      }

    private:

      HashTable(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <unsigned int NH>
  bool IsValid(const HashTable<NH>& H) { return H.isvalid(); }

  template <unsigned int NH>
  void release(HashTable<NH>& H) { H.clearData(); }

}

#include "map/hash/key2hash.h"

namespace mysimulator {

  template <>
  void HashTable<3>::create(const unsigned int& key) {
    _key2hash_3element(reinterpret_cast<const char*>(&key),
                       sizeof(unsigned int)/sizeof(char),elem);
  }

  template <>
  void HashTable<3>::create(const int& key) {
    _key2hash_3element(reinterpret_cast<const char*>(&key),
                       sizeof(int)/sizeof(char),elem);
  }

  template <>
  void HashTable<3>::create(const Array1DContent<char>& key) {
    _key2hash_3element(key.start,key.size,elem);
  }

  template <>
  void HashTable<3>::create(const Array1DContent<int>& key) {
    _key2hash_3element(reinterpret_cast<const char*>(key.start),
                       key.size*sizeof(int)/sizeof(char),elem);
  }

  template <>
  void HashTable<3>::create(const Array1DContent<unsigned int>& key) {
    _key2hash_3element(reinterpret_cast<const char*>(key.start),
                       key.size*sizeof(unsigned int)/sizeof(char),elem);
  }

}

#endif

