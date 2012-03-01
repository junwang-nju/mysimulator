
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Both_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Both_H_

#include "interaction/func/impl/dihedral/periodic/parameter/name.h"
#include "intrinsic-type/cos.h"
#include "intrinsic-type/sin.h"

namespace mysimulator {

  template <typename T>
  void BothDihedralPeriodic(const T& dih,const Unique64Bit* P,T& func,T& diff) {
    func=diff=0.;
    T theta;
    Unique64Bit* Q=const_cast<Unique64Bit*>(P);
    for(unsigned int i=0;i<P[DihPeriodicNumFuncs].value<unsigned int>();++i) {
      theta=dih+Q[DihPeriodicFuncPhase].value<T>();
      theta*=Q[DihPeriodicFuncFrequence].value<unsigned int>();
      func+=Q[DihPeriodicFuncStrength].value<T>()*(Cosine(theta)+1.);
      diff-=Q[DihPeriodicFuncStrengthFrequence].value<T>()*Sine(theta);
      Q+=DihPeriodicFuncNumberParameters;
    }
  }

}

#endif

