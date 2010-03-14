
#ifndef _Interaction_Method_Operation_H_
#define _Interaction_Method_Operation_H_

#include "interaction-method.h"
#include "interaction-particle-particle-harmonic.h"
#include "interaction-particle-particle-lj612.h"
#include "interaction-particle-particle-lj612cut.h"
#include "interaction-particle-particle-coulomb.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void SetInteractionMethod(InteractionMethod<DistEvalMethod,GeomType>& IM,
                            const unsigned int iTag) {
    IM.iTag=iTag;
    switch(iTag) {
      case ParticleParticle_Harmonic:
        IM.EFuncVV=EFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   varVector,varVector>;
        IM.EFuncRV=EFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   refVector,varVector>;
        IM.EFuncVR=EFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   varVector,refVector>;
        IM.EFuncRR=EFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   refVector,refVector>;
        IM.GFuncVV=GFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   varVector,varVector>;
        IM.GFuncRV=GFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   refVector,varVector>;
        IM.GFuncVR=GFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   varVector,refVector>;
        IM.GFuncRR=GFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   refVector,refVector>;
        IM.BFuncVV=BFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   varVector,varVector>;
        IM.BFuncRV=BFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   refVector,varVector>;
        IM.BFuncVR=BFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   varVector,refVector>;
        IM.BFuncRR=BFunc_ParticleParticle_Harmonic<DistEvalMethod,GeomType,
                                                   refVector,refVector>;
        break;
      case ParticleParticle_LJ612:
        IM.EFuncVV=EFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                varVector,varVector>;
        IM.EFuncRV=EFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                refVector,varVector>;
        IM.EFuncVR=EFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                varVector,refVector>;
        IM.EFuncRR=EFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                refVector,refVector>;
        IM.GFuncVV=GFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                varVector,varVector>;
        IM.GFuncRV=GFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                refVector,varVector>;
        IM.GFuncVR=GFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                varVector,refVector>;
        IM.GFuncRR=GFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                refVector,refVector>;
        IM.BFuncVV=BFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                varVector,varVector>;
        IM.BFuncRV=BFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                refVector,varVector>;
        IM.BFuncVR=BFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                varVector,refVector>;
        IM.BFuncRR=BFunc_ParticleParticle_LJ612<DistEvalMethod,GeomType,
                                                refVector,refVector>;
        break;
      case ParticleParticle_LJ612Cut:
        IM.EFuncVV=EFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   varVector,varVector>;
        IM.EFuncRV=EFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   refVector,varVector>;
        IM.EFuncVR=EFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   varVector,refVector>;
        IM.EFuncRR=EFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   refVector,refVector>;
        IM.GFuncVV=GFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   varVector,varVector>;
        IM.GFuncRV=GFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   refVector,varVector>;
        IM.GFuncVR=GFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   varVector,refVector>;
        IM.GFuncRR=GFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   refVector,refVector>;
        IM.BFuncVV=BFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   varVector,varVector>;
        IM.BFuncRV=BFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   refVector,varVector>;
        IM.BFuncVR=BFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   varVector,refVector>;
        IM.BFuncRR=BFunc_ParticleParticle_LJ612Cut<DistEvalMethod,GeomType,
                                                   refVector,refVector>;
        break;
      case ParticleParticle_Coulomb:
        IM.EFuncVV=EFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  varVector,varVector>;
        IM.EFuncRV=EFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  refVector,varVector>;
        IM.EFuncVR=EFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  varVector,refVector>;
        IM.EFuncRR=EFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  refVector,refVector>;
        IM.GFuncVV=GFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  varVector,varVector>;
        IM.GFuncRV=GFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  refVector,varVector>;
        IM.GFuncVR=GFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  varVector,refVector>;
        IM.GFuncRR=GFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  refVector,refVector>;
        IM.BFuncVV=BFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  varVector,varVector>;
        IM.BFuncRV=BFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  refVector,varVector>;
        IM.BFuncVR=BFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  varVector,refVector>;
        IM.BFuncRR=BFunc_ParticleParticle_Coulomb<DistEvalMethod,GeomType,
                                                  refVector,refVector>;
        break;
      case UnknownInteraction:
      default:
        myError("Unknown Interaction Type");
    }
  }

}

#endif

