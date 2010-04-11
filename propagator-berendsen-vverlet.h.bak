
#ifndef _Propagator_Berendsen_VelVerlet_H_
#define _Propagator_Berendsen_VelVerlet_H_

#include "propagator-particle-berendsen-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"
#include "monomer-type.h"
#include <cmath>

namespace std {

  void BV_AllocGbParam(FuncParamType& gbPrm){
    gbPrm.allocate(NumberParamBV);
    varVector<uint> offset(NumberParamBV),size(NumberParamBV);
    offset[BasicBV]=0;    size[BasicBV]=NumberBasicBV;
    gbPrm.BuildStructure(offset,size);
  }

  template <typename DistEvalObj, typename GeomType, uint bMode>
  void BV_Step(VectorBase<refVector<double> >& Coordinate,
               VectorBase<refVector<double> >& Velocity,
               VectorBase<refVector<double> >& Gradient,
               const VectorBase<refVector<double> >& Mass,
               const ParamList& PList,
               VectorBase<InteractionList<DistEvalObj,GeomType,bMode> >& ILS,
               VectorBase<MonomerPropagator>& Mv, FuncParamType& gbPrm,
               FuncParamType& cgbPrm,
               DistEvalObj& DEval, const GeomType& Geo) {
    uint n=Coordinate.size();
    assert(n==Velocity.size());
    assert(n==Gradient.size());
    for(uint i=0;i<n;++i)
      Mv[i].MvFunc[BeforeGBV](Coordinate[i],Velocity[i],Gradient[i],
                              Mv[i].runParam,gbPrm,cgbPrm);
    DEval.Update();
    for(uint i=0;i<n;++i) Gradient[i]=0.;
    G_ListSet(Coordinate,ILS,PList,DEval,Geo,Gradient);
    for(uint i=0;i<n;++i)
      Mv[i].MvFunc[AfterGBV](Coordinate[i],Velocity[i],Gradient[i],
                             Mv[i].runParam,gbPrm,cgbPrm);
    double fac=0.;
    for(uint i=0;i<n;++i) fac+=normSQ(Velocity[i])*Mass[i][0];
    fac=gbPrm[BasicBV][TemperatureBV]*gbPrm[BasicBV][DegreeFreedomBV]/fac;
    gbPrm[BasicBV][ScaleFacBV]=
        sqrt(1.+gbPrm[BasicBV][DeltaTIvRelaxTBV]*(fac-1.));
    for(uint i=0;i<n;++i)
      Mv[i].MvFunc[PostProcessBV](Coordinate[i],Velocity[i],Gradient[i],
                                  Mv[i].runParam,gbPrm,cgbPrm);
  }

  void BV_SetTemperature(FuncParamType& gbPrm, const double* data,const uint&){
    gbPrm[BasicBV][TemperatureBV]=*data;
  }

  void BV_SetRelaxTime(FuncParamType& gbPrm, const double* data,const uint&) {
    gbPrm[BasicBV][RelaxTimeBV]=*data;
  }

  void BV_Synchronize(const VectorBase<refVector<double> >& IvMass,
                      const VectorBase<refVector<double> >& DMask,
                      FuncParamType& gbPrm, FuncParamType& cgbPrm,
                      VectorBase<MonomerPropagator>& Mv) {
    double dof=0.;
    uint n=IvMass.size();
    for(uint i=0;i<n;++i) dof+=sumABS(DMask[i]);
    gbPrm[BasicBV][DegreeFreedomBV]=dof;
    gbPrm[BasicBV][DeltaTIvRelaxTBV]=cgbPrm[BasicCommon][DeltaTime]/
                                     gbPrm[BasicBV][RelaxTimeBV];
    for(uint i=0;i<n;++i)
      Mv[i].Sync(IvMass[i],gbPrm,cgbPrm,Mv[i].runParam);
  }

  template <typename DistEvalObj, typename GeomType, uint bMode>
  void SetAsBV(Propagator<DistEvalObj,GeomType,bMode>& Pg,
               const VectorBase<uint>& MerType) {
    Pg.GbAlloc=BV_AllocGbParam;
    Pg.GbSetFunc.allocate(NumberSetBV);
    Pg.GbSetFunc[SetTemperatureBV]=BV_SetTemperature;
    Pg.GbSetFunc[SetRelaxTimeBV]=BV_SetRelaxTime;
    Pg.Step=BV_Step;
    Pg.Sync=BV_Synchronize;
    uint n=MerType.size();
    Pg.UnitMove.allocate(n);
    uint mType;
    for(uint i=0;i<n;++i) {
      mType=MerType[i];
      if(mType==Particle) SetAsPBV(Pg.UnitMove[i]);
      else myError("Unknown Monomer Types!");
    }
  }

}

#endif

