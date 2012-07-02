
#include "propagator/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

namespace mysimulator {

  class OutTest : public PropagatorOutput<double,FreeSpace> {
    public:
      virtual void Allocate() {}
      virtual void Write(const double& now,System<double,FreeSpace>& S,
                         Propagator<double,FreeSpace>* P) {
        S.UpdateE(0);
        P->UpdateKineticEnergy();
        std::cout<<now<<"\t"<<S.Energy()<<"\t"<<P->KineticEnergy()<<endl;
      }
  };

}

int main() {

  System<double,FreeSpace>  S;

  S.AllocateKind(6);
  for(unsigned int i=0;i<4;++i) S.Kind(i)=ParticleUnit;
  for(unsigned int i=4;i<6;++i) S.Kind(i)=WallUnit;

  S.AllocateXVGE(2);
  S.Location()[0][0]=0;       S.Location()[0][1]=0;
  S.Location()[1][0]=1.2;     S.Location()[1][1]=0;
  S.Location()[2][0]=1.3;     S.Location()[2][1]=1.5;
  S.Location()[3][0]=0.8;     S.Location()[3][1]=2.2;
  S.Location()[4][0]=1;       S.Location()[4][1]=0;   S.Location()[4][2]=-1;
  S.Location()[5][0]=-1;      S.Location()[5][1]=0;   S.Location()[5][2]=-2;
  S.Velocity().Fill(0);

  Array2D<InteractionFuncName>  IFN;
  ArrayNumeric<unsigned int>  sz;
  sz.Allocate(3);
  sz[0]=3;    sz[1]=3;    sz[2]=2;
  IFN.Allocate(sz);
  for(unsigned int j=0;j<3;++j)   IFN[0][j]=Harmonic;
  for(unsigned int j=0;j<3;++j)   IFN[1][j]=LJ612;
  for(unsigned int j=0;j<2;++j)   IFN[2][j]=WallHarmonic;
  S.AllocateInteraction(IFN,2);
  S.Interaction(0).Index(0)[0]=0; S.Interaction(0).Index(0)[1]=1;
  S.Interaction(0).Index(1)[0]=1; S.Interaction(0).Index(1)[1]=2;
  S.Interaction(0).Index(2)[0]=2; S.Interaction(0).Index(2)[1]=3;
  S.Interaction(1).Index(0)[0]=0; S.Interaction(1).Index(0)[1]=2;
  S.Interaction(1).Index(1)[0]=0; S.Interaction(1).Index(1)[1]=3;
  S.Interaction(1).Index(2)[0]=1; S.Interaction(1).Index(2)[1]=3;
  S.Interaction(2).Index(0)[0]=4; S.Interaction(2).Index(0)[1]=0;
  S.Interaction(2).Index(1)[0]=5; S.Interaction(2).Index(1)[1]=3;
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
  for(unsigned int i=0;i<2;++i) {
    Value<double>(S.Interaction(2).Parameter(i,HarmonicEqLength))=1.;
    Value<double>(S.Interaction(2).Parameter(i,HarmonicEqStrength))=100.;
    S.Interaction(2).ParameterBuild(i);
  }

  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(3);
  S.InteractionGroup(0).WorkID(0)=0;
  S.InteractionGroup(0).WorkID(1)=1;
  S.InteractionGroup(0).WorkID(2)=2;

  S.UpdateB(0);

  Propagator<double,FreeSpace>* P=NULL;
  Introduce(P,MolecularDynamics);

  Array<StepPropagatorName> SPN;
  SPN.Allocate(2);
  SPN[0]=VelVerletConstE;
  SPN[1]=FixPosition;
  P->Allocate(SPN,UniqueMass,BoxMullerRNG,MTStandardRNG);
  P->AllocateOutput<OutTest>();

  P->Time(MDTime_NowTime)=0;
  P->IntTime(MDTime_NowStep)=0;
  P->Time(MDTime_TimeStep)=0.001;
  P->Time(MDTime_TotalPeriod)=10.;
  P->Time(MDTime_OutputInterval)=0.001;
  P->UpdateTime(Step_Total_OInterval);

  *Pointer<double>(P->Parameter(PropagatorMD_Mass))=1.;
  P->Update();

  P->Step(0)->AllocateRange(1);
  P->Step(0)->Range(0)[0]=0;
  P->Step(0)->Range(0)[1]=4;
  P->Step(1)->AllocateRange(1);
  P->Step(1)->Range(0)[0]=4;
  P->Step(1)->Range(0)[1]=2;
  P->IntroduceSystem(S);

  P->Evolute(S);

  P->DetachSystem();

  return 0;
}

