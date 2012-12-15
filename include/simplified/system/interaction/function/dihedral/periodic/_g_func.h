
#ifndef _System_Interaction_Function_Dihedral_Periodic_G_Func_H_
#define _System_Interaction_Function_Dihedral_Periodic_G_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/dihedral/periodic/post-name.h"
#include "basic/util/sine.h"

namespace mysimulator {

  void _gfunc_dihedral_periodic(
      Array<Double> const& _post, const InteractionParameter& P, double* Diff) {
    double Dih=_post[DihedralPeriodicPostName::Angle];
    double dDih=Dih-P[DihedralPeriodicParameterName::Double::Phase];
    *Diff=P[DihedralPeriodicParameterName::Double::SFProduct]*
          __sin(P(DihedralPeriodicParameterName::Int::Frequency)*dDih);
  }

}

#endif


