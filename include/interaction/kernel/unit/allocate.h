
#ifndef _Interaction_Kernel_Unit_Allocate_H_
#define _Interaction_Kernel_Unit_Allocate_H_

#include "interaction/kernel/unit/interface.h"

namespace mysimulator {

  template <template<typename> class DBuffer, typename GeomType,typename T>
  void allocate(InteractionKernelUnit<DBuffer,GeomType,T>& KU,
                const InteractionFunctionName itag) {
    release(KU);
    KU.tag=itag;
    switch(itag) {
      case Harmonic:
        KU.EFunc=InteractionFunc<Harmonic,DBuffer,GeomType,T>::Energy;
        KU.GFunc=InteractionFunc<Harmonic,DBuffer,GeomType,T>::Gradient;
        KU.BFunc=InteractionFunc<Harmonic,DBuffer,GeomType,T>::Both;
        break;
      case LJ612:
        KU.EFunc=InteractionFunc<LJ612,DBuffer,GeomType,T>::Energy;
        KU.GFunc=InteractionFunc<LJ612,DBuffer,GeomType,T>::Gradient;
        KU.BFunc=InteractionFunc<LJ612,DBuffer,GeomType,T>::Both;
        break;
      case LJ612Cut:
        KU.EFunc=InteractionFunc<LJ612Cut,DBuffer,GeomType,T>::Energy;
        KU.GFunc=InteractionFunc<LJ612Cut,DBuffer,GeomType,T>::Gradient;
        KU.BFunc=InteractionFunc<LJ612Cut,DBuffer,GeomType,T>::Both;
        break;
      case LJ1012:
        KU.EFunc=InteractionFunc<LJ1012,DBuffer,GeomType,T>::Energy;
        KU.GFunc=InteractionFunc<LJ1012,DBuffer,GeomType,T>::Gradient;
        KU.BFunc=InteractionFunc<LJ1012,DBuffer,GeomType,T>::Both;
        break;
      case LJ1012Cut:
        KU.EFunc=InteractionFunc<LJ1012Cut,DBuffer,GeomType,T>::Energy;
        KU.GFunc=InteractionFunc<LJ1012Cut,DBuffer,GeomType,T>::Gradient;
        KU.BFunc=InteractionFunc<LJ1012Cut,DBuffer,GeomType,T>::Both;
        break;
      case Core12:
        KU.EFunc=InteractionFunc<Core12,DBuffer,GeomType,T>::Energy;
        KU.GFunc=InteractionFunc<Core12,DBuffer,GeomType,T>::Gradient;
        KU.BFunc=InteractionFunc<Core12,DBuffer,GeomType,T>::Both;
      case CoreLJ612:
        KU.EFunc=InteractionFunc<CoreLJ612,DBuffer,GeomType,T>::Energy;
        KU.GFunc=InteractionFunc<CoreLJ612,DBuffer,GeomType,T>::Gradient;
        KU.BFunc=InteractionFunc<CoreLJ612,DBuffer,GeomType,T>::Both;
        break;
      case Coulomb:
        KU.EFunc=InteractionFunc<Coulomb,DBuffer,GeomType,T>::Energy;
        KU.GFunc=InteractionFunc<Coulomb,DBuffer,GeomType,T>::Gradient;
        KU.BFunc=InteractionFunc<Coulomb,DBuffer,GeomType,T>::Both;
        break;
      default:
        Error("Unknown Interaction Function Type!");
    };
  }

  template <template<typename> class DBuffer, typename GeomType,typename T>
  void imprint(InteractionKernelUnit<DBuffer,GeomType,T>& KU,
               const InteractionKernelUnit<DBuffer,GeomType,T>& cKU) {
    allocate(KU,cKU.tag);
  }

}

#endif

