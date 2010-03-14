
#ifndef _Interaction_Particle_Particle_Base_H_
#define _Interaction_Particle_Particle_Base_H_

#include "parameter-list-base.h"

namespace std {

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EFunc_ParticleParticle_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy,
      void (*efunc)(const double, const VectorBase<double>&, double&)) {
    DEval.Evaluate(Coor[0],Coor[1],Idx[0],Idx[1],Geo);
    double DistSQ=DEval.DistanceSQ();
    double ee;
    efunc(DistSQ,Param,ee);
    Energy+=ee;
  } 

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void GFunc_ParticleParticle_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      VectorBase<refVector<double> >& Gradient,
      void (*gfunc)(const double, const VectorBase<double>&, double&)) {
    DEval.Evaluate(Coor[0],Coor[1],Idx[0],Idx[1],Geo);
    double DistSQ=DEval.DistanceSQ();
    double ef;
    gfunc(DistSQ,Param,ef);
    Gradient[0].shift(+ef,DEval.Displacement());
    Gradient[1].shift(-ef,DEval.Displacement());
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BFunc_ParticleParticle_Base(
      const VectorBase<refVector<double> >& Coor,
      const VectorBase<unsigned int>& Idx, const VectorBase<double>& Param,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo,
      double& Energy, VectorBase<refVector<double> >& Gradient,
      void (*bfunc)(const double,const VectorBase<double>&,double&,double&)) {
    DEval.Evaluate(Coor[0],Coor[1],Idx[0],Idx[1],Geo);
    double DistSQ=DEval.DistanceSQ();
    double ee,ef;
    bfunc(DistSQ,Param,ee,ef);
    Energy+=ee;
    Gradient[0].shift(+ef,DEval.Displacement());
    Gradient[1].shift(-ef,DEval.Displacement());
  }

}

#endif

