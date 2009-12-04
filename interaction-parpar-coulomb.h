
#ifndef _Interaction_ParticleParticle_Coulomb_H_
#define _Interaction_ParticleParticle_Coulomb_H_

#include "interaction-parpar-base.h"
#include "functional-coulomb.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_Coulomb(const VectorBase<Property*>& P,
                        const ParamList& PList,
                        DistEvalObj& DEval, const GeomType& Geo,
                        double& Energy) {
    E_ParPar_Base(P,PList,DEval,Geo,Energy,
                  ParticleParticle_Coulomb,FuncFactor_coulomb);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_Coulomb(const VectorBase<Property*>& P,
                        const ParamList& PList,
                        DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,PList,DEval,Geo,
                  ParticleParticle_Coulomb,DiffFactor_coulomb);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_Coulomb(const VectorBase<Property*>& P,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    EG_ParPar_Base(P,PList,DEval,Geo,Energy,
                   ParticleParticle_Coulomb,BothFactor_coulomb);
  }

}

#endif

