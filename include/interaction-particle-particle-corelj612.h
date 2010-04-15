
#ifndef _Interaction_Particle_Particle_CoreLJ612_H_
#define _Interaction_Particle_Particle_CoreLJ612_H_

#include "interaction-pairwise-base.h"
#include "functional-corelj612.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_ParticleParticle_CoreLJ12(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >&,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy) {
    EFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Energy,FuncCoreLJ612);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_ParticleParticle_CoreLJ12(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >&,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Grad) {
    GFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Grad,DiffCoreLJ612);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_ParticleParticle_CoreLJ12(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      VectorBase<refVector<double> >&,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Grad) {
    BFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Grad,BothCoreLJ612);
  }

}

#endif
