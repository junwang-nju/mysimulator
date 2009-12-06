
#ifndef _Propagator_ConstE_VelVerlet_H_
#define _Propagator_ConstE_VelVerlet_H_

#include "propagator-particle-conste-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"

namespace std {

  void EV_AllocGbParam(ParamPackType& gbPrm,const VectorBase<Property>& PSet) {
    gbPrm.allocate(NumberParamEV);
  }
  
  template <typename DistEvalObj, typename GeomType>
  void EV_Step(VectorBase<Property>& PropSet, const ParamList& PList,
               VectorBase<IDList<DistEvalObj,GeomType> >& IDLS,
               VectorBase<MonomerPropagator>& Mv, ParamPackType& gbPrm,
               ParamPackType& cgbPrm,
               DistEvalObj& DEval, const GeomType& Geo) {
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) Mv[i].MvFunc[BeforeGEV](PropSet[i],Mv[i].runParam,
                                                  gbPrm,cgbPrm);
    DEval.Update();
    for(uint i=0;i<n;++i) PropSet[i].Gradient=0.;
    G_ListSet(PropSet,PList,IDLS,DEval,Geo);
    for(uint i=0;i<n;++i) Mv[i].MvFunc[AfterGEV](PropSet[i],Mv[i].runParam,
                                                 gbPrm,cgbPrm);
  }

  void EV_Synchronize(const VectorBase<Property>& PropSet,
                      VectorBase<MonomerPropagator>& Mv,ParamPackType& gbPrm,
                      ParamPackType& cgbPrm){
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) Mv[i].Sync(PropSet[i],gbPrm,cgbPrm,Mv[i].runParam);
  }

  template <typename DistEvalObj, typename GeomType>
  void SetAsEV(const VectorBase<Property>& PropSet,
               Propagator<DistEvalObj,GeomType>& Pg) {
    Pg.GbAlloc=EV_AllocGbParam;
    Pg.GbSetFunc.allocate(NumberSetEV);
    Pg.Step=EV_Step;
    Pg.Sync=EV_Synchronize;
    uint n=PropSet.size();
    Pg.UnitMove.allocate(n);
    uint mType;
    for(uint i=0;i<n;++i) {
      mType=PropSet[i].Info[MonomerTypeID];
      if(mType==Particle) SetAsPEV(Pg.UnitMove[i]);
      else if(mType>NumberTypes)  myError("Unknown Monomer Types!");
    }
  }
  
}

#endif
