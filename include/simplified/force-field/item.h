
#ifndef _Force_Field_Item_H_
#define _Force_Field_Item_H_

#include "force-field/parser.h"
#include <algorithm>


namespace mysimulator {

  class _ForceFieldItem {

    public:

      typedef _ForceFieldItem  Type;

    private:

      char* _key;
      char* _type;
      char* _value;

    public:

      _ForceFieldItem() : _key(nullptr), _type(nullptr), _value(nullptr) {}
      _ForceFieldItem(const Type& FI) : _ForceFieldItem() { operator=(FI); }
      _ForceFieldItem(Type&& FI) : _ForceFieldItem() { swap(FI); }
      ~_ForceFieldItem() { reset(); }


      operator bool() const {
        return _key!=nullptr && _type!=nullptr && _value!=nullptr;
      }
      const char* Key() const { return _key; }
      const char* ValueType() const { return _type; }
      const char* Value() const { return _value; }
      void reset() { __delete_array<char>(_key);    _key=nullptr;
                     __delete_array<char>(_type);   _type=nullptr;
                     __delete_array<char>(_value);  _value=nullptr; }

      Type& operator=(const Type& FI) {
        assert((bool)FI);
        reset();
        _key=new char[strlen(FI._key)+1];
        _type=new char[strlen(FI._type)+1];
        _value=new char[strlen(FI._type)+1];
        strcpy(_key,FI._key);
        strcpy(_type,FI._type);
        strcpy(_value,FI._value);
        return *this;
      }
      Type& operator=(const char* rec) {
        assert(IsForceFieldRecord(rec));
        reset();
        __parse_key_for_forcefield_record(_key,rec);
        __parse_type_for_forcefield_record(_type,rec);
        __parse_value_for_forcefield_record(_value,rec);
        return *this;
      }

      void swap(Type& FI) {
        std::swap(_key,FI._key);
        std::swap(_type,FI._type);
        std::swap(_value,FI._value);
      }

  };

}

namespace mysimulator {

  void swap(mysimulator::_ForceFieldItem& A, mysimulator::_ForceFieldItem& B) {
    A.swap(B);
  }

}

#endif

