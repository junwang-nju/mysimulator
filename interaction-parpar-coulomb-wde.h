
#ifndef _Interaction_ParticleParticle_Coulomb_WithDistanceDielectric_H_
#define _Interaction_ParticleParticle_Coulomb_WithDistanceDielectric_H_

#include "interaction-parpar-base.h"
#include "functional-coulomb-withDistDiel.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_CoulombWDE(const VectorBase<Property<refVector>*>& P,
                           const VectorBase<uint>& Idx,
                           const VectorBase<uint>& KIdx,
                           const ParamList& PList,
                           DistEvalObj& DEval, const GeomType& Geo,
                           double& Energy) {
    E_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,
                  ParticleParticle_CoulombWDE,FuncFactor_coulomb_wde);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_CoulombWDE(const VectorBase<Property<refVector>*>& P,
                           const VectorBase<uint>& Idx,
                           const VectorBase<uint>& KIdx,
                           const ParamList& PList,
                           DistEvalObj& DEval, const GeomType& Geo,
                           VectorBase<Property<refVector>*>& G) {
    G_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,G,
                  ParticleParticle_CoulombWDE,DiffFactor_coulomb_wde);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_CoulombWDE(const VectorBase<Property<refVector>*>& P,
                           const VectorBase<uint>& Idx,
                           const VectorBase<uint>& KIdx,
                            const ParamList& PList,
                            DistEvalObj& DEval, const GeomType& Geo,
                            double& Energy,
                            VectorBase<Property<refVector>*>& G) {
    EG_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,G,
                   ParticleParticle_CoulombWDE,BothFactor_coulomb_wde);
  }

}

#endif

