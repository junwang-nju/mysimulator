
#ifndef _Interaction_ParticleParticle_Harmonic_H_
#define _Interaction_ParticleParticle_Harmonic_H_

#include "interaction-parpar-base.h"
#include "functional-harmonic.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_Harmonic(const VectorBase<PropertyComponent<refVector>*>& P,
                         const VectorBase<uint>& Idx,
                         const VectorBase<uint>& KIdx,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    E_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,
                  ParticleParticle_Harmonic,FuncFactor_harmonic);
  } 

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_Harmonic(const VectorBase<PropertyComponent<refVector>*>& P,
                         const VectorBase<uint>& Idx,
                         const VectorBase<uint>& KIdx,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         VectorBase<PropertyComponent<refVector>*>& G) {
    G_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,G,
                  ParticleParticle_Harmonic,DiffFactor_harmonic);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_Harmonic(const VectorBase<PropertyComponent<refVector>*>& P,
                          const VectorBase<uint>& Idx,
                          const VectorBase<uint>& KIdx,
                          const ParamList& PList,
                          DistEvalObj& DEval, const GeomType& Geo,
                          double& Energy,
                          VectorBase<PropertyComponent<refVector>*>& G) {
    EG_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,G,
                   ParticleParticle_Harmonic,BothFactor_harmonic);
  }

}

#endif

