
#ifndef _Interaction_ParticleParticle_Quadrupal_Harmonic_H_
#define _Interaction_ParticleParticle_Quadrupal_Harmonic_H_

#include "functional-quadrupal-harmonic.h"
#include "interaction-parpar-base.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_QuadHarm(const VectorBase<Property>& P,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    E_ParPar_Base(P,PList,DEval,Geo,Energy,
                  ParticleParticle_QuadHarmonic,FuncFactor_quadrupalharmonic);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_QuadHarm(const VectorBase<Property>& P,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,PList,DEval,Geo,
                  ParticleParticle_QuadHarmonic,DiffFactor_quadrupalharmonic);
  }
  
  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_QuadHarm(const VectorBase<Property>& P,
                          const ParamList& PList,
                          DistEvalObj& DEval, const GeomType& Geo,
                          double& Energy) {
    EG_ParPar_Base(P,PList,DEval,Geo,Energy,
                   ParticleParticle_QuadHarmonic,BothFactor_quadrupalharmonic);
  }

}

#endif

