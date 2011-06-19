
#ifndef _Interaction_Kernel_Allocate_H_
#define _Interaction_Kernel_Allocate_H_

#include "interaction/kernel/interface.h"

namespace mysimulator {

  template <InteractionFunctionName ItType, template<typename> class DBuffer,
            typename GeomType, typename T>
  void allocate(InteractionKernel<ItType,DBuffer,GeomType,T>& K,
                const unsigned int nunit, const unsigned int dim, ...) {
    switch(ItType) {
      case Harmonic:
      case LJ612:
      case LJ612Cut:
      case LJ1012:
      case LJ1012Cut:
      case Core12:
      case CoreLJ612:
      case Coulomb:
        release(K.tmvec);   break;
      default:
        Error("Unknown Interaction Function Name!");
    };
    allocate(K.DB,dim,nunit);
    allocate(K.Geo,dim);
  }

  template <InteractionFunctionName ItType, template<typename> class DBuffer,
            typename GeomType, typename T>
  void imprint(InteractionKernel<ItType,DBuffer,GeomType,T>& K,
               const InteractionKernel<ItType,DBuffer,GeomType,T>& cK) {
    allocate(K,cK.NumUnit(),cK.Dimension());
  }

}

#endif

