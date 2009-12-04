
#ifndef _Interaction_ParticleParticle_LJ1012_H_
#define _Interaction_ParticleParticle_LJ1012_H_

#include "interaction-parpar-base.h"
#include "functional-lj1012.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_LJ1012(const VectorBase<Property*>& P,
                       const ParamList& PList,
                       DistEvalObj& DEval, const GeomType& Geo,
                       double& Energy) {
    E_ParPar_Base(P,PList,DEval,Geo,Energy,
                  ParticleParticle_LJ1012,FuncFactor_lj1012);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_LJ1012(VectorBase<Property*>& P,
                       const ParamList& PList,
                       DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,PList,DEval,Geo,
                  ParticleParticle_LJ1012,DiffFactor_lj1012);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_LJ1012(VectorBase<Property*>& P,
      const ParamList& PList,
                        DistEvalObj& DEval, const GeomType& Geo,
                        double& Energy) {
    EG_ParPar_Base(P,PList,DEval,Geo,Energy,
                   ParticleParticle_LJ1012,BothFactor_lj1012);
  }

}

#endif
