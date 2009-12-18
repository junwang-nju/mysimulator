
#ifndef _ID_List_Operation_H_
#define _ID_List_Operation_H_

#include "id-list.h"
#include "interaction.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void SetInteraction(IDList<DistEvalObj,GeomType>& IDL, const uint& iTag) {
    IDL.interactionTag=iTag;
    switch(iTag) {
      case ParticleParticle_Harmonic:
        IDL.efunc=E_ParPar_Harmonic;
        IDL.gfunc=G_ParPar_Harmonic;
        IDL.bfunc=EG_ParPar_Harmonic;
        break;
      case ParticleParticle_LJ1012:
        IDL.efunc=E_ParPar_LJ1012;
        IDL.gfunc=G_ParPar_LJ1012;
        IDL.bfunc=EG_ParPar_LJ1012;
        break;
      case ParticleParticle_LJ612:
        IDL.efunc=E_ParPar_LJ612;
        IDL.gfunc=G_ParPar_LJ612;
        IDL.bfunc=EG_ParPar_LJ612;
        break;
      case ParticleParticle_LJ612Cut:
        IDL.efunc=E_ParPar_LJ612Cut;
        IDL.gfunc=G_ParPar_LJ612Cut;
        IDL.bfunc=EG_ParPar_LJ612Cut;
        break;
      default:
        myError("Unknown Interaction Type!");
    };
  }
}

#endif

