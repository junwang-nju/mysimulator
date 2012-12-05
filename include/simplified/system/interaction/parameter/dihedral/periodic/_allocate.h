
#ifndef _System_Interaction_Parameter_Dihedral_Periodic_Allocate_H_
#define _System_Interaction_Parameter_Dihedral_Periodic_Allocate_H_

#include "system/interaction/parameter/dihedral/periodic/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _allocate_param_dihedral_periodic(
      Array<Double>& _FParam,Array<Int>& _IParam,Array<InteractionParameter>&) {
    _FParam.allocate(DihedralPeriodicParameterName::Double::NumberParameter);
    _IParam.allocate(DihedralPeriodicParameterName::Int::NumberParameter);
  }

}

#endif

