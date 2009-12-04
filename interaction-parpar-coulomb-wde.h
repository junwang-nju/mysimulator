
#ifndef _Interaction_ParticleParticle_Coulomb_WithDistanceDielectric_H_
#define _Interaction_ParticleParticle_Coulomb_WithDistanceDielectric_H_

#include "interaction-parpar-base.h"
#include "functional-coulomb-withDistDiel.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_CoulombWDE(const VectorBase<Property*>& P,
                           const ParamList& PList,
                           DistEvalObj& DEval, const GeomType& Geo,
                           double& Energy) {
    E_ParPar_Base(P,PList,DEval,Geo,Energy,
                  ParticleParticle_CoulombWDE,FuncFactor_coulomb_wde);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_CoulombWDE(const VectorBase<Property*>& P,
                           const ParamList& PList,
                           DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,PList,DEval,Geo,
                  ParticleParticle_CoulombWDE,DiffFactor_coulomb_wde);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_CoulombWDE(VectorBase<Property*>& P,
                            const ParamList& PList,
                            DistEvalObj& DEval, const GeomType& Geo,
                            double& Energy) {
    EG_ParPar_Base(P,PList,DEval,Geo,Energy,
                   ParticleParticle_CoulombWDE,BothFactor_coulomb_wde);
  }

}

#endif

