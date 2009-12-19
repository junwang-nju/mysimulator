
#ifndef _Propagator_ConstE_VelVerlet_H_
#define _Propagator_ConstE_VelVerlet_H_

#include "propagator-particle-conste-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"
#include "monomer-type.h"

namespace std {

  void EV_AllocGbParam(FuncParamType& gbPrm) {
    gbPrm.allocate(NumberParamEV);
  }
  
  template <typename DistEvalObj, typename GeomType>
  void EV_Step(VectorBase<refVector<double> >& Coordinate,
               VectorBase<refVector<double> >& Velocity,
               VectorBase<refVector<double> >& Gradient,
               const VectorBase<refVector<double> >&,
               const ParamList& PList,
               VectorBase<IDList<DistEvalObj,GeomType> >& IDLS,
               VectorBase<MonomerPropagator>& Mv, FuncParamType& gbPrm,
               FuncParamType& cgbPrm,
               DistEvalObj& DEval, const GeomType& Geo) {
    uint n=Coordinate.size();
    assert(n==Velocity.size());
    assert(n==Gradient.size());
    for(uint i=0;i<n;++i)
      Mv[i].MvFunc[BeforeGEV](Coordinate[i],Velocity[i],Gradient[i],
                              Mv[i].runParam,gbPrm,cgbPrm);
    DEval.Update();
    for(uint i=0;i<n;++i) Gradient[i]=0.;
    G_ListSet(IDLS,PList,DEval,Geo);
    for(uint i=0;i<n;++i)
      Mv[i].MvFunc[AfterGEV](Coordinate[i],Velocity[i],Gradient[i],
                             Mv[i].runParam,gbPrm,cgbPrm);
  }

  void EV_Synchronize(const VectorBase<refVector<double> >& IvMass,
                      const VectorBase<refVector<double> >&,
                      FuncParamType& gbPrm,FuncParamType& cgbPrm,
                      VectorBase<MonomerPropagator>& Mv){
    uint n=IvMass.size();
    for(uint i=0;i<n;++i) Mv[i].Sync(IvMass[i],gbPrm,cgbPrm,Mv[i].runParam);
  }

  template <typename DistEvalObj, typename GeomType>
  void SetAsEV(Propagator<DistEvalObj,GeomType>& Pg,
               const VectorBase<uint>& MerType) {
    Pg.GbAlloc=EV_AllocGbParam;
    Pg.GbSetFunc.allocate(NumberSetEV);
    Pg.Step=EV_Step;
    Pg.Sync=EV_Synchronize;
    uint n=MerType.size();
    Pg.UnitMove.allocate(n);
    uint mType;
    for(uint i=0;i<n;++i) {
      mType=MerType[i];
      if(mType==Particle) SetAsPEV(Pg.UnitMove[i]);
      else myError("Unknown Monomer Types!");
    }
  }
  
}

#endif
