
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Move_Func_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Move_Func_H_

#include "system/propagate/vverlet/const-e/_move.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncBsVVerletGMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int&) {
    _BfMoveFuncCEVVerletGMass<T,VT>(X,V,G,dt,nhtim,0);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncBsVVerletAMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int& n) {
    _BfMoveFuncCEVVerletAMass<T,VT>(X,V,G,dt,nhtim,n);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncBsVVerletGMass(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const unsigned int&) {
    _AfMoveFuncCEVVerletGMass<T,VT>(V,G,nhtim,0);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncBsVerletAMass(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const unsigned int& n) {
    _AfMoveFuncCEVVerletAMass<T,VT>(V,G,nhtim,n);
  }

}

#endif

