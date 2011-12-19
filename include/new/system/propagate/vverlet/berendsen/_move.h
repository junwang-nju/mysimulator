
#ifndef _System_Propagate_VelocityVerlet_Berendsen_Move_Func_H_
#define _System_Propagate_VelocityVerlet_Berendsen_Move_Func_H_

#include "system/propagate/vverlet/const-e/_move.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveFuncBsVVerletGlobalMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int&) {
    _BfMoveFuncCEVVerletGlobalMass(X,V,G,dt,nhtim,0);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncBsVVerletArrayMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim,
      const unsigned int& n) {
    _BfMoveFuncCEVVerletArrayMass(X,V,G,dt,nhtim,n);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncBsVVerletGlobalMass(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const unsigned int&) {
    _AfMoveFuncCEVVerletGlobalMass(V,G,nhtim,0);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncBsVerletArrayMass(
      VT<T>& V, VT<T>& G, const Unique64Bit& nhtim, const unsigned int& n) {
    _AfMoveFuncCEVVerletArrayMass(V,G,nhtim,n);
  }

}

#endif

