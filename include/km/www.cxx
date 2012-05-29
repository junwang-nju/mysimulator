
#include "propagator/minimizer/line/tracking/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  System<double,FreeSpace> S;

  S.AllocateKind(2);
  for(unsigned int i=0;i<2;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(2);
  S.Location()[0][0]=0;       S.Location()[0][1]=0;
  S.Location()[1][0]=1.2;     S.Location()[1][1]=0;
  S.Velocity().Fill(0);

  Array2D<InteractionFuncName> IFN;
  IFN.Allocate(1,1);
  IFN[0][0]=Harmonic;
  S.AllocateInteraction(IFN,2);
  S.Interaction(0).Index(0)[0]=0;   S.Interaction(0).Index(0)[1]=1;
  Value<double>(S.Interaction(0).Parameter(0,HarmonicEqLength))=1.;
  Value<double>(S.Interaction(0).Parameter(0,HarmonicEqStrength))=100.;
  S.Interaction(0).ParameterBuild(0);

  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(1);
  S.InteractionGroup(0).WorkID(0)=0;

  S.UpdateB(0);

  Propagator<double,FreeSpace>* P=NULL;
  P=new PropagatorTrackingLineMinimizer<double,FreeSpace>;

  _SwapContent(S.Location(),S.Velocity());
  return 0;
}

