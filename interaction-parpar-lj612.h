
#ifndef _Interaction_ParticleParticle_LJ612_H_
#define _Interaction_ParticleParticle_LJ612_H_

#include "interaction-parpar-base.h"
#include "functional-lj612.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_LJ612(const VectorBase<Property<refVector>*>& P,
                      const VectorBase<uint>& Idx,
                      const VectorBase<uint>& KIdx,
                      const ParamList& PList,
                      DistEvalObj& DEval, const GeomType& Geo,
                      double& Energy) {
    E_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,
                  ParticleParticle_LJ612,FuncFactor_lj612);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_LJ612(const VectorBase<Property<refVector>*>& P,
                      const VectorBase<uint>& Idx,
                      const VectorBase<uint>& KIdx,
                      const ParamList& PList,
                      DistEvalObj& DEval, const GeomType& Geo,
                      VectorBase<Property<refVector>*>& G) {
    G_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,G,
                  ParticleParticle_LJ612,DiffFactor_lj612);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_LJ612(const VectorBase<Property<refVector>*>& P,
                       const VectorBase<uint>& Idx,
                       const VectorBase<uint>& KIdx,
                       const ParamList& PList,
                       DistEvalObj& DEval, const GeomType& Geo,
                       double& Energy,
                       VectorBase<Property<refVector>*>& G) {
    EG_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,G,
                   ParticleParticle_LJ612,BothFactor_lj612);
  }

}

#endif

