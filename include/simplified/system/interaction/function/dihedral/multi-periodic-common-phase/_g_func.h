
#ifndef _System_Interaction_Function_Dihedral_MultiPeriodic_CmPhase_G_Func_H_
#define _System_Interaction_Function_Dihedral_MultiPeriodic_CmPhase_G_Func_H_

#include "system/interaction/function/dihedral/multi-periodic-common-phase/post-name.h"
#include "system/interaction/function/dihedral/periodic/_g_func.h"

namespace mysimulator {

  void _gfunc_dihedral_multi_periodic_common_phase(
      Array<Double> const& _post,const InteractionParameter& P,double *Diff) {
    double SF=0;
    double dDih=_post[DihedralMultiPeriodicCommonPhasePostName::Angle]-P[0];
    for(unsigned int i=0;i<P(0);++i) {
      InteractionParameter const& RP=P.child(i);
      SF+=RP[DihedralPeriodicParameterName::Double::SFProduct]*
          __sin(RP(DihedralPeriodicParameterName::Int::Frequency)*dDih);
    }
    *Diff=SF;
  }

}

#endif

