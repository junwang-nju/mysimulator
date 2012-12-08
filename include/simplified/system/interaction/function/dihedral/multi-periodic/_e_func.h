
#ifndef _System_Interaction_Function_Dihedral_MultiPeriodic_E_Func_H_
#define _System_Interaction_Function_Dihedral_MultiPeriodic_E_Func_H_

#include "system/interaction/function/dihedral/multi-periodic/post-name.h"
#include "system/interaction/function/dihedral/periodic/_e_func.h"

namespace mysimulator {

  void _efunc_dihedral_multi_periodic(
      Array<Double> const& _post,const InteractionParameter& P,double* Func) {
    double SF=0;
    double Dih=_post[DihedralPeriodicPostName::Angle];
    double dDih=Dih-P[DihedralPeriodicParameterName::Double::Phase];
    InteractionParameter& RP;
    for(unsigned int i=0;i<P(0);++i) {
      RP=P.child(i)l
      SF+=RP[DihedralPeriodicParameterName::Double::Strength]*
          (1.-__cos(RP(DihedralPeriodicParameterName::Int::Frequency)*dDih));
    }
    *Func=SF;
  }

}

#endif

