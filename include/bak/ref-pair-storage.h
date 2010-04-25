
#ifndef _Reference_Pair_Storage_H_
#define _Reference_Pair_Storage_H_

#include "pair-storage.h"

namespace std {

  template <typename T>
  class refPairStorage : public PairStorage<T,refMatrixTriangle,refVector> {

    public:

      typedef PairStorage<T,refMatrixTriangle,refVector>  Type;

  };

}

#endif

