
#ifndef _Propagator_Langevin_VelVerlet_H_
#define _Propagator_Langevin_VelVerlet_H_

#include "propagator-particle-langevin-vverlet.h"
#include "param-list.h"
#include "interaction-4listset.h"
#include "propagator.h"
#include "monomer-type.h"

namespace std {

  void LV_AllocGbParam(FuncParamType& gbPrm){
    gbPrm.allocate(NumberParamLV);
    varVector<uint> offset(NumberParamLV),size(NumberParamLV);
    offset[BasicLV]=0;    size[BasicLV]=NumberBasicLV;
    offset[RandPointerLV]=NumberBasicLV;  size[RandPointerLV]=1U;
    gbPrm.BuildStructure(offset,size);
  }

  template <typename DistEvalObj, typename GeomType, uint bMode>
  void LV_Step(VectorBase<refVector<double> >& Coordinate,
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
    assert(n==Mass.size());
    for(uint i=0;i<n;++i)
      Mv[i].MvFunc[BeforeGLV](Coordinate[i],Velocity[i],Gradient[i],
                              Mv[i].runParam,gbPrm,cgbPrm);
    DEval.Update();
    for(uint i=0;i<n;++i) Gradient[i]=0.;
    G_ListSet(Coordinate,ILS,PList,DEval,Geo,Gradient);
    for(uint i=0;i<n;++i)
      Mv[i].MvFunc[AfterGLV](Coordinate[i],Velocity[i],Gradient[i],
                             Mv[i].runParam,gbPrm,cgbPrm);
  }

  void LV_SetTemperature(FuncParamType& gbPrm,
                         const double* data, const uint&) {
    gbPrm[BasicLV][TemperatureLV]=*data;
  }

  void LV_SetViscosity(FuncParamType& gbPrm, const double* data, const uint&) {
    gbPrm[BasicLV][ViscosityCoefLV]=*data;
  }

  void LV_SetGRNGPointer(FuncParamType& gbPrm,const double* data,const uint&){
    gbPrm[RandPointerLV][GaussianRNGPointerLV]=
        static_cast<double>(reinterpret_cast<long long>(data));
  }

  void LV_Synchronize(const VectorBase<refVector<double> >& IvMass,
                      const VectorBase<refVector<double> >&,
                      FuncParamType& gbPrm, FuncParamType& cgbPrm,
                      VectorBase<MonomerPropagator>& Mv) {
    gbPrm[BasicLV][TempeDeltaTLV]=gbPrm[BasicLV][TemperatureLV]*
                                  cgbPrm[BasicCommon][DeltaTime];
    uint n=IvMass.size();
    for(uint i=0;i<n;++i) Mv[i].Sync(IvMass[i],gbPrm,cgbPrm,Mv[i].runParam);
  }
  
  template <typename DistEvalObj, typename GeomType, uint bMode>
  void SetAsLV(Propagator<DistEvalObj,GeomType,bMode>& Pg,
               const VectorBase<uint>& MerType) {
    Pg.GbAlloc=LV_AllocGbParam;
    Pg.GbSetFunc.allocate(NumberSetLV);
    Pg.GbSetFunc[SetTemperatureLV]=LV_SetTemperature;
    Pg.GbSetFunc[SetViscosityLV]=LV_SetViscosity;
    Pg.GbSetFunc[SetGRNGPointerLV]=LV_SetGRNGPointer;
    Pg.Step=LV_Step;
    Pg.Sync=LV_Synchronize;
    uint n=MerType.size();
    Pg.UnitMove.allocate(n);
    uint mType;
    for(uint i=0;i<n;++i) {
      mType=MerType[i];
      if(mType==Particle)   SetAsPLV(Pg.UnitMove[i]);
      else myError("Unknown Monomer Types!");
    }
  }

}

#endif

