
#ifndef _Propagator_ConstE_VelVerlet_H_
#define _Propagator_ConstE_VelVerlet_H_

#include "propagator-particle-conste-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"

namespace std {

  void EV_AllocGbParam(ParamPackType& gbPrm,const varVector<Property>& PSet) {
    PropagatorParamAllocate(gbPrm,static_cast<uint>(NumberParamEV));
  }
  
  template <typename DistEvalObj, typename GeomType>
  void EV_Step(varVector<Property>& PropSet, const ParamList& PList,
               varVector<IDList<DistEvalObj,GeomType> >& IDLS,
               varVector<MonomerPropagator>& Mv, ParamPackType& gbPrm,
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

  void EV_Synchronize(const varVector<Property>& PropSet,
                      varVector<MonomerPropagator>& Mv,ParamPackType& gbPrm,
                      ParamPackType& cgbPrm){
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) Mv[i].Sync(PropSet[i],Mv[i].runParam,gbPrm,cgbPrm);
  }

  template <typename DistEvalObj, typename GeomType>
  void SetAsEV(const varVector<Property>& PropSet,
               Propagator<DistEvalObj,GeomType>& Pg) {
    Pg.GbAlloc=EV_AllocGbParam;
    PropagatorParamAllocate(Pg.GbSetFunc,static_cast<uint>(NumberSetEV));
    Pg.Step=EV_Step;
    Pg.Sync=EV_Synchronize;
    uint n=PropSet.size();
    PropagatorParamAllocate(Pg.UnitMove,n);
    uint mType;
    for(uint i=0;i<n;++i) {
      mType=PropSet[i].MonomerType;
      if(mType==Particle) SetAsPEV(Pg.UnitMove[i]);
      else if(mType>NumberTypes)  myError("Unknown Monomer Types!");
    }
  }
  
}

#endif
