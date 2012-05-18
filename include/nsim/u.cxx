
#include "minimizer/interface.h"
#include "boundary/free/interface.h"
#include "system/interaction/use.h"
#include "system/evaluate/regular.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  Array2D<double> X;
  X.Allocate(4,2);
  Fill(X,0.);
  X[1][0]=1.2;
  X[2][0]=2.3;    X[2][1]=1.5;
  X[3][0]=-1.5;   X[3][1]=0.7;

  Array2D<unsigned int> ID;
  Array2D<Unique64Bit>  Param;
  Array1D<unsigned int> sz;

  ID.Allocate(6,2);
  for(unsigned int i=0,n=0;i<4;++i)
  for(unsigned int j=i+1;j<4;++j,++n) {
    ID[n][0]=i;   ID[n][1]=j;
  }
  sz.Allocate(6);
  for(unsigned int i=0;i<6;++i) sz[i]=HarmonicNumberParameters;
  Param.Allocate(sz);
  Param[0][HarmonicEqLength].d=0.8;
  Param[0][HarmonicEqStrength].d=100.;
  Param[1][HarmonicEqLength].d=0.5;
  Param[1][HarmonicEqStrength].d=100.;
  Param[2][HarmonicEqLength].d=0.9;
  Param[2][HarmonicEqStrength].d=10.;
  Param[3][HarmonicEqLength].d=1.2;
  Param[3][HarmonicEqStrength].d=20.;
  Param[4][HarmonicEqLength].d=0.7;
  Param[4][HarmonicEqStrength].d=200.;
  Param[5][HarmonicEqLength].d=1.2;
  Param[5][HarmonicEqStrength].d=50.;
  for(unsigned int i=0;i<6;++i) BuildParameterHarmonic<double>(Param[i]);

  System<double,Array2D<unsigned int>,Array2D<Unique64Bit>,FreeSpace,
         Array1D<InteractionBuffer<double> >,SystemContentWithE> S;
  S.Content.X.Refer(X);
  S.Content.EGData.Allocate(X);
  S.Interactions.Allocate(1);
  UseParam(S.Interactions[0],Param);
  UseID(S.Interactions[0],ID);
  S.Interactions[0].Geom.Allocate(2);
  S.Interactions[0].Func.Allocate(6);
  for(unsigned int i=0;i<6;++i)
    S.Interactions[0].Func[i].Allocate(Harmonic);
  S.Interactions[0].Buffer.Allocate(6);
  for(unsigned int i=0;i<6;++i)
    S.Interactions[0].Buffer[i].Allocate(Harmonic,2);
  S.Interactions[0].EGData.Allocate(X);
  S.Propagators.Allocate(1);
  S.Propagators[0].Allocate(SystemToBeDetermined,1);
  S.Propagators[0].IDRange[0].uv[0]=0;
  S.Propagators[0].IDRange[0].uv[1]=4;
  S.Propagators[0]._Build(S.Content);
  S._Build();

  System<double,Array2D<unsigned int>,Array2D<Unique64Bit>,FreeSpace,
         Array1D<InteractionBuffer<double> >,SystemContentWithE> S1;
  S1.Refer(S);
  Clear(S1);

  cout.precision(16);
  Evaluate(S.Content,S.Interactions);
  cout<<S.Content.EGData.Energy[0]<<endl;

  Minimizer<SteepestDescent,TrackingMethod,double,Array2D<unsigned int>,
            Array2D<Unique64Bit>,
            FreeSpace,Array1D<InteractionBuffer<double> >,SystemContentWithE,
            StrongWolfe>  SM;
  SM.Load(S);
  SM.Go();
  cout<<S.Content.EGData.Energy[0]<<endl;
  cout<<SM.GCalcCount<<endl;
  cout<<SM.LineSearchCount<<endl;

  Clear(SM);
  Clear(S);

  return 0;
}

