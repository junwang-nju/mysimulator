
#ifndef _System_Interaction_Parameter_Dihedral_Periodic_Build_H_
#define _System_Interaction_Parameter_Dihedral_Periodic_Build_H_

#include "system/interaction/parameter/dihedral/periodic/name.h"
#include "array/interface.h"

namespace mysimulator {

  class InteractionParameter;

  void _build_dihedral_periodic(
      Array<Double>& _FParam,Array<Int>& _IParam,Array<InteractionParameter>&) {
    assert((bool)_FParam);
    assert((bool)_IParam);
    assert(_FParam.size()>=DihedralPeriodicParameterName::Double::NumberParameter);
    assert(_IParam.size()>=DihedralPeriodicParameterName::Int::NumberParameter);
    _FParam[DihedralPeriodicParameterName::Double::SFProduct] =
      _FParam[DihedralPeriodicParameterName::Double::Strength] *
      _IParam[DihedralPeriodicParameterName::Int::Frequency];
  }

}

#endif

