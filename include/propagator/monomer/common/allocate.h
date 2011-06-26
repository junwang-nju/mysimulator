
#ifndef _Propagator_Monomer_Common_Allocate_H_
#define _Propagator_Monomer_Common_Allocate_H_

#include "propagator/monomer/common/interface.h"

namespace mysimulator {

  template <typename T>
  void allocate(MonomerPropagatorCommon<T>& P,const unsigned int dim) {
    release(P);
    allocate(P.XVector,dim);
    allocate(P.VVector,dim);
    allocate(P.GVector,dim);
    allocate(P.MskVector,dim);
  }

  template <typename T>
  void imprint(MonomerPropagatorCommon<T>& P,
               const MonomerPropagatorCommon<T>& cP) {
    assert(IsValid(cP));
    allocate(P,cP.XVector.size);
  }

}

#endif

