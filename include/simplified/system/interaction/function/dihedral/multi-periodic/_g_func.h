
#ifndef _System_Interaction_Function_Dihedral_MultiPeriodic_G_Func_H_
#define _System_Interaction_Function_Dihedral_MultiPeriodic_G_Func_H_

#include "system/interaction/function/dihedral/multi-periodic/post-name.h"
#include "system/interaction/function/dihedral/periodic/_g_func.h"

namespace mysimulator {

  void _gfunc_dihedral_multi_periodic(
      Array<Double> const& _post,const InteractionParameter& P,double *Diff) {
    double D,SD=0;
    for(unsigned int i=0;i<P(0);++i) {
      _gfunc_dihedral_periodic(_post,P,&D);
      SD+=D;
    }
    *Diff=SD;
  }

}

#endif

