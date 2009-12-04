
#ifndef _Interaction_ParticleParticle_LJ612_H_
#define _Interaction_ParticleParticle_LJ612_H_

#include "interaction-parpar-base.h"
#include "functional-lj612.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_LJ612(const VectorBase<Property*>& P,
                      const ParamList& PList,
                      DistEvalObj& DEval, const GeomType& Geo,
                      double& Energy) {
    E_ParPar_Base(P,PList,DEval,Geo,Energy,
                  ParticleParticle_LJ612,FuncFactor_lj612);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_LJ612(VectorBase<Property*>& P,
                      const ParamList& PList,
                      DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,PList,DEval,Geo,
                  ParticleParticle_LJ612,DiffFactor_lj612);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_LJ612(VectorBase<Property*>& P,
                       const ParamList& PList,
                       DistEvalObj& DEval, const GeomType& Geo,
                       double& Energy) {
    EG_ParPar_Base(P,PList,DEval,Geo,Energy,
                   ParticleParticle_LJ612,BothFactor_lj612);
  }

}

#endif
