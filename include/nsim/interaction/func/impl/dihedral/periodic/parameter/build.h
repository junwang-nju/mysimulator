
#ifndef _Interaction_Func_Impl_Dihedral_Periodic_Parameter_Build_H_
#define _Interaction_Func_Impl_Dihedral_Periodic_Parameter_Build_H_

#include "unique/64bit/interface.h"
#include "interaction/func/impl/dihedral/periodic/parameter/name.h"

namespace mysimulator {

  void _DihedralPeriodicSetSize(Array1D<Unique64Bit>& P) {
    P[DihedralPeriodicNumParameters].u=
      DihedralPeriodicFuncParamShift+
      P[DihedralPeriodicNumFuncs].u*DihedralPeriodicFuncNumberParameters;
  }

  template <typename T>
  void _DihedralPeriodicBuild(Array1D<Unique64Bit>& P) {
    unsigned int Sf=DihedralPeriodicFuncParamShift;
    for(unsigned int i=0;i<P[DihedralPeriodicNumFuncs].u;++i) {
      P[Sf+DihedralPeriodicFuncStrengthFrequency].value<T>()=
        P[Sf+DihedralPeriodicFuncStrength].value<T>()*
        P[Sf+DihedralPeriodicFuncFrequency].u;
      Sf+=DihedralPeriodicFuncNumberParameters;
    }
  }

  template <typename T>
  void BuildParameterDihedralPeriodic(Array1D<Unique64Bit>& P) {
    _DihedralPeriodicSetSize(P);
    _DihedralPeriodicBuild(P);
  }

}

#endif

