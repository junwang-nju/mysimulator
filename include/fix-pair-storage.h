
#ifndef _Fixed_Pair_Storage_H_
#define _Fixed_Pair_Storage_H_

#include "pair-storage-base.h"
#include "fix-matrix-triangle.h"
#include "ref-matrix-triangle.h"

namespace std {

  template <typename T, unsigned int NUnits>
  class fixPairStorage :public PairStorageBase<T,refMatrixTriangle,refVector> {

    public:

      typedef fixPairStorage<T>   Type;

      typedef PairStorageBase<T,refMatrixTriangle,refVector>  ParentType;

    protected:

      fixVector<unsigned int,1> inGStatus;

      fixMatrixTriangle<T,NUnits,false> inData;
  };

}

#endif

