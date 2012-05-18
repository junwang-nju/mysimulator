
#include "system/interface.h"
#include "boundary/free/interface.h"
#include "system/interaction/use.h"
#include "random/box-muller/interface.h"
#include "random/mt/standard/interface.h"
#include "system/evaluate/regular.h"
#include "array/2d/io.h"

using namespace mysimulator;

void NWrite(System<double,Array2D<unsigned int>,Array2D<Unique64Bit>,FreeSpace,
                   Array1D<InteractionBuffer<double> >,SystemContentWithEGV>& S,
            Dynamics<MicroCanonicalVelVerlet,double,
                     BoxMuller<MersenneTwister<StandardMT> > >& Dyn) {
  Write(Dyn.NowTime,"\t");
  EvaluateEnergy(S.Content,S.Interactions);
  Write(S.Content.EGData.Energy[0],"\t");
  S.Propagators[0]._Update(VelVerletConstECalcKE);
  Write(S.Propagators[0].Param[VelVerletConstEValKineticEnergy].d,"\n");
}

int main() {
  Array2D<double> X;
  X.Allocate(4,2);
  Fill(X,0.);
  X[1][0]=1.2;
  X[2][0]=1.3;    X[2][1]=1.5;
  X[3][0]=0.8;    X[3][1]=2.2;

  Array2D<unsigned int> ID;
  ID.Allocate(6,2);
  ID[0][0]=0;     ID[0][1]=1;
  ID[1][0]=1;     ID[1][1]=2;
  ID[2][0]=2;     ID[2][1]=3;
  ID[3][0]=0;     ID[3][1]=2;
  ID[4][0]=0;     ID[4][1]=3;
  ID[5][0]=1;     ID[5][1]=3;

  Array1D<unsigned int> sz;
  Array2D<Unique64Bit> Param;
  sz.Allocate(6);
  for(unsigned int i=0;i<3;++i) sz[i]=HarmonicNumberParameters;
  for(unsigned int i=3;i<6;++i) sz[i]=LJ612NumberParameters;
  Param.Allocate(sz);
  for(unsigned int i=0;i<3;++i) {
    Param[i][HarmonicEqLength].d=1.;
    Param[i][HarmonicEqStrength].d=100.;
    BuildParameterHarmonic<double>(Param[i]);
  }
  for(unsigned int i=3;i<6;++i) {
    Param[i][LJ612EqRadius].d=1.;
    Param[i][LJ612EqEnergyDepth].d=0.;
    BuildParameterLJ612<double>(Param[i]);
  }

  System<double,Array2D<unsigned int>,Array2D<Unique64Bit>,FreeSpace,
         Array1D<InteractionBuffer<double> >,SystemContentWithEGV> S;

  S.Content.Allocate(X);

  S.Interactions.Allocate(1);
  UseParam(S.Interactions[0],Param);
  UseID(S.Interactions[0],ID);
  S.Interactions[0].Geom.Allocate(2);
  S.Interactions[0].EGData.Allocate(X);
  S.Interactions[0].Func.Allocate(6);
  for(unsigned int i=0;i<3;++i) S.Interactions[0].Func[i].Allocate(Harmonic);
  for(unsigned int i=3;i<6;++i) S.Interactions[0].Func[i].Allocate(LJ612);
  S.Interactions[0].Buffer.Allocate(6);
  for(unsigned int i=0;i<3;++i)
    S.Interactions[0].Buffer[i].Allocate(Harmonic,2);
  for(unsigned int i=3;i<6;++i)
    S.Interactions[0].Buffer[i].Allocate(LJ612,2);

  S.Propagators.Allocate(1);
  S.Propagators[0].Allocate(SystemConstEVelVerlet,1);
  S.Propagators[0].IDRange[0].uv[0]=0;
  S.Propagators[0].IDRange[0].uv[1]=4;
  S.Propagators[0]._Build(S.Content);

  S._Build();

  S.Propagators[0].Param[VelVerletConstEModMass].u=ArrayMass;

  Dynamics<MicroCanonicalVelVerlet,double,
           BoxMuller<MersenneTwister<StandardMT> > > Dyn;
  Dyn.TimeStep=0.001;
  Dyn.NumSteps=10000;
  Dyn.StartTime=0.;
  Dyn.UpdateRunPeriod();
  Dyn.NumStepsBwOutput=2;
  Dyn.UpdateTimeBwOutput();
  Dyn.IsFirstOutput=true;
  Dyn.IsTerminated=true;

  Dyn.WriteFunc.ptr=reinterpret_cast<void*>(NWrite);
  Dyn.Bind(S);

  Copy(S.Content.X,X);
  EvaluateGradient(S.Content,S.Interactions);
  Fill(S.Content.Velocity,0.);
  Fill(Dyn.AMass,1.);
  S.Propagators[0]._Update(VelVerletConstECalcHTIM);
  S.Propagators[0]._Update(VelVerletConstECalcKE);

  S.Evolute(Dyn);

  Dyn.UnBind(S);

  return 0;
}

