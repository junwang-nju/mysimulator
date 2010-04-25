
#ifndef _Variable_Pair_Storage_H_
#define _Variable_Pair_Storage_H_

#include "pair-storage.h"

namespace std {

  template <typename T>
  class varPairStorage : public PairStorage<T,varMatrixTriangle,varVector> {

    public:

      typedef PairStorage<T,varMatrixTriangle,varVector>  Type;

  };

}

#endif

