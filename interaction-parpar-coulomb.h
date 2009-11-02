
#ifndef _Interaction_ParticleParticle_Coulomb_H_
#define _Interaction_ParticleParticle_Coulomb_H_

#include "interaction-parpar-base.h"
#include "functional-coulomb.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_Coulomb(const varVector<Property*>& P,
                        const ParamList& PList,
                        DistEvalObj& DEval, const GeomType& Geo,
                        double& Energy) {
    E_ParPar_Base(P,PList,DEval,Geo,Energy,FuncFactor_coulomb);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_Coulomb(const varVector<Property*>& P,
                        const ParamList& PList,
                        DistEvalObj& DEval, const GeomType& Geo) {
    G_ParPar_Base(P,PList,DEval,Geo,DiffFactor_coulomb);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_Coulomb(const varVector<Property*>& P,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    EG_ParPar_Base(P,PList,DEval,Geo,Energy,BothFactor_coulomb);
  }

}

#endif

