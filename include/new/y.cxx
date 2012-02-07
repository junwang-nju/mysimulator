
#include "dynamics/evolute.h"
#include "dynamics/output/energy/bind.h"
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

  allocate(S.Propagates[0],SysConstEVelVerlet,1);
  S.Propagates[0].MerIDRange[0].u[0]=0;
  S.Propagates[0].MerIDRange[0].u[1]=3;
  S.Propagates[0].buildGroupContent(S.Content());

  S.build();

  S.Propagates[0].Param[ModCEVVerletMass].u[0]=ArrayMass;

  allocate(GR);
  GR.init(23293);

  Dynamics<MicroCanonical,double,Array2D,
           DynOutputEnergy<FileOutput,double,Array1D<IDType>,Array1D<ParamType>,
                           FreeSpace,Array2D,SysContentWithEGV> >
  DynMC;
  DynMC.bind(S);

  COut.precision(12);
  copy(S.Content().X(),X);
  fillArray(GR,S.Content().Velocity());
  GenericEvaluate(S.Content(),S.Interactions);
  COut<<S.Content().EGData.Energy()<<Endl;

  DynMC.TimeStep=0.001;
  DynMC.NumSteps=10000;
  DynMC.StartTime=0.;
  DynMC.updateRunPeriod();
  fill(DynMC.Mass,1.);
  S.Propagates[0].update(CalcCEVVerletHTIM);
  copy(DynMC.Output.OS,COut);
  DynMC.Output.TimeBwOutput=0.002;
  DynMC.Output.NumStepsBwOutput=2;
  DynMC.Output.IsFirstOutput=true;
  DynMC.Output.setNowTime(DynMC.NowTime);

  evolute(DynMC,S);

  DynMC.unbind(S);

  return 0;
}

