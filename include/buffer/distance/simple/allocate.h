
#ifndef _Buffer_Distance_Simple_Allocate_H_
#define _Buffer_Distance_Simple_Allocate_H_

#include "buffer/distance/simple/interface.h"
#include "buffer/distance/simple/data-name.h"
#include "intrinsic-type/copy.h"
#include "vector/allocate.h"

namespace mysimulator {

  template <typename T>
  void allocate(SimpleDistanceBuffer<T>& B,
                const unsigned int dim, const unsigned int nunit) {
    allocate(B.DisplaceVector,dim);
    allocate(B.data,DBSimpleNumberData);
    copy(B.UnitNumber(),nunit);
  }

  template <typename T>
  void imprint(SimpleDistanceBuffer<T>& B,
               const SimpleDistanceBuffer<T>& cB) {
    assert(IsValid(cB));
    allocate(B,cB.Dimension(),cB.UnitNumber());
  }

}

#endif

