
#ifndef _Propagator_Berendsen_VelocityVerlet_H_
#define _Propagator_Berendsen_VelocityVerlet_H_

#include "propagator.h"
#include "interaction-4listset.h"
#include "vector-op.h"
#include "propagator-set-common.h"
#include <cmath>

namespace std {

  void BV_Allocate(varVector<PropagatorDataElementType>& GPrm) {
    GPrm.allocate(NumberParamBV);
  }

  void BV_Synchronize(
      const VectorBase<refVector<double> >&,
      const VectorBase<refVector<double> >& DMask,
      VectorBase<PropagatorDataElementType>& GParam) {
    double dof=0.;
    for(unsigned int i=0;i<DMask.size();++i) dof+=sumABS(DMask[i]);
    GParam[BV_DegreeFreedom]=dof;
    GParam[BV_DeltaTIvRelaxT]=GParam[DeltaTime].d/GParam[BV_RelaxTime].d;
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BV_Step(
      const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
      VectorBase<refVector<double> >& Coor,
      VectorBase<refVector<double> >& Vel,
      VectorBase<refVector<double> >& Grad,
      const VectorBase<refVector<double> >& Mass,
      const VectorBase<refVector<unsigned int> >& IdxLst,
      const VectorBase<refVector<double> >& ParamLst,
      VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<MonomerPropagator>& Unit,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo) {
    assert(Coor.size()==Vel.size());
    assert(Coor.size()==Grad.size());
    assert(Coor.size()==Unit.size());
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[BV_BeforeG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
    DEval.update();
    for(unsigned int i=0;i<Grad.size();++i) Grad[i]=0.;
    GFunc(Coor,IM,IdxLst,ParamLst,DEval,Geo,Grad);
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[BV_AfterG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
    double fac=0.;
    for(unsigned int i=0;i<Vel.size();++i) fac=normSQ(Vel[i])*Mass[i][0];
    fac=GParam[BV_Temperature].d*GParam[BV_DegreeFreedom].d/fac;
    GParam[BV_ScaleFactor]=sqrt(GParam[BV_DeltaTIvRelaxT].d*(fac-1.));
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[BV_PostProcess](Coor[i],Vel[i],Grad[i],GParam,
                                   Unit[i].Param);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void BV_Step(
      const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
      VectorBase<refVector<double> >& Coor,
      VectorBase<refVector<double> >& Vel,
      VectorBase<refVector<double> >& Grad,
      const VectorBase<refVector<double> >& Mass,
      const VectorBase<refVector<refVector<unsigned int> > >& IdxLst,
      const VectorBase<refVector<refVector<double> > >& ParamLst,
      VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<MonomerPropagator>& Unit,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo) {
    assert(Coor.size()==Vel.size());
    assert(Coor.size()==Grad.size());
    assert(Coor.size()==Unit.size());
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[BV_BeforeG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
    DEval.update();
    for(unsigned int i=0;i<Grad.size();++i) Grad[i]=0.;
    GFunc(Coor,IM,IdxLst,ParamLst,DEval,Geo,Grad);
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[BV_AfterG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
    double fac=0.;
    for(unsigned int i=0;i<Vel.size();++i) fac=normSQ(Vel[i])*Mass[i][0];
    fac=GParam[BV_Temperature].d*GParam[BV_DegreeFreedom].d/fac;
    GParam[BV_ScaleFactor]=sqrt(GParam[BV_DeltaTIvRelaxT].d*(fac-1.));
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[BV_PostProcess](Coor[i],Vel[i],Grad[i],GParam,
                                   Unit[i].Param);
  }

  void BV_SetTemperature(VectorBase<PropagatorDataElementType>& GPrm,
                         const void* pd) {
    GPrm[BV_Temperature]=*reinterpret_cast<const double*>(pd);
  }

  void BV_SetRelaxTime(VectorBase<PropagatorDataElementType>& GPrm,
                       const void* pd) {
    GPrm[BV_RelaxTime]=*reinterpret_cast<const double*>(pd);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void SetAsBV(Propagator<DistEvalMethod,GeomType>& P) {
    P.GAlloc=BV_Allocate;
    P.GSync=BV_Synchronize;
    P.GSet.allocate(NumberSetBV);
    AssignCommonSet4Propagator(P.GSet);
    P.GSet[TemperatureInBV]=BV_SetTemperature;
    P.GSet[RelaxTimeInBV]=BV_SetRelaxTime;
    P.HStepVV=BV_Step<DistEvalMethod,GeomType,varVector,varVector>;
    P.HStepVR=BV_Step<DistEvalMethod,GeomType,varVector,refVector>;
    P.HStepRV=BV_Step<DistEvalMethod,GeomType,refVector,varVector>;
    P.HStepRR=BV_Step<DistEvalMethod,GeomType,refVector,refVector>;
    P.FStepVV=BV_Step<DistEvalMethod,GeomType,varVector,varVector>;
    P.FStepVR=BV_Step<DistEvalMethod,GeomType,varVector,refVector>;
    P.FStepRV=BV_Step<DistEvalMethod,GeomType,refVector,varVector>;
    P.FStepRR=BV_Step<DistEvalMethod,GeomType,refVector,refVector>;
  }

}

#endif

