
#ifndef _Propagator_Langevin_VelVerlet_H_
#define _Propagator_Langevin_VelVerlet_H_

#include "propagator-particle-langevin-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"

namespace std {

  void LV_AllocGbParam(ParamPackType& gbPrm, const varVector<Property>& PSet){
    PropagatorParamAllocate(gbPrm,static_cast<uint>(NumberParamLV));
    PropagatorParamAllocate(gbPrm[BasicLV],static_cast<uint>(NumberBasicLV));
    PropagatorParamAllocate(gbPrm[RandPointerLV],1U);
  }

  template <typename DistEvalObj, typename GeomType>
  void LV_Step(varVector<Property>& PropSet, const ParamList& PList,
               varVector<IDList<DistEvalObj,GeomType> >& IDLS,
               varVector<MonomerPropagator>& Mv, ParamPackType& gbPrm,
               ParamPackType& cgbPrm,
               DistEvalObj& DEval, const GeomType& Geo) {
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) Mv[i].MvFunc[BeforeGLV](PropSet[i],Mv[i].runParam,
                                                  gbPrm,cgbPrm);
    DEval.Update();
    for(uint i=0;i<n;++i) PropSet[i].Gradient=0.;
    G_ListSet(PropSet,PList,IDLS,DEval,Geo);
    for(uint i=0;i<n;++i) Mv[i].MvFunc[AfterGLV](PropSet[i],Mv[i].runParam,
                                                 gbPrm,cgbPrm);
  }

  void LV_SetTemperature(ParamPackType& gbPrm,
                         const double* data, const uint&) {
    gbPrm[BasicLV][TemperatureLV]=*data;
  }

  void LV_SetViscosity(ParamPackType& gbPrm, const double* data, const uint&) {
    gbPrm[BasicLV]
  }
}

#endif

