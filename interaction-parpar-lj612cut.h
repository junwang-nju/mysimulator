
#ifndef _Interaction_ParticleParticle_LJ612Cut_H_
#define _Interaction_ParticleParticle_LJ612Cut_H_

#include "interaction-parpar-base.h"
#include "functional-lj612cut.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_LJ612Cut(const VectorBase<PropertyComponent<refVector>*>& P,
  											 const VectorBase<uint>& Idx,
  											 const VectorBase<uint>& KIdx,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    E_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,
                  ParticleParticle_LJ612Cut,FuncFactor_lj612cut);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_LJ612Cut(const VectorBase<PropertyComponent<refVector>*>& P,
  											 const VectorBase<uint>& Idx,
  											 const VectorBase<uint>& KIdx,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         VectorBase<PropertyComponent<refVector>*>& G) {
    G_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,G,
                  ParticleParticle_LJ612Cut,DiffFactor_lj612cut);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_LJ612Cut(const VectorBase<PropertyComponent<refVector>*>& P,
  											 	const VectorBase<uint>& Idx,
  											 	const VectorBase<uint>& KIdx,
                          const ParamList& PList,
                          DistEvalObj& DEval, const GeomType& Geo,
                          double& Energy,
                          VectorBase<PropertyComponent<refVector>*>& G) {
    EG_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,G,
                   ParticleParticle_LJ612Cut,BothFactor_lj612cut);
  }

}

#endif
