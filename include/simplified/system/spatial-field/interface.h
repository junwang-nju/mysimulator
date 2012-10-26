
#ifndef _System_SpactialField_Interface_H_
#define _System_SpactialField_Interface_H_

#include "vec-array/interface.h"
#include "system/kind/coordinate-size.h"

namespace mysimulator {

  template <typename T>
  class SpatialField : public VectorArray<T> {

    public:

      static_assert(!__intrinsic_flag<T>::FG,
                    "For intrinsic types, please use Intrinsic<T>!\n");

      typedef SpatialField<T> Type;
      typedef VectorArray<T>  ParentType;
      typedef unsigned int size_type;

      SpatialField() : ParentType() {}
      SpatialField(size_type n,size_type dim) : ParentType(n,dim) {}
      SpatialField(const Type& F) : ParentType((ParentType const&)F) {}
      SpatialField(Type&& F) : ParentType((ParentType&&)F) {}
      SpatialField(const Array<SystemKindName>& K,unsigned int dim)
          : SpatialField() { allocate(K,dim); }
      ~SpatialField() { ParentType::reset(); }

      void allocate(Array<SystemKindName> const& K, unsigned int dim) {
        assert((bool)K);
        ParentType::reset();
        Array<UInt> SZ(K.size());
        for(size_type i=0;i<K.size();++i) SZ[i]=CoordinateSize(K[i],dim);
        ParentType::allocate(SZ);
        SZ.reset();
      }

  };

}

#endif

