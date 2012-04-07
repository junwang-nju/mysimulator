
#ifndef _Interaction_Func_Implement_Dihedral_Periodic_Parameter_Build_H_
#define _Interaction_Func_Implement_Dihedral_Periodic_Parameter_Build_H_

#include "unique/64bit/copy.h"
#include "interaction/func/impl/dihedral/periodic/parameter/name.h"

namespace mysimulator {

  void _SetSizeDihPeriodicNumParameter(Unique64Bit* prm) {
    prm[DihedralPeriodicNumParameters].value<unsigned int>()=
      DihedralPeriodicFuncParamShift+
      prm[DihedralPeriodicNumFuncs].value<unsigned int>()*
      DihedralPeriodicFuncNumberParameters;
  }

  template <typename T>
  void _BuildParameterDihedralPeriodic(Unique64Bit* prm) {
    unsigned int I=DihedralPeriodicFuncParamShift;
    for(unsigned int i=0;i<prm[DihedralPeriodicNumFuncs].value<unsigned int>();
        ++i) {
      copy(prm[I+DihedralPeriodicFuncStrengthFrequence],
           prm[I+DihedralPeriodicFuncStrength].value<T>()*
           prm[I+DihedralPeriodicFuncFrequence].value<unsigned int>());
      I+=DihedralPeriodicFuncNumberParameters;
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
    assert(prm.size>=DihedralPeriodicNumParameters);
    _SetSizeDihPeriodicNumParameter(prm.start);
    assert(prm.size>=prm[DihedralPeriodicNumParameters].value<unsigned int>());
    _BuildParameterDihedralPeriodic<T>(prm.start);
  }

}

#endif

