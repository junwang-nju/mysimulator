
#ifndef _System_Interaction_Function_Dihedral_MultiPeriod_EG_Func_H_
#define _System_Interaction_Function_Dihedral_MultiPeriod_EG_Func_H_

#include "system/interaction/function/dihedral/multi-periodic/post-name.h"
#include "system/interaction/function/dihedral/periodic/_eg_func.h"

namespace mysimulator {

  void _egfunc_dihedral_multi_periodic(
      Array<Double> const& _post,const InteractionParameter& P,
      double *Func, double *Diff) {
    double SF=0,SD=0;
    double Dih=_post[DihedralPeriodicPostName::Angle];
    double dDih=Dih-P[DihedralPeriodicParameterName::Double::Phase];
    double FD;
    InteractionParameter& RP;
    for(unsigned int i=0;i<P(0);++i) {
      RP=P.child(i);
      FD=RP(DihedralPeriodicParameterName::Int::Frequency)*dDih;
      SF+=RP[DihedralPeriodicParameterName::Double::Strength]*(1.-__cos(FD));
      SD+=RP[DihedralPeriodicParameterName::Double::SFProduct]*__sin(FD);
    }
    *Func=SF;
    *Diff=SD;
  }

}

#endif

