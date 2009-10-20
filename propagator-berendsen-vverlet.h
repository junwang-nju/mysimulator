
#ifndef _Propagator_Berendsen_VelVerlet_H_
#define _Propagator_Berendsen_VelVerlet_H_

#include "propagator-particle-berendsen-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"

namespace std {

  void BV_AllocGbParam(ParamPackType& gbPrm, const varVector<Property>& PSet){
    PropagatorParamAllocate(gbPrm,static_cast<uint>(NumberParamBV));
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

}

#endif

