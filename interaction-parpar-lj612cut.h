
#ifndef _Interaction_ParticleParticle_LJ612Cut_H_
#define _Interaction_ParticleParticle_LJ612Cut_H_

#include "interaction-parpar-base.h"
#include "functional-lj612cut.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_LJ612Cut(const varVector<Property*>& P,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    E_ParPar_Base(P,PList,DEval,Geo,Energy,FuncFactor_lj612cut);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_LJ612Cut(varVector<Property*>& P,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,PList,DEval,Geo,DiffFactor_lj612cut);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_LJ612Cut(const varVector<Property*>& P,
                          const ParamList& PList,
                          DistEvalObj& DEval, const GeomType& Geo,
                          double& Energy) {
    EG_ParPar_Base(P,PList,DEval,Geo,Energy,BothFactor_lj612cut);
  }

}

#endif
