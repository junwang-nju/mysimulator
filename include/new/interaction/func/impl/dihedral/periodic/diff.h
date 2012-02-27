
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Diff_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Diff_H_

#include "interaction/func/impl/dihedral/periodic/parameter/name.h"
#include "intrinsic-type/sin.h"

namespace mysimulator {

  template <typename T>
  void DiffDihedralPeriodic(const T& dih, const Unique64Bit* P, T& diff) {
    diff=0.;
    Unique64Bit *Q=const_cast<Unique64Bit*>(P)+DihPeriodicFuncParamShift;
    T theta;
    for(unsigned int i=0;i<P[DihPeriodicNumFuncs].u;++i) {
      theta=dih+Q[DihPeriodicFuncPhase].value<T>();
      diff-=Q[DihPeriodicFuncStrengthFrequence].value<T>()*
            Sine(Q[DihPeriodicFuncFrequence].u*theta);
      Q+=DihPeriodicFuncNumberParameters;
    }
  }

}

#endif

