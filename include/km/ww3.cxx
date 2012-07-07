
#include "propagator/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  System<double,FreeSpace> S;

  S.AllocateKind(4);
  for(unsigned int i=0;i<4;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(2);
  S.Location()[0][0]=0;       S.Location()[0][1]=0;
  S.Location()[1][0]=1.2;     S.Location()[1][1]=0;
  S.Location()[2][0]=1.3;     S.Location()[1][1]=1.5;
  S.Location()[3][0]=0.8;     S.Location()[1][1]=2.2;
  S.Velocity().Fill(0);

  Array2D<InteractionFuncName> IFN;
  ArrayNumeric<unsigned int> sz;
  sz.Allocate(2);
  sz.Fill(3U);
  IFN.Allocate(sz);
  for(unsigned int j=0;j<3;++j) IFN[0][j]=Harmonic;
  for(unsigned int j=0;j<3;++j) IFN[1][j]=LJ612;
  S.AllocateInteraction(IFN,2);
  S.Interaction(0).Index(0)[0]=0;   S.Interaction(0).Index(0)[1]=1;
  S.Interaction(0).Index(1)[0]=1;   S.Interaction(0).Index(1)[1]=2;
  S.Interaction(0).Index(2)[0]=2;   S.Interaction(0).Index(2)[1]=3;
  S.Interaction(1).Index(0)[0]=0;   S.Interaction(1).Index(0)[1]=2;
  S.Interaction(1).Index(1)[0]=0;   S.Interaction(1).Index(1)[1]=3;
  S.Interaction(1).Index(2)[0]=1;   S.Interaction(1).Index(2)[1]=3;
  for(unsigned int i=0;i<3;++i) {
    Value<double>(S.Interaction(0).Parameter(i,HarmonicEqLength))=1.;
    Value<double>(S.Interaction(0).Parameter(i,HarmonicEqStrength))=100.;
    S.Interaction(0).ParameterBuild(i);
  }
  for(unsigned int i=0;i<3;++i) {
    Value<double>(S.Interaction(1).Parameter(i,LJ612EqRadius))=1.;
    Value<double>(S.Interaction(1).Parameter(i,LJ612EqEnergyDepth))=1.;
    S.Interaction(1).ParameterBuild(i);
  }

  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(2);
  S.InteractionGroup(0).WorkID(0)=0;
  S.InteractionGroup(0).WorkID(1)=1;

  S.UpdateB(0);
  cout.precision(20);

  Propagator<double,FreeSpace>* P=NULL;
  Introduce(P,LBFGSMinimizer,TrackingLineMinimizer);

  Array<StepPropagatorName> SPN;
  SPN.Allocate(1);
  SPN[0]=MinimizerShiftLine;
  P->Allocate(SPN);

  P->Update();

  P->Step(0)->AllocateRange(1);
  P->Step(0)->Range(0)[0]=0;
  P->Step(0)->Range(0)[1]=4;
  P->IntroduceSystem(S);

  P->Evolute(S);
  cout<<Value<unsigned int>(P->Parameter(BaseMin_GCalcCount))<<endl;
  cout<<Value<unsigned int>(P->Parameter(LBFGSMinimizer_LineSearchCount))<<endl;
  cout<<S.Energy()<<endl;
  for(unsigned int i=0;i<4;i++) {
    for(unsigned int j=0;j<2;j++) cout<<"\t"<<S.Location()[i][j];
    cout<<endl;
  }

  P->DetachSystem();

  return 0;
}

