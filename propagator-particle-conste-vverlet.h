
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

  void ParticleConstEVelVerlet_Move_BeforeG(
        Property& nowProp,
        const varVector<varVector<double> >& mvParm) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM],nowProp.Gradient);
    nowProp.Coordinate.shift(mvParm[Basic][DeltaTime],nowProp.Velocity);
  }

  void ParticleConstEVelVerlet_Move_AfterG(
        Property& nowProp,
        const varVector<varVector<double> >& mvParm) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM],nowProp.Gradient);
  }

  void ParticleConstEVelVerlet_AllocateParam(
      varVector<varVector<double> >& param,const uint* propdim,const uint& n) {
    param.allocate(2);
    param[0].allocate(2);
    param[1].allocate(*propdim);
  }

  void ParticleConstEVelVerlet_SetTimeStep(
      varVector<varVector<double> >& param,
      const double* tstep, const uint& n=1) {
    param[Basic][DeltaTime]=*tstep;
    param[Basic][HalfDeltaTime]=0.5*param[Basic][DeltaTime];
  }

  void ParticleConstEVelVerlet_Synchronize(
      const Property& nowProp, varVector<varVector<double> >& param) {
    param[HfDeltaT_ivM]=nowProp.ivMass;
    param[HfDeltaT_ivM].scale(param[Basic][HalfDeltaTime]);
  }

  template <typename DistEvalObj, typename GeomType>
  void SetAs_ParticleConstEVelVerlet(
      MonomerPropagatorFormat<DistEvalObj,GeomType>& MPF) {
    MPF.mvfunc.allocate(2);
    MPF.setfunc.allocate(1);
    MPF.mvfunc[0]=ParticleConstEVelVerlet_Move_BeforeG;
    MPF.mvfunc[1]=ParticleConstEVelVerlet_Move_AfterG;
    MPF.setfunc[0]=ParticleConstEVelVerlet_SetTimeStep;
    MPF.alloc=ParticleConstEVelVerlet_AllocateParam;
    MPF.sync=ParticleConstEVelVerlet_Synchronize;
  }

}

#endif

