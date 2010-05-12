
#ifndef _Interaction_ParticleParticle_Coulomb_H_
#define _Interaction_ParticleParticle_Coulomb_H_

#include "interaction-parpar-base.h"
#include "functional-coulomb.h"
#include "interaction-type.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void E_ParPar_Coulomb(const VectorBase<refVector<double>*>& P,
                        const VectorBase<uint>& Idx,
                        const VectorBase<uint>& KIdx,
                        const ParamList& PList,
                        DistEvalObj& DEval, const GeomType& Geo,
                        double& Energy) {
    E_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,
                  ParticleParticle_Coulomb,FuncFactor_coulomb);
  }

  template <typename DistEvalObj, typename GeomType>
  void G_ParPar_Coulomb(const VectorBase<refVector<double>*>& P,
                        const VectorBase<uint>& Idx,
                        const VectorBase<uint>& KIdx,
                        const ParamList& PList,
                        DistEvalObj& DEval, const GeomType& Geo,
                        VectorBase<refVector<double>*>& G) {
    G_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,G,
                  ParticleParticle_Coulomb,DiffFactor_coulomb);
  }

  template <typename DistEvalObj, typename GeomType>
  void EG_ParPar_Coulomb(const VectorBase<refVector<double>*>& P,
                         const VectorBase<uint>& Idx,
                         const VectorBase<uint>& KIdx,
                         const ParamList& PList,
                         DistEvalObj& DEval, const GeomType& Geo,
                         double& Energy,
                         VectorBase<refVector<double>*>& G) {
    EG_ParPar_Base(P,Idx,KIdx,PList,DEval,Geo,Energy,G,
                   ParticleParticle_Coulomb,BothFactor_coulomb);
  }

}

#endif

