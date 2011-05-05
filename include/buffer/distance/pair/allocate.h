
#ifndef _Buffer_Distance_Pair_Allocate_H_
#define _Buffer_Distance_Pair_Allocate_H_

#include "buffer/distance/pair/interface.h"
#include "matrix/storage/allocate.h"
#include "buffer/distance/pair/data-name.h"

namespace mysimulator {

  template <typename T>
  void allocate(PairDistanceBuffer<T>& B,
                const unsigned int dim, const unsigned int nunit) {
    allocate(B.DisplaceVector,dim);
    allocate(B.data,DBPairNumberData);
    copy(B.UnitNumber(),nunit);
    allocate(B.DSqMat,nunit);
  }

}

#endif

