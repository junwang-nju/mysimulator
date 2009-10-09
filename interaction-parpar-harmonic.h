
#ifndef _Interaction_ParticleParticle_Harmonic_H_
#define _Interaction_ParticleParticle_Harmonic_H_

#include "interaction-parpar-base.h"
#include "functional-harmonic.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_Harmonic(const varVector<Property*>& P,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    E_ParPar_Base(P,PList,DEval,Geo,Energy,FuncFactor_harmonic);
  } 

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_Harmonic(varVector<Property*>& P,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,PList,DEval,Geo,DiffFactor_harmonic);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_Harmonic(varVector<Property*>& P,
                          const ParamList& PList,
                          DistEvalObj& DEval, const GeomType& Geo,
                          double& Energy) {
    EG_ParPar_Base(P,PList,DEval,Geo,Energy,BothFactor_harmonic);
  }

}

#endif

