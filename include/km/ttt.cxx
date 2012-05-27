
#include "propagator/regular/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

namespace mysimulator {

  class OutTest : public PropagatorOutput<double,FreeSpace,
                                          BoxMuller<MersenneTwisterStandard> > {
    public:
      virtual void Write(const double& now,System<double,FreeSpace>& S,
                         Propagator<double,FreeSpace,
                                    BoxMuller<MersenneTwisterStandard> >* P) {
        S.UpdateE(0);
        P->UpdateKineticEnergy();
        std::cout<<now<<"\t"<<S.Energy()<<"\t"<<P->KineticEnergy()<<endl;
      }
  };

}

int main() {
  Propagator<double,FreeSpace>* P=new PropagatorRegular<double,FreeSpace>;

  P->SetMassFlag(UniqueMass);
  P->SetFrictionFlag(UnknownFrictionProperty);
  P->Output()=new OutTest;

  Array2D<StepPropagatorName>   SPN;
  SPN.Allocate(1,1);
  SPN[0][0]=VelVerletConstE;
  P->Allocate(SPN);

  P->Time().InitNowTime(0);
  P->Time().SetTime(0.001,10.);
  P->SetOutputTime(0.001);

  Value<double>(P->Parameter(PropagatorMass))=1.;
  P->Steps(0,0)->Update();

  System<double,FreeSpace> S;

  S.AllocateXVGE(4,2);
  S.Location()[0][0]=0;       S.Location()[0][1]=0;
  S.Location()[1][0]=1.2;     S.Location()[1][1]=0;
  S.Location()[2][0]=1.3;     S.Location()[2][1]=1.5;
  S.Location()[3][0]=0.8;     S.Location()[3][1]=2.2;
  for(unsigned int i=0;i<3;++i)
    S.Velocity()[i][0]=S.Velocity()[i][1]=0;

  Array2D<InteractionFuncName>  IFN;
  IFN.Allocate(2,3);
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
  cout<<S.Energy()<<endl;

  P->Steps(0,0)->AllocateRange(1);
  P->Steps(0,0)->Range(0)[0]=0;
  P->Steps(0,0)->Range(0)[1]=4;
  P->IntroduceSystem(S);

  P->Evolute(S);

  return 0;
}

