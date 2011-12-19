
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Move_Func_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Move_Func_H_

#include "system/propagate/vverlet/const-e/_move.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncBsVVerletGMass(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const T& dt,
      const Unique64Bit& nhtim) {
    _BfMoveFuncCEVVerletGMass<T,VT>(gC,dt,nhtim);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncBsVVerletAMass(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const T& dt,
      const Unique64Bit& nhtim) {
    _BfMoveFuncCEVVerletAMass<T,VT>(gC,dt,nhtim);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncBsVVerletGMass(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const Unique64Bit& nhtim){
    _AfMoveFuncCEVVerletGMass<T,VT>(gC,nhtim);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncBsVVerletAMass(
      Array1DContent<SysContentWithEGV<T,VT> >& gC, const Unique64Bit& nhtim){
    _AfMoveFuncCEVVerletAMass<T,VT>(gC,nhtim);
  }

}

#endif

