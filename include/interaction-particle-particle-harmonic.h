
#ifndef _Interaction_Particle_Particle_Harmonic_H_
#define _Interaction_Particle_Particle_Harmonic_H_

#include "interaction-pairwise-base.h"
#include "functional-harmonic.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_ParticleParticle_Harmonic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy) {
    EFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Energy,FuncHarmonic);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_ParticleParticle_Harmonic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Gradient) {
    GFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Gradient,
                                DiffHarmonic);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_ParticleParticle_Harmonic(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy,VectorBase<refVector<double> >& Gradient) {
    BFunc_Pairwise_Base(Coor,Idx,Param,DEval,Geo,Energy,Gradient,
                                BothHarmonic);
  }

}

#endif
