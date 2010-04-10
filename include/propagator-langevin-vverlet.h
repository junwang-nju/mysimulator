
#ifndef _Propagator_Langevin_VelocityVerlet_H_
#define _Propagator_Langevin_VelocityVerlet_H_

#include "propagator.h"
#include "propagator-parameter-name-langevin-vverlet.h"
#include "interaction-4listset.h"
#include "propagator-set-common.h"

namespace std {

  void LV_Allocate(varVector<PropagatorDataElementType>& GPrm) {
    GPrm.allocate(NumberParamLV);
  }

  void LV_Synchronize(
      const VectorBase<refVector<double> >& IvMass,
      const VectorBase<refVector<double> >&,
      VectorBase<PropagatorDataElementType>& GParam) {
    GParam[LV_TemperatureDeltaT]=GParam[LV_Temperature].d
                                *GParam[DeltaTime].d;
  }

  void LV_SetTemperature(
      VectorBase<PropagatorDataElementType>& GParam, const void* pd) {
    GParam[LV_Temperature]=*reinterpret_cast<const double*>(pd);
  }

  void LV_SetViscosity(
      VectorBase<PropagatorDataElementType>& GParam, const void* pd) {
    GParam[LV_ViscosityCoef]=*reinterpret_cast<const double*>(pd);
  }

  void LV_SetGaussianRNGPointer(
      VectorBase<PropagatorDataElementType>& GParam, const void* pd) {
    GParam[LV_GaussianRNGPointer].vptr=const_cast<void*>(pd);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void LV_Step(
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
      Unit[i].Move[LV_BeforeG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
    DEval.update();
    for(unsigned int i=0;i<Grad.size();++i) Grad[i]=0.;
    GFunc(Coor,IM,IdxLst,ParamLst,DEval,Geo,Grad);
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[LV_AfterG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void LV_Step(
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
      Unit[i].Move[LV_BeforeG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
    DEval.update();
    for(unsigned int i=0;i<Grad.size();++i) Grad[i]=0.;
    GFunc(Coor,IM,IdxLst,ParamLst,DEval,Geo,Grad);
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[LV_AfterG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType>
  void SetAsLV(Propagator<DistEvalMethod,GeomType>& P) {
    P.GAlloc=LV_Allocate;
    P.GSync=LV_Synchronize;
    P.GSet.allocate(NumberSetLV);
    AssignCommonSet4Propagator(P.GSet);
    P.GSet[TemperatureInLV]=LV_SetTemperature;
    P.GSet[ViscosityInLV]=LV_SetViscosity;
    P.GSet[GaussianRNGPointerInLV]=LV_SetGaussianRNGPointer;
    P.HStepVV=LV_Step<DistEvalMethod,GeomType,varVector,varVector>;
    P.HStepVR=LV_Step<DistEvalMethod,GeomType,varVector,refVector>;
    P.HStepRV=LV_Step<DistEvalMethod,GeomType,refVector,varVector>;
    P.HStepRR=LV_Step<DistEvalMethod,GeomType,refVector,refVector>;
    P.FStepVV=LV_Step<DistEvalMethod,GeomType,varVector,varVector>;
    P.FStepVR=LV_Step<DistEvalMethod,GeomType,varVector,refVector>;
    P.FStepRV=LV_Step<DistEvalMethod,GeomType,refVector,varVector>;
    P.FStepRR=LV_Step<DistEvalMethod,GeomType,refVector,refVector>;
  }

}

#endif

