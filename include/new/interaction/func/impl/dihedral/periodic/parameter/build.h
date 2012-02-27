
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Parameter_Build_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Parameter_Build_H_

#include "unique/64bit/copy.h"
#include "interaction/func/impl/dihedral/periodic/parameter/name.h"

namespace mysimulator {

  void _SetSizeDihPeriodicNumParameter(Unique64Bit* P) {
    prm[DihPeriodicNumParameters].u=
      DihPeriodicFuncParamShift+
      prm[DihPeriodicNumFuncs].u*DihPeriodicFuncNumberParameters;
  }

  template <typename T>
  void _BuildParameterDihedralPeriodic(Unique64Bit* prm) {
    unsigned int I=DihPeriodicFuncParamShift;
    for(unsigned int i=0;i<prm[DihPeriodicNumFuncs].u;++i) {
      copy(prm[I+DihPeriodicFuncStrengthFrequence],
           prm[I+DihPeriodicFuncStrength].value<T>()*
           prm[I+DihPeriodicFuncFrequence].u);
      I+=DihPeriodicFuncNumberParameters;
    }
  }

  template <typename T>
  void BuildParameterDihedralPeriodic(Unique64Bit* prm) {
    _SetSizeDihPeriodicNumParameter(prm);
    _BuildParameterDihedralPeriodic<T>(prm);
  }

}

#include "array/1d/content/interface.h"

namespace mysimulator {

  template <typename T>
  void BuildParameterDihedralPeriodic(Array1DContent<Unique64Bit>& prm) {
    assert(prm.size>DihPeriodicNumParameters);
    _SetSizeDihPeriodicNumParameter(prm.start);
    assert(prm.size>prm[DihPeriodicNumParameters].u);
    _BuildParameterDihedralPeriodic<T>(prm.start);
  }

}

#endif

