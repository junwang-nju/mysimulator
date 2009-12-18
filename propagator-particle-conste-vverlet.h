
#ifndef _Propagator_Particle_ConstE_VelVerlet_H_
#define _Propagator_Particle_ConstE_VelVerlet_H_

#include "particle.h"
#include "monomer-propagator.h"
#include "propagator-particle-conste-vverlet-index.h"
#include "propagator-conste-vverlet-index.h"
#include "propagator-common-index.h"

namespace std {

  void PEV_Move_BeforeG(VectorBase<double>& Coordinate,
                        VectorBase<double>& Velocity,
                        const VectorBase<double>& Gradient,
                        FuncParamType& mnPrm, const FuncParamType& gbPrm,
                        const FuncParamType& cgbPrm) {
    Velocity.shift(-mnPrm[BasicPEV][HfDeltaTIvMPEV],Gradient);
    Coordinate.shift(cgbPrm[BasicCommon][DeltaTime],Velocity);
  }

  void PEV_Move_AfterG(VectorBase<double>& Coordinate,
                       VectorBase<double>& Velocity,
                       const VectorBase<double>& Gradient,
                       FuncParamType& mnPrm, const FuncParamType& gbPrm,
                       const FuncParamType& cgbPrm){
    Velocity.shift(-mnPrm[BasicPEV][HfDeltaTIvMPEV],Gradient);
  }

  void PEV_AllocParam(FuncParamType& mnPrm, const VectorBase<uint>& SizeInf) {
    mnPrm.allocate(NumberParamPEV);
    varVector<uint> offset(NumberParamPEV),size(NumberParamPEV);
    offset[BasicPEV]=0;
    size[BasicPEV]=NumberBasicPEV;
    mnPrm.BuildStructure(offset,size);
  }

  void PEV_Synchronize(const VectorBase<double>& IvMass,
                       const FuncParamType& gbPrm, const FuncParamType& cgbPrm,
                       FuncParamType& mnPrm) {
    mnPrm[BasicPEV][HfDeltaTIvMPEV]=cgbPrm[BasicCommon][HalfDeltaTime]*
                                    IvMass[0];
  }

  void SetAsPEV(MonomerPropagator& MP) {
    MP.MvFunc.allocate(NumberMoveEV);
    MP.MvFunc[BeforeGEV]=PEV_Move_BeforeG;
    MP.MvFunc[AfterGEV]=PEV_Move_AfterG;
    MP.SetFunc.allocate(NumberSetPEV);
    MP.Alloc=PEV_AllocParam;
    MP.Sync=PEV_Synchronize;
  }

}

#endif
