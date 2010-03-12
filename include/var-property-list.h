
#ifndef _Variable_Property_List_H_
#define _Variable_Property_List_H_

#include "property-list-base.h"
#include "var-vector.h" 

namespace std {

  template <typename T>
  class varPropertyList : public PropertyListBase<T,varVector> {

    public:

      typedef varPropertyList<T>    Type;

      typedef PropertyListBase<T,varVector>   ParentType;

      varPropertyList() : ParentType() {}

      varPropertyList(const VectorBase<unsigned int>& ShpSize) : ParentType() {
        allocate(ShpSize);
      }

      varPropertyList(const Type&) {
        myError("Cannot create from variable Property List");
      }

      virtual ~varPropertyList() {}

      Type& operator=(const Type& vPL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vPL));
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

      void allocate(const VectorBase<unsigned int>& ShapeSize) {
        unsigned int n=ShapeSize.size();
        unsigned int ne=0;
        for(unsigned int i=0;i<n;++i)   ne+=ShapeSize[i];
        static_cast<ParentType*>(this)->allocate(ne);
        this->StructureVec().allocate(n);
        ne=0;
        for(unsigned int i=0;i<n;ne+=ShapeSize[i],++i)
          this->operator[](i).refer(
              *static_cast<typename ParentType::ParentType*>(this),
              ne,ShapeSize[i]);
      }

  };

}

#endif
