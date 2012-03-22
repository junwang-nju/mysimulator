
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Func_Dihedral_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Func_Dihedral_H_

#include "interaction/func/impl/dihedral/periodic/parameter/name.h"
#include "intrinsic-type/cos.h"

namespace mysimulator {

  template <typename T>
  void FuncDihedralPeriodicDih(const T* dih, const Unique64Bit* P, T* func) {
    T fc=0;
    Unique64Bit *Q=const_cast<Unique64Bit*>(P)+DihPeriodicFuncParamShift;
    T theta;
    for(unsigned int i=0;i<P[DihPeriodicNumFuncs].value<unsigned int>();++i) {
      theta=(*dih)+Q[DihPeriodicFuncPhase].value<T>();
      fc+=
        Q[DihPeriodicFuncStrength].value<T>()*
        (Cosine(Q[DihPeriodicFuncFrequence].value<unsigned int>()*theta)+1.);
      Q+=DihPeriodicFuncNumberParameters;
    }
    *func=fc;
  }

}

#endif

