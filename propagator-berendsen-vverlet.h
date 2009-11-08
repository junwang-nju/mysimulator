
#ifndef _Propagator_Berendsen_VelVerlet_H_
#define _Propagator_Berendsen_VelVerlet_H_

#include "propagator-particle-berendsen-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"

namespace std {

  void BV_AllocGbParam(ParamPackType& gbPrm, const varVector<Property>& PSet){
    PropagatorParamAllocate(gbPrm,static_cast<uint>(NumberParamBV));
    PropagatorParamAllocate(gbPrm[BasicBV],static_cast<uint>(NumberBasicBV));
  }

  template <typename DistEvalObj, typename GeomType>
  void BV_Step(varVector<Property>& PropSet, const ParamList& PList,
               varVector<IDList<DistEvalObj,GeomType> >& IDLS,
               varVector<MonomerPropagator>& Mv, ParamPackType& gbPrm,
               ParamPackType& cgbPrm,
               DistEvalObj& DEval, const GeomType& Geo) {
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) Mv[i].MvFunc[BeforeGBV](PropSet[i],Mv[i].runParam,
                                                  gbPrm,cgbPrm);
    DEval.Update();
    for(uint i=0;i<n;++i) PropSet[i].Gradient=0.;
    G_ListSet(PropSet,PList,IDLS,DEval,Geo);
    for(uint i=0;i<n;++i) Mv[i].MvFunc[AfterGBV](PropSet[i],Mv[i].runParam,
                                                 gbPrm,cgbPrm);
    double fac=0.;
    for(uint i=0;i<n;++i) fac+=normSQ(PropSet[i].Velocity)*PropSet[i].Mass[0];
    fac=gbPrm[BasicBV][TemperatureBV]*gbPrm[BasicBV][DegreeFreedomBV]/fac;
    gbPrm[BasicBV][ScaleFacBV]=
        sqrt(1.+gbPrm[BasicBV][DeltaTIvRelaxTBV]*(fac-1.));
    for(uint i=0;i<n;++i) Mv[i].MvFunc[PostProcessBV](PropSet[i],
                                                      Mv[i].runParam,
                                                      gbPrm,cgbPrm);
  }

  void BV_SetTemperature(ParamPackType& gbPrm, const double* data,const uint&){
    gbPrm[BasicBV][TemperatureBV]=*data;
  }

  void BV_SetRelaxTime(ParamPackType& gbPrm, const double* data,const uint&) {
    gbPrm[BasicBV][RelaxTimeBV]=*data;
  }

  void BV_Synchronize(const varVector<Property>& PropSet,
                      varVector<MonomerPropagator>& Mv, ParamPackType& gbPrm,
                      ParamPackType& cgbPrm) {
    double dof=0.;
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) dof+=sumABS(PropSet[i].dMask);
    gbPrm[BasicBV][DegreeFreedomBV]=dof;
    gbPrm[BasicBV][DeltaTIvRelaxTBV]=cgbPrm[BasicCommon][DeltaTime]/
                                     gbPrm[BasicBV][RelaxTimeBV];
    for(uint i=0;i<n;++i) Mv[i].Sync(PropSet[i],gbPrm,cgbPrm,Mv[i].runParam);
  }

  template <typename DistEvalObj, typename GeomType>
  void SetAsBV(const varVector<Property>& PropSet,
               Propagator<DistEvalObj,GeomType>& Pg) {
    Pg.GbAlloc=BV_AllocGbParam;
    PropagatorParamAllocate(Pg.GbSetFunc,static_cast<uint>(NumberSetBV));
    Pg.GbSetFunc[SetTemperatureBV]=BV_SetTemperature;
    Pg.GbSetFunc[SetRelaxTimeBV]=BV_SetRelaxTime;
    Pg.Step=BV_Step;
    Pg.Sync=BV_Synchronize;
    uint n=PropSet.size();
    PropagatorParamAllocate(Pg.UnitMove,n);
    uint mType;
    for(uint i=0;i<n;++i) {
      mType=PropSet[i].MonomerType;
      if(mType==Particle) SetAsPBV(Pg.UnitMove[i]);
      else if(mType>NumberTypes)  myError("Unknown Monomer Types!");
    }
  }

}

#endif

