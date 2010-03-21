
#ifndef _Reference_Pair_Storage_H_
#define _Reference_Pair_Storage_H_

#include "pair-storage-base.h"
#include "ref-matrix-triangle.h"

namespace std {

  template <typename T>
  class refPairStorage :public PairStorageBase<T,refMatrixTriangle,refVector> {

    public:

      typedef refPairStorage<T>   Type;

      typedef PairStorageBase<T,refMatrixTriangle,refVector>  ParentType;

      refPairStorage() : ParentType() {}

      refPairStorage(const Type&) {
        myError("Cannot create from fixed Pair Storage");
      }

      Type& operator=(const Type& rPS) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(rPS));
        return *this;
      }

      template <template <typename> class TMat,
                template <typename> class VecType>
      void refer(const PairStorageBase<T,TMat,VecType>& PS) {
        this->GStatusVec().refer(PS.GStatusVec());
        this->DataMat().refer(PS.DataMat());
      }

  };

}

#endif

