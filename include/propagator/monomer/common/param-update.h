
#ifndef _Propagator_Monomer_Parameter_Common_Update_H_
#define _Propagator_Monomer_Parameter_Common_Update_H_

#include "propagator/monomer/common/param-name.h"
#include "vector/interface.h"
#include "unique-parameter/64bit/interface.h"

namespace mysimulator {

  template <typename T>
  void UpdateMonomerPropagatorCommon(Vector<UniqueParameter64Bit>& MP,
                                     const Vector<UniqueParameter64Bit>& SP) {
    assert(MP[MassData].value<T>()>1e-8);
    copy(MP[IvMassData],1./MP[MassData].value<T>());
  }

}

#endif

