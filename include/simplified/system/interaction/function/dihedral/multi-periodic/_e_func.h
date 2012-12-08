
#ifndef _System_Interaction_Function_Dihedral_MultiPeriodic_E_Func_H_
#define _System_Interaction_Function_Dihedral_MultiPeriodic_E_Func_H_

#include "system/interaction/function/dihedral/multi-periodic/post-name.h"
#include "system/interaction/function/dihedral/periodic/_e_func.h"

namespace mysimulator {

  void _efunc_dihedral_multi_periodic(
      Array<Double> const& _post,const InteractionParameter& P,double* Func) {
    double F,SF=0;
    for(unsigned int i=0;i<P(0);++i) {
      _efunc_dihedral_periodic(_post,P,&F);
      SF+=F;
    }
    *Func=SF;
  }

}

#endif

