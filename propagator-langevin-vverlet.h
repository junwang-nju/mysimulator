
#ifndef _Propagator_Langevin_VelVerlet_H_
#define _Propagator_Langevin_VelVerlet_H_

#include "propagator-particle-langevin-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"

namespace std {

  void LV_AllocGbParam(ParamPackType& gbPrm, const VectorBase<Property>& PSet){
    gbPrm.allocate(NumberParamLV);
    gbPrm[BasicLV].allocate(NumberBasicLV);
    gbPrm[RandPointerLV].allocate(1U);
  }

  template <typename DistEvalObj, typename GeomType>
  void LV_Step(VectorBase<Property>& PropSet, const ParamList& PList,
               VectorBase<IDList<DistEvalObj,GeomType> >& IDLS,
               VectorBase<MonomerPropagator>& Mv, ParamPackType& gbPrm,
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
    gbPrm[BasicLV][ViscosityCoefLV]=*data;
  }

  void LV_SetGRNGPointer(ParamPackType& gbPrm,const double* data,const uint&){
    gbPrm[RandPointerLV][GaussianRNGPointerLV]=
        static_cast<double>(reinterpret_cast<long long>(data));
  }

  void LV_Synchronize(const VectorBase<Property>& PropSet,
                      VectorBase<MonomerPropagator>& Mv, ParamPackType& gbPrm,
                      ParamPackType& cgbPrm) {
    gbPrm[BasicLV][TempeDeltaTLV]=gbPrm[BasicLV][TemperatureLV]*
                                  cgbPrm[BasicCommon][DeltaTime];
    uint n=PropSet.size();
    for(uint i=0;i<n;++i) Mv[i].Sync(PropSet[i],gbPrm,cgbPrm,Mv[i].runParam);
  }
  
  template <typename DistEvalObj, typename GeomType>
  void SetAsLV(const VectorBase<Property>& PropSet,
               Propagator<DistEvalObj,GeomType>& Pg) {
    Pg.GbAlloc=LV_AllocGbParam;
    Pg.GbSetFunc.allocate(NumberSetLV);
    Pg.GbSetFunc[SetTemperatureLV]=LV_SetTemperature;
    Pg.GbSetFunc[SetViscosityLV]=LV_SetViscosity;
    Pg.GbSetFunc[SetGRNGPointerLV]=LV_SetGRNGPointer;
    Pg.Step=LV_Step;
    Pg.Sync=LV_Synchronize;
    uint n=PropSet.size();
    Pg.UnitMove.allocate(n);
    uint mType;
    for(uint i=0;i<n;++i) {
      mType=PropSet[i].Info[MonomerTypeID];
      if(mType==Particle)   SetAsPLV(Pg.UnitMove[i]);
      else if(mType>NumberTypes)  myError("Unknown Monomer Types!");
    }
  }

}

#endif

