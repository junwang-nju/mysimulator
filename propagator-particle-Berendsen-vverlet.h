
#ifndef _Propagator_Particle_Berendsen_VelVerlet_H_
#define _Propagator_Particle_Berendsen_VelVerlet_H_

#include "property.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "monomer-propagator-format.h"

namespace std {

  enum PropagatorParam_4ParticleBerendsenVelVerlet {
    Basic_4PBV=0,
    HfDeltaT_ivM_4PBV,
    TScaleFac_4PBV,
    NumberParam_4PBV,
    DeltaTime_4PBV=0,
    HalfDeltaTime_4PBV,
    RelaxTime_4PBV,
    DeltaT_ivRelaxT_4PBV,
    NumberBasicParam_4PBV,
    BeforeG_4PBV=0,
    AfterG_4PBV,
    PostProcess_4PBV,
    NumberMoveFunc_4PBV,
    SetTimeStep_4PBV=0,
    SetRelaxTime_4PBV,
    NumberSetFunc_4PBV
  };

  void ParticleBerendsenVelVerlet_Move_BeforeG(
        Property& nowProp,
        const varVector<varVector<double> >& mvParm) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM_4PBV],nowProp.Gradient);
    nowProp.Coordinate.shift(mvParm[Basic_4PBV][DeltaTime_4PBV],
                             nowProp.Velocity);
  }

  void ParticleBerendsenVelVerlet_Move_AfterG(
        Property& nowProp,
        const varVector<varVector<double> >& mvParm) {
    nowProp.Velocity.shift(-1.,mvParm[HfDeltaT_ivM_4PBV],nowProp.Gradient);
  }

  void ParticleBerendsenVelVerlet_Move_PostProcess(
        Property& nowProp,
        const varVector<varVector<double> >& mvParm) {
    nowProp.Velocity.scale(mvParm[TScaleFac_4PBV][0]);
  }

  void ParticleBerendsenVelVerlet_AllocateParam(
      varVector<varVector<double> >& param,
      const uint* propdim, const uint& n){
    param.allocate(static_cast<uint>(NumberParam_4PBV));
    param[Basic_4PBV].allocate(static_cast<uint>(NumberBasicParam_4PBV));
    param[HfDeltaT_ivM_4PBV].allocate(*propdim);
    param[TScaleFac_4PBV].allocate(1);
  }

  void ParticleBerendsenVelVerlet_SetTimeStep(
      varVector<varVector<double> >& param,
      const double* ddata, const uint& n=1) {
    param[Basic_4PBV][DeltaTime_4PBV]=*ddata;
    param[Basic_4PBV][HalfDeltaTime_4PBV]=
        0.5*param[Basic_4PBV][DeltaTime_4PBV];
    param[Basic_4PBV][DeltaT_ivRelaxT_4PBV]=
        param[Basic_4PBV][DeltaTime_4PBV]/
        param[Basic_4PBV][RelaxTime_4PBV];
  }

  void ParticleBerendsenVelVerlet_SetRelaxTime(
      varVector<varVector<double> >& param,
      const double* ddata, const uint& n=1) {
    param[Basic_4PBV][RelaxTime_4PBV]=*ddata;
    param[Basic_4PBV][DeltaT_ivRelaxT_4PBV]=
        param[Basic_4PBV][DeltaTime_4PBV]/
        param[Basic_4PBV][RelaxTime_4PBV];
  }

  void ParticleBerendsenVelVerlet_Synchronize(
      const Property& nowProp, varVector<varVector<double> >& param) {
    param[HfDeltaT_ivM_4PBV]=nowProp.ivMass[0];
    param[HfDeltaT_ivM_4PBV].scale(param[Basic_4PBV][HalfDeltaTime_4PBV]);
  }

  template <typename DistEvalObj, typename GeomType>
  void SetAs_ParticleBerendsenVelVerlet(
      MonomerPropagatorFormat<DistEvalObj,GeomType>& MPF) {
    MPF.mvfunc.allocate(static_cast<uint>(NumberMoveFunc_4PBV));
    MPF.mvfunc[BeforeG_4PBV]=ParticleBerendsenVelVerlet_Move_BeforeG;
    MPF.mvfunc[AfterG_4PBV]=ParticleConstEVelVerlet_Move_AfterG;
    MPF.mvfunc[PostProcess_4PBV]=ParticleBerendsenVelVerlet_Move_PostProcess;
    MPF.setfunc.allocate(static_cast<uint>(NumberSetFunc_4PBV));
    MPF.setfunc[SetTimeStep_4PBV]=ParticleBerendsenVelVerlet_SetTimeStep;
    MPF.setfunc[SetRelaxTime_4PBV]=ParticleBerendsenVelVerlet_SetRelaxTime;
    MPF.alloc=ParticleBerendsenVelVerlet_AllocateParam;
    MPF.sync=ParticleBerendsenVelVerlet_Synchronize;
  }

}

#endif

