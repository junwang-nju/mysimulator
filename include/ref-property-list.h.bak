
#ifndef _Reference_Property_List_H_
#define _Reference_Property_List_H_

#include "property-list-base.h"

namespace std {

  template <typename T>
  class refPropertyList : public PropertyListBase<T,refVector> {

    public:

      typedef refPropertyList<T>  Type;

      typedef PropertyListBase<T,refVector>   ParentType;

      refPropertyList() : ParentType() {}

      refPropertyList(const Type&) {
        myError("Cannot create from reference Property List");
      }

      ~refPropertyList() {}

      Type& operator=(const Type& rPL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rPL));
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

      template <template <typename> class VecType>
      void refer(const PropertyListBase<T,VecType>& PL) {
        static_cast<ParentType*>(this)->refer(PL);
        this->Structure().refer(PL.Structure());
      }

  };

}

#endif
