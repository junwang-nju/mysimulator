
#ifndef _Propagator_ConstantE_VelocityVerlet_H_
#define _Propagator_ConstantE_VelocityVerlet_H_

#include "propagator-parameter-element.h"
#include "propagator-parameter-name-conste-vverlet.h"
#include "propagator.h"

namespace std {

  void EV_Allocate(varVector<PropagatorDataElementType>& GPrm) {
    GPrm.allocate(NumberParamEV);
  }

  void EV_Synchronize(
      const VectorBase<refVector<double> >& IvMass,
      const VectorBase<refVector<double> >&,
      VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<MonomerPropagator>& Unit) {
    for(unsigned int i=0;i<IvMass.size();++i)
      Unit[i].synchronize(IvMass[i],GParam);
  }

  template <template <template <typename> class> class DistEvalMethod,
            template <template <typename> class> class GeomType,
            template <typename> class VecTypeD,
            template <typename> class VecTypeG>
  void EV_Step(
      const VectorBase<InteractionMethod<DistEvalMethod,GeomType> >& IM,
      VectorBase<refVector<double> >& Coor,
      VectorBase<refVector<double> >& Vel,
      VectorBase<refVector<double> >& Grad,
      const VectorBase<refVector<unsigned int> >& IdxLst,
      const VectorBase<refVector<double> >& ParamLst,
      VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<MonomerPropagator>& Unit,
      DistEvalMethod<VecTypeD>& DEval, const GeomType<VecTypeG>& Geo) {
    assert(Coor.size()==Vel.size());
    assert(Coor.size()==Grad.size());
    assert(Coor.size()==Unit.size());
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[EV_BeforeG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
    DEval.update();
    for(unsigned int i=0;i<Grad.size();++i) Grad[i]=0.;
    GFunc(Coor,IM,IdxLst,ParamLst,DEval,Geo,Grad);
    for(unsigned int i=0;i<Unit.size();++i)
      Unit[i].Move[EV_AfterG](Coor[i],Vel[i],Grad[i],GParam,Unit[i].Param);
  }

}

#endif

