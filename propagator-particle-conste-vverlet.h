
#ifndef _Propagator_Particle_ConstE_vverlet_H_
#define _Propagator_Particle_ConstE_vverlet_H_

#include "property.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "monomer-propagator-format.h"

namespace std {

  enum PropagatorParam_4ParticleConstEVelVerlet {
    Basic_4PEV=0,
    HfDeltaT_ivM_4PEV,
    NumberParam_4PEV,
    DeltaTime_4PEV=0,
    HalfDeltaTime_4PEV,
    NumberBasicParam_4PEV,
    BeforeG_4PEV=0,
    AfterG_4PEV,
    NumberMoveFunc_4PEV,
    SetTimeStep_4PEV=0,
    NumberSetFunc_4PEV
  };

  void ParticleConstEVelVerlet_Move_BeforeG(
        Property& nowProp,
        const varVector<varVector<double> >& mvParm) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM_4PEV],nowProp.Gradient);
    nowProp.Coordinate.shift(mvParm[Basic_4PEV][DeltaTime_4PEV],
                             nowProp.Velocity);
  }

  void ParticleConstEVelVerlet_Move_AfterG(
        Property& nowProp,
        const varVector<varVector<double> >& mvParm) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM_4PEV],nowProp.Gradient);
  }

  void ParticleConstEVelVerlet_AllocateParam(
      varVector<varVector<double> >& param,const uint* propdim,const uint& n) {
    param.allocate(static_cast<uint>(NumberParam_4PEV));
    param[Basic_4PEV].allocate(static_cast<uint>(NumberBasicParam_4PEV));
    param[HfDeltaT_ivM_4PEV].allocate(*propdim);
  }

  void ParticleConstEVelVerlet_SetTimeStep(
      varVector<varVector<double> >& param,
      const double* tstep, const uint& n=1) {
    param[Basic_4PEV][DeltaTime_4PEV]=*tstep;
    param[Basic_4PEV][HalfDeltaTime_4PEV]=
        0.5*param[Basic_4PEV][DeltaTime_4PEV];
  }

  void ParticleConstEVelVerlet_Synchronize(
      const Property& nowProp, varVector<varVector<double> >& param) {
    param[HfDeltaT_ivM_4PEV]=nowProp.ivMass[0];
    param[HfDeltaT_ivM_4PEV].scale(param[Basic_4PEV][HalfDeltaTime_4PEV]);
  }

  template <typename DistEvalObj, typename GeomType>
  void SetAs_ParticleConstEVelVerlet(
      MonomerPropagatorFormat<DistEvalObj,GeomType>& MPF) {
    MPF.mvfunc.allocate(static_cast<uint>(NumberMoveFunc_4PEV));
    MPF.setfunc.allocate(static_cast<uint>(NumberSetFunc_4PEV));
    MPF.mvfunc[BeforeG_4PEV]=ParticleConstEVelVerlet_Move_BeforeG;
    MPF.mvfunc[AfterG_4PEV]=ParticleConstEVelVerlet_Move_AfterG;
    MPF.setfunc[SetTimeStep_4PEV]=ParticleConstEVelVerlet_SetTimeStep;
    MPF.alloc=ParticleConstEVelVerlet_AllocateParam;
    MPF.sync=ParticleConstEVelVerlet_Synchronize;
  }

}

#endif

