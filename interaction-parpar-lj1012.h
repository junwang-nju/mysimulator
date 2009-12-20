
#ifndef _Interaction_ParticleParticle_LJ1012_H_
#define _Interaction_ParticleParticle_LJ1012_H_

#include "interaction-parpar-base.h"
#include "functional-lj1012.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_LJ1012(const VectorBase<refVector<double>*>& P,
                       const VectorBase<uint>& Idx,
                       const VectorBase<uint>& KIdx,
                       const ParamList& PList,
                       DistEvalObj& DEval, const GeomType& Geo,
                       double& Energy) {
    E_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,
                  ParticleParticle_LJ1012,FuncFactor_lj1012);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_LJ1012(const VectorBase<refVector<double>*>& P,
                       const VectorBase<uint>& Idx,
                       const VectorBase<uint>& KIdx,
                       const ParamList& PList,
                       DistEvalObj& DEval, const GeomType& Geo,
                       VectorBase<refVector<double>*>& G) {
    G_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,G,
                  ParticleParticle_LJ1012,DiffFactor_lj1012);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_LJ1012(const VectorBase<refVector<double>*>& P,
                        const VectorBase<uint>& Idx,
                        const VectorBase<uint>& KIdx,
                        const ParamList& PList,
                        DistEvalObj& DEval, const GeomType& Geo,
                        double& Energy,
                        VectorBase<refVector<double>*>& G) {
    EG_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,G,
                   ParticleParticle_LJ1012,BothFactor_lj1012);
  }

}

#endif
