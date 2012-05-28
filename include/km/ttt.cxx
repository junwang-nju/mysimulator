
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
  SPN.Allocate(1,2);
  SPN[0][0]=VelVerletConstE;
  SPN[0][1]=FixPosition;
  P->Allocate(SPN);

  P->Time().InitNowTime(0);
  P->Time().SetTime(0.001,10.);
  P->SetOutputTime(0.001);

  *Pointer<double>(P->Parameter(PropagatorMass))=1.;
  P->Update();

  System<double,FreeSpace> S;

  S.AllocateKind(6);
  for(unsigned int i=0;i<4;++i) S.Kind(i)=ParticleUnit;
  S.Kind(4)=WallUnit;
  S.Kind(5)=WallUnit;
  S.AllocateXVGE(2);
  S.Location()[0][0]=0;    S.Location()[0][1]=0;
  S.Location()[1][0]=1.2;  S.Location()[1][1]=0;
  S.Location()[2][0]=1.3;  S.Location()[2][1]=1.5;
  S.Location()[3][0]=0.8;  S.Location()[3][1]=2.2;
  S.Location()[4][0]=1;    S.Location()[4][1]=0;    S.Location()[4][2]=-1;
  S.Location()[5][0]=-1;   S.Location()[5][1]=0;    S.Location()[5][2]=2;
  S.Velocity().Fill(0);

  Array2D<InteractionFuncName>  IFN;
  ArrayNumeric<unsigned int> sz;
  sz.Allocate(3);
  sz[0]=3;    sz[1]=3;    sz[2]=2;
  IFN.Allocate(sz);
  for(unsigned int j=0;j<3;++j) IFN[0][j]=Harmonic;
  for(unsigned int j=0;j<3;++j) IFN[1][j]=LJ612;
  for(unsigned int j=0;j<2;++j) IFN[2][j]=WallHarmonic;
  S.AllocateInteraction(IFN,2);
  S.Interaction(0).Index(0)[0]=0;   S.Interaction(0).Index(0)[1]=1;
  S.Interaction(0).Index(1)[0]=1;   S.Interaction(0).Index(1)[1]=2;
  S.Interaction(0).Index(2)[0]=2;   S.Interaction(0).Index(2)[1]=3;
  S.Interaction(1).Index(0)[0]=0;   S.Interaction(1).Index(0)[1]=2;
  S.Interaction(1).Index(1)[0]=0;   S.Interaction(1).Index(1)[1]=3;
  S.Interaction(1).Index(2)[0]=1;   S.Interaction(1).Index(2)[1]=3;
  S.Interaction(2).Index(0)[0]=4;   S.Interaction(2).Index(0)[1]=0;
  S.Interaction(2).Index(1)[0]=5;   S.Interaction(2).Index(1)[1]=3;
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
  //cout<<S.Energy()<<endl;

  P->Steps(0,0)->AllocateRange(1);
  P->Steps(0,0)->Range(0)[0]=0;
  P->Steps(0,0)->Range(0)[1]=4;
  P->Steps(0,1)->AllocateRange(1);
  P->Steps(0,1)->Range(0)[0]=4;
  P->Steps(0,1)->Range(0)[1]=2;
  P->IntroduceSystem(S);

  P->Evolute(S);

  delete P; P=NULL;
  return 0;
}

