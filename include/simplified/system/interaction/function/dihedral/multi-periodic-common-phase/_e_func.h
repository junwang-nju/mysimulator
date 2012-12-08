
#ifndef _System_Interaction_Function_Dihedral_MultiPeriodic_CmPhase_E_Func_H_
#define _System_Interaction_Function_Dihedral_MultiPeriodic_CmPhase_E_Func_H_

#include "system/interaction/function/dihedral/multi-periodic-common-phase/post-name.h"
#include "system/interaction/function/dihedral/periodic/_e_func.h"

namespace mysimulator {

  void _efunc_dihedral_multi_periodic_common_phase(
      Array<Double> const& _post,const InteractionParameter& P,double* Func) {
    double SF=0;
    double dDih=_post[DihedralMultiPeriodicCommonPhasePostName::Angle]-P[0];
    for(unsigned int i=0;i<P(0);++i) {
      InteractionParameter const& RP=P.child(i);
      SF+=RP[DihedralPeriodicParameterName::Double::Strength]*
          (1.-__cos(RP(DihedralPeriodicParameterName::Int::Frequency)*dDih));
    }
    *Func=SF;
  }

}

#endif

