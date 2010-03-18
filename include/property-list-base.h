
#ifndef _Property_List_Base_H_
#define _Property_List_Base_H_

#include "ref-vector.h"

namespace std {

  template <typename T, template <typename> class VecType>
  class PropertyListBase : public VecType<T> {

    public:

      typedef PropertyListBase<T,VecType>   Type;

      typedef VecType<T>    ParentType;

      typedef refVector<T>  PropertyType;

    protected:

      VecType<PropertyType> Struct;

    public:

      PropertyListBase() : ParentType() { assert(VecType<T>::IsVector); }

      PropertyListBase(const Type&) {
        myError("Cannot create from Property List Base Basic");
      }

      virtual ~PropertyListBase() { clear(); }

      void clear() {
        static_cast<ParentType*>(this)->clear();
        for(unsigned int i=0;i<Struct.size();++i)   Struct[i].clear();
        Struct.clear();
      }

      Type& operator=(const Type& PLB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(PLB));
        return *this;
      }

      Type& operator=(const VectorBase<T>& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }

      Type& operator=(const T& Value) {
        static_cast<ParentType*>(this)->operator=(Value);
        return *this;
      }

      const unsigned int size() const { return Struct.size(); }

      const unsigned int dataSize() const {
        return static_cast<const ParentType*>(this)->size();
      }

      const unsigned int numberUnits() const { return size(); }

      const VecType<PropertyType>& Structure() const { return Struct; }

      VecType<PropertyType>& Structure() { return Struct; }

      const PropertyType& operator[](const unsigned int I) const {
        return Struct[I];
      }

      PropertyType& operator[](const unsigned int I) { return Struct[I]; }

      const PropertyType* beginUnit() const { return Struct.begin(); }

      const PropertyType* endUnit() const { return Struct.end(); }

  };

}

#endif

