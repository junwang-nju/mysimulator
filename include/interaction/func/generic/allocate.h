
#ifndef _Interaction_Function_Generic_Allocate_H_
#define _Interaction_Function_Generic_Allocate_H_

#include "interaction/func/generic/interface.h"
#include "interaction/func/interface.h"

namespace mysimulator {

  template <template<typename> class DBuffer, typename GeomType,typename T>
  void allocate(InteractionFuncGeneric<DBuffer,GeomType,T>& G,
                const InteractionFunctionName itag) {
    release(G);
    G.tag=itag;
    switch(itag) {
      case Harmonic:
        G.EFunc=InteractionFunc<Harmonic,DBuffer,GeomType,T>::Energy;
        G.GFunc=InteractionFunc<Harmonic,DBuffer,GeomType,T>::Gradient;
        G.BFunc=InteractionFunc<Harmonic,DBuffer,GeomType,T>::Both;
        break;
      case LJ612:
        G.EFunc=InteractionFunc<LJ612,DBuffer,GeomType,T>::Energy;
        G.GFunc=InteractionFunc<LJ612,DBuffer,GeomType,T>::Gradient;
        G.BFunc=InteractionFunc<LJ612,DBuffer,GeomType,T>::Both;
        break;
      case LJ612Cut:
        G.EFunc=InteractionFunc<LJ612Cut,DBuffer,GeomType,T>::Energy;
        G.GFunc=InteractionFunc<LJ612Cut,DBuffer,GeomType,T>::Gradient;
        G.BFunc=InteractionFunc<LJ612Cut,DBuffer,GeomType,T>::Both;
        break;
      case LJ1012:
        G.EFunc=InteractionFunc<LJ1012,DBuffer,GeomType,T>::Energy;
        G.GFunc=InteractionFunc<LJ1012,DBuffer,GeomType,T>::Gradient;
        G.BFunc=InteractionFunc<LJ1012,DBuffer,GeomType,T>::Both;
        break;
      case LJ1012Cut:
        G.EFunc=InteractionFunc<LJ1012Cut,DBuffer,GeomType,T>::Energy;
        G.GFunc=InteractionFunc<LJ1012Cut,DBuffer,GeomType,T>::Gradient;
        G.BFunc=InteractionFunc<LJ1012Cut,DBuffer,GeomType,T>::Both;
        break;
      case Core12:
        G.EFunc=InteractionFunc<Core12,DBuffer,GeomType,T>::Energy;
        G.GFunc=InteractionFunc<Core12,DBuffer,GeomType,T>::Gradient;
        G.BFunc=InteractionFunc<Core12,DBuffer,GeomType,T>::Both;
      case CoreLJ612:
        G.EFunc=InteractionFunc<CoreLJ612,DBuffer,GeomType,T>::Energy;
        G.GFunc=InteractionFunc<CoreLJ612,DBuffer,GeomType,T>::Gradient;
        G.BFunc=InteractionFunc<CoreLJ612,DBuffer,GeomType,T>::Both;
        break;
      case Coulomb:
        G.EFunc=InteractionFunc<Coulomb,DBuffer,GeomType,T>::Energy;
        G.GFunc=InteractionFunc<Coulomb,DBuffer,GeomType,T>::Gradient;
        G.BFunc=InteractionFunc<Coulomb,DBuffer,GeomType,T>::Both;
        break;
      default:
        Error("Unknown Interaction Function Type!");
    };
  }

  template <template<typename> class DBuffer, typename GeomType,typename T>
  void imprint(InteractionFuncGeneric<DBuffer,GeomType,T>& G,
               const InteractionFuncGeneric<DBuffer,GeomType,T>& cG) {
    allocate(G,cG.tag);
  }

}

#endif

