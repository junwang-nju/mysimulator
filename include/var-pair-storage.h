
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

      varPairStorage() : ParentType() { this->GStatusVec().allocate(1); }

  };

}

#endif

