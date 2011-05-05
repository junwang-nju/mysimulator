
#ifndef _Buffer_Distance_Pair_Copy_H_
#define _Buffer_Distance_Pair_Copy_H_

#include "buffer/distance/pair/interface.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(PairDistanceBuffer<T>& B, const PairDistanceBuffer<cT>& cB) {
    assert(IsValid(B)&&IsValid(cB));
    copy(static_cast<DistanceBufferBase<T>&>(B),
         static_cast<const DistanceBufferBase<T>&>(cB));
    copy(B.DSqMat,cB.DSqMat);
  }

  template <typename T>
  void ecopy(PairDistanceBuffer<T>& B, const PairDistanceBuffer<T>& cB) {
    assert(IsValid(B)&&IsValid(cB));
    assert(B.DSqMat.data.property[MatrixDimension]==
           cB.DSqMat.data.property[MatrixDimension]);
    copy(static_cast<DistanceBufferBase<T>&>(B),
         static_cast<const DistanceBufferBase<T>&>(cB));
    ecopy(B.DSqMat,cB.DSqMat);
  }

}

#endif

