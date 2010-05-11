
#ifndef _Interaction_Particle_Particle_Core12_H_
#define _Interaction_Particle_Particle_Core12_H_

#include "interaction-pairwise-base.h"
#include "functional-core12.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_ParticleParticle_Core12(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >&,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy) {
    EFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Energy,FuncCore12);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_ParticleParticle_Core12(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >&,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Grad) {
    GFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Grad,DiffCore12);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_ParticleParticle_Core12(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >&,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Grad) {
    BFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Energy,Grad,BothCore12);
  }

}

#endif

