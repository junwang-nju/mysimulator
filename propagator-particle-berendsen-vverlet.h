
#ifndef _Propagator_Particle_Berendsen_VelVerlet_H_
#define _Propagator_Particle_Berendsen_VelVerlet_H_

#include "particle.h"
#include "monomer-propagator.h"
#include "propagator-particle-berendsen-vverlet-index.h"
#include "propagator-berendsen-vverlet-index.h"
#include "propagator-common-index.h"

namespace std {

  void PBV_Move_BeforeG(VectorBase<double>& Coordinate,
                        VectorBase<double>& Velocity,
                        const VectorBase<double>& Gradient,
                        FuncParamType& mnPrm,const FuncParamType& gbPrm,
                        const FuncParamType& cgbPrm) {
    Velocity.shift(-mnPrm[BasicPBV][HfDeltaTIvMPBV],Gradient);
    Coordinate.shift(cgbPrm[BasicCommon][DeltaTime],Velocity);
  }

  void PBV_Move_AfterG(VectorBase<double>& Coordinate,
                       VectorBase<double>& Velocity,
                       const VectorBase<double>& Gradient,
                       FuncParamType& mnPrm,const FuncParamType& gbPrm,
                       const FuncParamType& cgbPrm) {
    Velocity.shift(-mnPrm[BasicPBV][HfDeltaTIvMPBV],Gradient);
  }

  void PBV_Move_PostProcess(VectorBase<double>& Coordinate,
                            VectorBase<double>& Velocity,
                            const VectorBase<double>& Gradient,
                            FuncParamType& mnPrm,const FuncParamType& gbPrm,
                            const FuncParamType& cgbPrm) {
    Velocity.scale(gbPrm[BasicBV][ScaleFacBV]);
  }

  void PBV_AllocParam(FuncParamType& mnPrm, const VectorBase<uint>& SizeInf) {
    mnPrm.allocate(NumberParamPBV);
    varVector<uint> offset(NumberParamPEV),size(NumberParamPEV);
    offset[BasicPBV]=0;     size[BasicPBV]=NumberBasicPEV;
    mnPrm.BuildStructure(offset,size);
  }

  void PBV_Synchronize(const VectorBase<double>& IvMass,
                       const FuncParamType& gbPrm,const FuncParamType& cgbPrm,
                       FuncParamType& mnPrm) {
    mnPrm[BasicPBV][HfDeltaTIvMPBV]=cgbPrm[BasicCommon][HalfDeltaTime]*
                                    IvMass[0];
  }

  void SetAsPBV(MonomerPropagator& MP) {
    MP.MvFunc.allocate(NumberMoveBV);
    MP.MvFunc[BeforeGBV]=PBV_Move_BeforeG;
    MP.MvFunc[AfterGBV]=PBV_Move_AfterG;
    MP.MvFunc[PostProcessBV]=PBV_Move_PostProcess;
    MP.SetFunc.allocate(NumberSetPBV);
    MP.Alloc=PBV_AllocParam;
    MP.Sync=PBV_Synchronize;
  }

}

#endif

