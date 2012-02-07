
#include "dynamics/evolute.h"
#include "dynamics/bind.h"
#include "dynamics/output/energy/link.h"
#include "io/output/file/copy.h"

#include "system/content/with-egv/allocate.h"
#include "system/content/with-egv/refer.h"
#include "system/interaction/use.h"
#include "system/propagate/allocate.h"
#include "system/evaluate/regular.h"
#include "interaction/func/allocate.h"
#include "boundary/free/allocate.h"
#include "random/box-muller/allocate.h"
#include "random/mt/allocate.h"
#include "array/2d/allocate.h"
#include "array/2d/copy.h"
#include "array/2d/fill.h"
#include "array/2d/refer.h"
#include "array/2d/scale.h"
#include "array/2d/shift.h"
#include "array/2d/norm.h"
#include "array/2d/dot.h"
#include "array/2d/inverse.h"
#include "array/2d/square-root.h"
#include "array/2d/compare.h"
using namespace mysimulator;

int main() {

  typedef Array1D<int>  IDType;
  typedef Array1D<Unique64Bit>  ParamType;

  Array2D<double> X;
  Array1D<IDType>     ID;
  Array1D<ParamType>  Param;
  System<double,Array1D<IDType>,Array1D<ParamType>,FreeSpace,Array2D,
         SysContentWithEGV>   S;
  BoxMuller<MersenneTwister<dSFMT,19937> > GR;

  allocate(X,4U,2U);
  fill(X,0.);
  X[1][0]=1.2;
  X[2][0]=1.3;    X[2][1]=1.5;
  X[3][0]=0.8;    X[3][1]=2.2;

  allocate(ID,6);
  for(unsigned int i=0;i<6;++i) allocate(ID[i],2);
  ID[0][0]=0;       ID[0][1]=1;
  ID[1][0]=1;       ID[1][1]=2;
  ID[2][0]=2;       ID[2][1]=3;
  ID[3][0]=0;       ID[3][1]=2;
  ID[4][0]=0;       ID[4][1]=3;
  ID[5][0]=1;       ID[5][1]=3;

  allocate(Param,6);
  for(unsigned int i=0;i<3;++i) {
    allocate(Param[i],HarmonicNumberParameters);
    Param[i][HarmonicEqLength].d=1.;
    Param[i][HarmonicEqStrength].d=100.;
    BuildParameterHarmonic<double>(Param[i]);
  }
  for(unsigned int i=3;i<6;++i) {
    allocate(Param[i],LJ612NumberParameters);
    Param[i][LJ612EqRadius].d=1.;
    Param[i][LJ612EqEnergyDepth].d=1.;
    BuildParameterLJ612<double>(Param[i]);
  }

  allocate(S.Content);
  allocate(S.Interactions,1);
  allocate(S.Propagates,1);

  allocate(S.Content(),X);

  useParam(S.Interactions[0],Param);
  useID(S.Interactions[0],ID);
  allocate(S.Interactions[0].Geom);
  allocate(S.Interactions[0].Geom(),2);
  allocate(S.Interactions[0].EGData);
  allocate(S.Interactions[0].EGData(),X);
  allocate(S.Interactions[0].Func,6);
  for(unsigned int i=0;i<3;++i) allocate(S.Interactions[0].Func[i],Harmonic,2);
  for(unsigned int i=3;i<6;++i) allocate(S.Interactions[0].Func[i],LJ612,2);
  SetWorkFunc(S.Interactions[0],ArrayInteraction);

  allocate(S.Propagates[0],SysLangevinVelVerlet,1);
  S.Propagates[0].MerIDRange[0].u[0]=0;
  S.Propagates[0].MerIDRange[0].u[1]=3;
  S.Propagates[0].buildGroupContent(S.Content());

  S.build();

  S.Propagates[0].Param[ModLgVVerletMass].u[0]=ArrayMass;
  S.Propagates[0].Param[ModLgVVerletFriction].u[0]=ArrayFriction;

  /*
  allocate(GR);
  GR.init(23293);
  S.Propagates[0].Param[DatLgVVerletGaussRNG].ptr[0]=reinterpret_cast<void*>(&GR);
  */

  Dynamics<LangevinVVerlet,double,Array2D,
           DynamicsOutputEnergy<FileOutput,double,Array1D<IDType>,
                                Array1D<ParamType>,FreeSpace,Array2D,
                                SysContentWithEGV> >
  DynL;

  allocate(DynL.Output.BaseData);
  bind(DynL,S);

  COut.precision(12);
  copy(S.Content().X(),X);
  allocate(DynL.CanonicalLangevinBaseData.rng);
  DynL.CanonicalLangevinBaseData.rng.init(23293);
  fillArray(DynL.CanonicalLangevinBaseData.rng,S.Content().Velocity());
  GenericEvaluate(S.Content(),S.Interactions);

  DynL.BaseData.TimeStep=0.001;
  DynL.CanonicalData.Temperature=0.5;
  DynL.BaseData.NumSteps=10000;
  DynL.BaseData.StartTime=0.;
  DynL.updateRunPeriod();
  fill(DynL.BaseData.Mass,1.);
  fill(DynL.CanonicalLangevinBaseData.Friction,10.);
  S.Propagates[0].update(CalcLgVVerletNegHTIM);
  S.Propagates[0].update(CalcLgVVerletFac);
  S.Propagates[0].update(CalcLgVVerletRandSize);
  allocate(DynL.Output.OS);
  copy(DynL.Output.OS(),COut);
  DynL.Output.BaseData().TimeBwOutput=0.002;
  DynL.Output.BaseData().NumStepsBwOutput=2;
  DynL.Output.IsFirstOutput=true;
  DynL.Output.IsTerminated=true;
  DynL.Output.BaseData().setNowTime(DynL.BaseData.NowTime);

  evolute(DynL,S);

  unbind(DynL,S);

  return 0;
}

