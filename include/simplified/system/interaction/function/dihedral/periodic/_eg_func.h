
#ifndef _System_Interaction_Function_Dihedral_Periodic_EG_Func_H_
#define _System_Interaction_Function_Dihedral_Periodic_EG_Func_H_

#include "system/interaction/parameter/interface.h"
#include "system/interaction/function/dihedral/periodic/post-name.h"
#include "basic/util/cosine.h"
#include "basic/util/sine.h"

namespace mysimulator {

  void _egfunc_dihedral_periodic(
      Array<Double> const& _post, const InteractionParameter& P,
      double* Func, double* Diff) {
    double Dih=_post[DihedralPeriodicPostName::Angle];
    double dDih=Dih-P[DihedralPeriodicParameterName::Double::Phase];
    *Func=P[DihedralPeriodicParameterName::Double::Strength]*
          (1.-__cos(P(DihedralPeriodicParameterName::Int::Frequency)*dDih));
    *Diff=P[DihedralPeriodicParameterName::Double::SFProduct]*
          __sin(P(DihedralPeriodicParameterName::Int::Frequency)*dDih);
  }

}

#endif

