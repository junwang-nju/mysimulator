
#ifndef _Interaction_ParticleParticle_Harmonic_H_
#define _Interaction_ParticleParticle_Harmonic_H_

#include "interaction-parpar-base.h"
#include "functional-harmonic.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_harmonic(const varVector<Property*>& P,
                         const varVector<double>& Parm,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    E_ParPar_Base(P,Parm,DEval,Geo,Energy,FuncFactor_harmonic);
  } 

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_harmonic(varVector<Property*>& P,
                         const varVector<double>& Parm,
                         DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,Parm,DEval,Geo,DiffFactor_harmonic);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_harmonic(varVector<Property*>& P,
                          const varVector<double>& Parm,
                          DistEvalObj& DEval, const GeomType& Geo,
                          double& Energy) {
    EG_ParPar_Base(P,Parm,DEval,Geo,Energy,BothFactor_harmonic);
  }

}

#endif

