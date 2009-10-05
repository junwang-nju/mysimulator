
#ifndef _Interaction_ParticleParticle_LJ612_H_
#define _Interaction_ParticleParticle_LJ612_H_

#include "property.h"
#include "functional-lj612.h"
#include "distance-evaluation.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_LJ612(const varVector<Property*>& P,
                      const varVector<double>& Parm, DistEvalObj& DEval,
                      const GeomType& Geo, double& Energy) {
    double DistSQ=DEval(*P[0],*P[1],Geo);
    double e;
    FuncFactor_lj612(DistSQ,Parm,e);
    Energy+=e;
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_LJ612(const varVector<Property*>& P,
                      const varVector<double>& Parm, DistEvalObj& DEval,
                      const GeomType& Geo) {
    double DistSQ=DEval(*P[0],*P[1],Geo,' ');
    double ef;
    DiffFactor_lj612(DistSQ,Parm,ef);
    P[0]->Gradient.shift(+ef,DEval.DisplaceVector());
    P[1]->Gradient.shift(-ef,DEval.DisplaceVector());
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_LJ612(const varVector<Property*>& P,
                       const varVector<double>& Parm, DistEvalObj& DEval,
                       const GeomType& Geo, double& Energy) {
    double DistSQ=DEval(*P[0],*P[1],Geo,' ');
    double ee,ef;
    BothFactor_lj612(DistSQ,Parm,ee,ef);
    Energy+=ee;
    P[0]->Gradient.shift(+ef,DEval.DisplaceVector());
    P[1]->Gradient.shift(-ef,DEval.DisplaceVector());
  }

}

#endif
