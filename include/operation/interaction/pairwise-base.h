
#ifndef _Interaction_Pairwise_Base_H_
#define _Interaction_Pairwise_Base_H_

#include "data/basic/vector.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T, typename DistBuffer>
  void EFuncPairwiseBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
  }

}

#endif

