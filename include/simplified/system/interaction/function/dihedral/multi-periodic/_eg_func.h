
#ifndef _System_Interaction_Function_Dihedral_MultiPeriodic_EG_Func_H_
#define _System_Interaction_Function_Dihedral_MultiPeriodic_EG_Func_H_

#include "system/interaction/function/dihedral/multi-periodic/post-name.h"
#include "system/interaction/function/dihedral/periodic/_eg_func.h"

namespace mysimulator {

  void _egfunc_dihedral_multi_periodic(
      Array<Double> const& _post,const InteractionParameter& P,
      double *Func, double *Diff) {
    double F,D,SF=0,SD=0;
    for(unsigned int i=0;i<P(0);++i) {
      _egfunc_dihedral_periodic(_post,P,&F,&D);
      SF+=F;
      SD+=D;
    }
    *Func=SF;
    *Diff=SD;
  }

}

#endif

