
#ifndef _ID_List_Operation_H_
#define _ID_List_Operation_H_

#include "interaction-list.h"
#include "interaction.h"

namespace std {

  template <typename DistEvalObj, typename GeomType, uint bMode>
  void SetInteraction(InteractionList<DistEvalObj,GeomType,bMode>& IL,
                      const uint& iTag) {
    IL.interactionTag=iTag;
    switch(iTag) {
      case ParticleParticle_Harmonic:
        IL.efunc=E_ParPar_Harmonic;
        IL.gfunc=G_ParPar_Harmonic;
        IL.bfunc=EG_ParPar_Harmonic;
        break;
      case ParticleParticle_LJ1012:
        IL.efunc=E_ParPar_LJ1012;
        IL.gfunc=G_ParPar_LJ1012;
        IL.bfunc=EG_ParPar_LJ1012;
        break;
      case ParticleParticle_LJ612:
        IL.efunc=E_ParPar_LJ612;
        IL.gfunc=G_ParPar_LJ612;
        IL.bfunc=EG_ParPar_LJ612;
        break;
      case ParticleParticle_LJ612Cut:
        IL.efunc=E_ParPar_LJ612Cut;
        IL.gfunc=G_ParPar_LJ612Cut;
        IL.bfunc=EG_ParPar_LJ612Cut;
        break;
      default:
        myError("Unknown Interaction Type!");
    };
  }
}

#endif

