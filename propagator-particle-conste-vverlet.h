
#ifndef _Propagator_Particle_ConstE_vverlet_H_
#define _Propagator_Particle_ConstE_vverlet_H_

#include "property.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "monomer-propagator-format.h"

namespace std {

  enum PropagatorParam_4ParticleConstEVelVerlet {
    Basic=0,
    HfDeltaT_ivM,
    DeltaTime=0,
    HalfDeltaTime,
  };

  template <typename DistEvalObj, typename GeomType>
  void SetAs_ParticleConstEVelVerlet(
      MonomerPropagatorFormat<DistEvalObj,GeomType>& MPF) {
    MPF.mvfunc.allocate(2);
    MPF.setfunc.allocate(1);
    MPF.mvfunc[0]=ParticleConstEVelVerlet_Move_BeforeG<DistEvalObj,GeomType>;
    MPF.mvfunc[1]=ParticleConstEVelVerlet_Move_AfterG<DistEvalObj,GeomType>;
    MPF.setfunc[0]=ParticleConstEVelVerlet_SetTimeStep;
    MPF.allocparam=ParticleConstEVelVerlet_AllocateParam;
    MPF.sync=ParticleConstEVelVerlet_Synchronize;
  }

  template <typename DistEvalObj, typename GeomType>
  void ParticleConstEVelVerlet_Move_BeforeG(
        Property& nowProp,
        varVector<Property>& PropSet,
        const ParamList& PList,
        varVector<IDList<DistEvalObj,GeomType> >& IDLS,
        const varVector<varVector<double> >& mvParm,
        DistEvalObj& DEval, const GeomType& Geo) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM],nowProp.Gradient);
    nowProp.Coordinate.shift(mvParm[Basic][HalfDeltaTime],nowProp.Velocity);
  }

  template <typename DistEvalObj, typename GeomType>
  void ParticleConstEVelVerlet_Move_AfterG(
        Property& nowProp,
        varVector<Property>& PropSet,
        const ParamList& PList,
        varVector<IDList<DistEvalObj,GeomType> >& IDLS,
        const varVector<varVector<double> >& mvParm,
        DistEvalObj& DEval, const GeomType& Geo) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM],nowProp.Gradient);
  }

  void ParticleConstEVelVerlet_AllocateParam(
      varVector<varVector<double> >& param,const uint& propdim) {
    param.allocate(2);
    param[0].allocate(2);
    param[1].allocate(propdim);
  }

  void ParticleConstEVelVerlet_SetTimeStep(
      varVector<varVector<double> >& param,
      const double* tstep, const uint n=1) {
    param[Basic][DeltaTime]=tstep;
    param[Basic][HalfDeltaTime]=0.5*param[Basic][DeltaTime];
  }

  void ParticleConstEVelVerlet_Synchronize(
      const Property& nowProp, varVector<varVector<double> >& param) {
    param[HfDeltaT_ivM]=nowProp.ivMass;
    param[HfDeltaT_ivM].scale(param[Basic][HalfDeltaTime]);
  }

}

#endif

