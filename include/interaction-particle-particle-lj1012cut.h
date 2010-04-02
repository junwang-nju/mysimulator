
#ifndef _Interaction_Particle_Particle_LJ1012Cut_H_
#define _Interaction_Particle_Particle_LJ1012Cut_H_

#include "interaction-particle-particle-base.h"
#include "functional-lj1012cut.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_ParticleParticle_LJ1012Cut(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy) {
    EFunc_ParticleParticle_Base(Coor,Idx,Param,DEval,Geo,Energy,FuncLJ1012Cut);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_ParticleParticle_LJ1012Cut(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Gradient) {
    GFunc_ParticleParticle_Base(Coor,Idx,Param,DEval,Geo,Gradient,
                                DiffLJ1012Cut);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_ParticleParticle_LJ1012Cut(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Gradient) {
    BFunc_ParticleParticle_Base(Coor,Idx,Param,DEval,Geo,Energy,Gradient,
                                BothLJ1012Cut);
  }

}

#endif

