
#ifndef _Interaction_ParticleParticle_Quadrupal_Harmonic_H_
#define _Interaction_ParticleParticle_Quadrupal_Harmonic_H_

#include "functional-quadrupal-harmonic.h"
#include "interaction-parpar-base.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_QuadHarm(const VectorBase<refVector<double>*>& P,
                         const VectorBase<uint>& Idx,
                         const VectorBase<uint>& KIdx,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy) {
    E_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,
                  ParticleParticle_QuadHarmonic,FuncFactor_quadrupalharmonic);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_QuadHarm(const VectorBase<refVector<double>*>& P,
                         const VectorBase<uint>& Idx,
                         const VectorBase<uint>& KIdx,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         VectorBase<refVector<double>*>& G) {
    G_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,G,
                  ParticleParticle_QuadHarmonic,DiffFactor_quadrupalharmonic);
  }
  
  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_QuadHarm(const VectorBase<refVector<double>*>& P,
                          const VectorBase<uint>& Idx,
                          const VectorBase<uint>& KIdx,
                          const ParamList& PList,
                          DistEvalObj& DEval, const GeomType& Geo,
                          double& Energy,
                          VectorBase<refVector<double>*>& G) {
    EG_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,G,
                   ParticleParticle_QuadHarmonic,BothFactor_quadrupalharmonic);
  }

}

#endif

