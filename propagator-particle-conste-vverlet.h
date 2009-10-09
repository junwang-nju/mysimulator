
#ifndef _Propagator_Particle_ConstE_vverlet_H_
#define _Propagator_Particle_ConstE_vverlet_H_

#include "property.h"
#include "param-list.h"
#include "interaction-4listset.h"

namespace std {

  enum PropagatorParam_4ParticleConstEVelVerlet {
    Basic=0,
    HfDeltaT_ivM,
    DeltaTime=0,
    HalfDeltaTime,
  };

  template <typename DistEvalObj, typename GeomType>
  void Particle_ConstE_VelVerlet_Move( ///!!!! not correct!!!!!!!!!!!!
      Property& nowProp,
      varVector<Property>& PropSet,
      const ParamList& PList,
      varVector<IDList<DistEvalObj,GeomType> >& IDLS,
      const varVector<varVector<double> >& mvParm,
      DistEvalObj& DEval, const GeomType& Geo) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM],nowProp.Gradient);
    nowProp.Coordinate.shift(mvParm[Basic][HalfDeltaTime],nowProp.Velocity);
    G_ListSet(PropSet,PList,IDLS,DEval,Geo);
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM],nowProp.Gradient);
  }

  void Particle_ConstE_VelVerlet_Allocate(
      varVector<varVector<double> >& param,const uint& propdim) {
    param.allocate(2);
    param[0].allocate(2);
    param[1].allocate(propdim);
  }

  void Particle_ConstE_VelVerlet_SetTimeStep(
      varVector<varVector<double> >& param, const double& tstep) {
    param[Basic][DeltaTime]=tstep;
    param[Basic][HalfDeltaTime]=0.5*param[Basic][DeltaTime];
  }

  void Particle_ConstE_VelVerlet_Synchronize(
      const Property& nowProp, varVector<varVector<double> >& param) {
    param[HfDeltaT_ivM]=nowProp.ivMass;
    param[HfDeltaT_ivM].scale(param[Basic][HalfDeltaTime]);
  }

}

#endif

