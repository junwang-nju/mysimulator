
#include "propagator/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

namespace mysimulator {

  class MyOut : public PropagatorOutput<double,FreeSpace> {
    public:
      virtual void Allocate() {}
      virtual void Write(const double& now,System<double,FreeSpace>& S,
                         Propagator<double,FreeSpace>* P) {
        S.UpdateE(0);
        P->UpdateKineticEnergy();
        std::cout<<now<<"\t"<<S.Energy()<<"\t"<<P->KineticEnergy()<<"\t";
        std::cout<<S.Location()[1][0]<<"\t"<<S.Location()[1][1]<<"\t";
        std::cout<<S.Location()[2][0]<<"\t"<<S.Location()[2][1]<<endl;
      }
  };

}

int main() {

  System<double,FreeSpace> S;

  S.AllocateKind(3);
  for(unsigned int i=0;i<3;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(2);
  S.Location()[0][0]=0;         S.Location()[0][1]=0;
  S.Location()[1][0]=1;         S.Location()[1][1]=0;
  S.Location()[2][0]=2;         S.Location()[2][1]=0;
  S.Velocity().Fill(0);
  S.Velocity()[2][0]=0.1;

  Array2D<InteractionFuncName> IFN;
  ArrayNumeric<unsigned int> sz;
  sz.Allocate(1);
  sz.Fill(2U);
  IFN.Allocate(sz);
  for(unsigned int j=0;j<2;++j) IFN[0][j]=Harmonic;
  S.AllocateInteraction(IFN,2);
  S.Interaction(0).Index(0)[0]=0;   S.Interaction(0).Index(0)[1]=1;
  S.Interaction(0).Index(1)[0]=1;   S.Interaction(0).Index(1)[1]=2;
  for(unsigned int i=0;i<2;++i) {
    Value<double>(S.Interaction(0).Parameter(i,HarmonicEqLength))=1.;
    Value<double>(S.Interaction(0).Parameter(i,HarmonicEqStrength))=100.;
    S.Interaction(0).ParameterBuild(i);
  }
  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(1);
  S.InteractionGroup(0).WorkID(0)=0;

  S.UpdateB(0);
  cout.precision(20);

  Propagator<double,FreeSpace>* P=NULL;
  Introduce(P,MolecularDynamics);

  Array<StepPropagatorName> SPN;
  SPN.Allocate(3);
  SPN[0]=FixPosition;
  SPN[1]=VelVerletConstE;
  SPN[2]=VelVerletConstVelocity;
  P->Allocate(SPN,UniqueMass);
  P->AllocateOutput<MyOut>();

  P->Time(MDTime_NowTime)=0;
  P->IntTime(MDTime_NowStep)=0;
  P->Time(MDTime_TimeStep)=0.001;
  P->Time(MDTime_TotalPeriod)=2.;
  P->Time(MDTime_OutputInterval)=0.001;
  P->UpdateTime(Step_Total_OInterval);

  *Pointer<double>(P->Parameter(PropagatorMD_Mass))=1.;
  P->Update();

  P->Step(0)->AllocateRange(1);
  P->Step(0)->Range(0)[0]=0;
  P->Step(0)->Range(0)[1]=1;
  P->Step(1)->AllocateRange(1);
  P->Step(1)->Range(0)[0]=1;
  P->Step(1)->Range(0)[1]=1;
  P->Step(2)->AllocateRange(1);
  P->Step(2)->Range(0)[0]=2;
  P->Step(2)->Range(0)[1]=1;
  P->IntroduceSystem(S);

  P->Evolute(S);

  P->DetachSystem();

  return 0;
}

