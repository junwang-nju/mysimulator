
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
  S.Velocity()[0][0]=1;       S.Velocity()[0][1]=0;
  S.Velocity()[1][0]=-1;      S.Velocity()[1][1]=0;

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

  Array<StepPropagatorName> SPN;
  SPN.Allocate(1);
  SPN[0]=MinimizerShiftLine;
  P->Allocate(SPN);

  *Pointer<double>(P->Parameter(BaseMin_Step))=0.1;

  P->Step(0)->AllocateRange(1);
  P->Step(0)->Range(0)[0]=0;
  P->Step(0)->Range(0)[1]=2;
  P->IntroduceSystem(S);

  Value<double>(P->Parameter(TrackingLineMin_MaxStep))=1000;
  Value<double>(P->Parameter(TrackingLineMin_SearchScale))=0.1;
  Value<double>(P->Parameter(TrackingLineMin_DecreaseFac))=1e-4;;
  Value<double>(P->Parameter(TrackingLineMin_CurvatureFac))=0.4;
  Value<double>(P->Parameter(TrackingLineMin_GradThreshold))=_RelDelta<double>();

  P->Evolute(S);

  P->DetachSystem();
  return 0;
}

