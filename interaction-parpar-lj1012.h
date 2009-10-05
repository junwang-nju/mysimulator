
#ifndef _Interaction_ParticleParticle_LJ1012_H_
#define _Interaction_ParticleParticle_LJ1012_H_

#include "interaction-parpar-base.h"
#include "functional-lj1012.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_LJ1012(const varVector<Property*>& P,
                       const varVector<double>& Parm,
                       DistEvalObj& DEval, const GeomType& Geo,
                       double& Energy) {
    E_ParPar_Base(P,Parm,DEval,Geo,Energy,FuncFactor_lj1012);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_LJ1012(varVector<Property*>& P,
                       const varVector<double>& Parm,
                       DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,Parm,DEval,Geo,DiffFactor_lj1012);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_LJ1012(varVector<Property*>& P,
                        const varVector<double>& Parm,
                        DistEvalObj& DEval, const GeomType& Geo,
                        double& Energy) {
    EG_ParPar_Base(P,Parm,DEval,Geo,Energy,BothFactor_lj1012);
  }

}

#endif
