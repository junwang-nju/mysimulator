
#ifndef _Property_H_
#define _Property_H_

#include "var-vector.h"

namespace std {

  template <template <typename> class VecType=varVector,
            typename DataType=double>
  class Property : public VecType<DataType> {
    public:
      typedef Property<VecType,DataType>  Type;
      typedef VecType<DataType>           ParentType;
      Property() : ParentType() { assert(ParentType::IsVector); }
      Property(const Type& C) {
        myError("copier for Coordinate is prohibited!");
      }
      Type& operator=(const Type& C) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(C));
        return *this;
      }
  };

}

#endif

