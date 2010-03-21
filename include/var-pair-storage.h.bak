
#ifndef _Variable_Pair_Storage_H_
#define _Variable_Pair_Storage_H_

#include "pair-storage-base.h"
#include "var-vector.h"
#include "var-matrix-triangle.h"

namespace std {

  template <typename T>
  class varPairStorage :public PairStorageBase<T,varMatrixTriangle,varVector> {

    public:

      typedef varPairStorage<T>   Type;

      typedef PairStorageBase<T,varMatrixTriangle,varVector>  ParentType;

      varPairStorage() : ParentType() {}

      varPairStorage(const unsigned int N) : ParentType() { allocate(N); }

      varPairStorage(const Type&) {
        myError("Cannot create from variable Pair Storage");
      }

      ~varPairStorage() {}

      Type& operator=(const Type& vPS) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(vPS));
        return *this;
      }

      void allocate(const unsigned int N) {
        this->DataMat().allocate(N,COrder,NoTranspose,UpperPart,true,false);
        this->GStatusVec().allocate(1);
        this->GStatusVec()=1U;
      }

  };

}

#endif

