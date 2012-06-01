
#include "propagator/interface.h"
#include "pdb-file/interface.h"
#include "basic/angle-calc.h"
#include "basic/dihedral-calc.h"
#include "random/box-muller/interface.h"
#include "random/mt-dsfmt/interface.h"
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
        std::cout<<now<<"\t"<<S.Energy()<<"\t"<<P->KineticEnergy();
        std::cout<<"\t"<<S.Energy()+P->KineticEnergy();
        for(unsigned int i=0;i<5;++i) std::cout<<"\t"<<S.Interaction(i).Energy();
        cout<<endl;
      }
  };

}

int main() {

  cout.precision(12);

  PDBFile PF;
  PDBObject PO;
  PF.Load("2CI2");
  PF.Produce(PO);

  FreeSpace FS;

  System<double,FreeSpace> S;
  const unsigned int NR=PO.NumberResidue();
  S.AllocateKind(NR);
  for(unsigned int i=0;i<NR;++i)  S.Kind(i)=ParticleUnit;

  S.AllocateXVGE(3);
  PO.ProduceCAlpha<UseFirstModel>(S.Location());
  S.Velocity().Fill(0);

  BoxMuller<MersenneTwisterDSFMT<19937> > RNG;
  RNG.Allocate();
  //RNG.InitWithTime();
  RNG.Init(2789243);
  for(unsigned int i=0;i<S.Velocity().Size();++i)
  for(unsigned int k=0;k<S.Velocity()[i].Size();++k)
    S.Velocity()[i][k]=RNG.Double();

  Array2D<unsigned int> CM;
  const unsigned int NP=PO.ProduceContact<SheaDef,UseFirstModel>(CM);
  unsigned int NC=0;
  for(unsigned int i=0;i<NP;++i)
    if(CM[i][0]!=CM[i][2]) NC++;
    else if(CM[i][3]-CM[i][1]>=4) NC++;

  Array2D<InteractionFuncName> IFN;
  ArrayNumeric<unsigned int> sz;
  sz.Allocate(5);
  sz[0]=NR-1;
  sz[1]=NR-2;
  sz[2]=NC;
  sz[3]=(NR*(NR-1)/2)-sz[0]-sz[1]-sz[2]-(NR-3);
  sz[4]=NR-3;
  IFN.Allocate(sz);
  for(unsigned int i=0;i<sz[0];++i)   IFN[0][i]=Harmonic;
  for(unsigned int i=0;i<sz[1];++i)   IFN[1][i]=AngleHarmonic;
  for(unsigned int i=0;i<sz[2];++i)   IFN[2][i]=LJ1012;
  for(unsigned int i=0;i<sz[3];++i)   IFN[3][i]=CoreLJ612;
  for(unsigned int i=0;i<sz[4];++i)   IFN[4][i]=DihedralPeriodic2P;
  S.AllocateInteraction(IFN,3);
  for(unsigned int i=0;i<sz[0];++i) {
    S.Interaction(0).Index(i)[0]=i;
    S.Interaction(0).Index(i)[1]=i+1;
  }
  for(unsigned int i=0;i<sz[1];++i) {
    S.Interaction(1).Index(i)[0]=i;
    S.Interaction(1).Index(i)[1]=i+1;
    S.Interaction(1).Index(i)[2]=i+2;
  }
  for(unsigned int i=0,n=0;i<NP;i++)
    if((CM[i][0]!=CM[i][2])||(CM[i][3]-CM[i][1]>=4)) {
      S.Interaction(2).Index(n)[0]=PO.Index(CM[i][0],CM[i][1]);
      S.Interaction(2).Index(n)[1]=PO.Index(CM[i][2],CM[i][3]);
      ++n;
    }
  bool flag;
  for(unsigned int i=0,n=0;i<NR;++i)
  for(unsigned int j=i+4;j<NR;++j) {
    flag=false;
    for(unsigned int k=0;k<sz[2];++k)
      if((i==S.Interaction(2).Index(k)[0])&&(j==S.Interaction(2).Index(k)[1])) {
        flag=true;
        break;
      }
    if(!flag) {
      S.Interaction(3).Index(n)[0]=i;
      S.Interaction(3).Index(n)[1]=j;
      ++n;
    }
  }
  for(unsigned int i=0;i<sz[4];++i) {
    S.Interaction(4).Index(i)[0]=i;
    S.Interaction(4).Index(i)[1]=i+1;
    S.Interaction(4).Index(i)[2]=i+2;
    S.Interaction(4).Index(i)[3]=i+3;
  }

  ArrayNumeric<double> Dsp;
  Dsp.Allocate(3);
  for(unsigned int i=0;i<sz[0];++i) {
    Value<double>(S.Interaction(0).Parameter(i,HarmonicEqLength))=
      Distance(Dsp,S.Location()[S.Interaction(0).Index(i)[0]],
                   S.Location()[S.Interaction(0).Index(i)[1]],FS);
    Value<double>(S.Interaction(0).Parameter(i,HarmonicEqStrength))=100.;
    S.Interaction(0).ParameterBuild(i);
  }
  for(unsigned int i=0;i<sz[1];++i) {
    Value<double>(S.Interaction(1).Parameter(i,AngleHarmonicEqAngle))=
      Angle(S.Location()[S.Interaction(1).Index(i)[0]],
            S.Location()[S.Interaction(1).Index(i)[1]],
            S.Location()[S.Interaction(1).Index(i)[2]]);
    Value<double>(S.Interaction(1).Parameter(i,AngleHarmonicStrength))=20.;
    S.Interaction(1).ParameterBuild(i);
  }
  for(unsigned int i=0;i<sz[2];++i) {
    Value<double>(S.Interaction(2).Parameter(i,LJ1012EqRadius))=
      Distance(Dsp,S.Location()[S.Interaction(2).Index(i)[0]],
                   S.Location()[S.Interaction(2).Index(i)[1]],FS);
    Value<double>(S.Interaction(2).Parameter(i,LJ1012EqEnergyDepth))=1.;
    S.Interaction(2).ParameterBuild(i);
  }
  for(unsigned int i=0;i<sz[3];++i) {
    Value<double>(S.Interaction(3).Parameter(i,CoreLJ612Radius))=4.;
    Value<double>(S.Interaction(3).Parameter(i,CoreLJ612EnergyDepth))=1.;
    S.Interaction(3).ParameterBuild(i);
  }
  for(unsigned int i=0;i<sz[4];++i) {
    Value<double>(S.Interaction(4).Parameter(i,DihedralPeriodicShift+
                                               DihedralPeriodicPhase))=
      Dihedral(S.Location()[S.Interaction(4).Index(i)[0]],
               S.Location()[S.Interaction(4).Index(i)[1]],
               S.Location()[S.Interaction(4).Index(i)[2]],
               S.Location()[S.Interaction(4).Index(i)[3]]);
    Value<double>(S.Interaction(4).Parameter(i,DihedralPeriodicShift+
                                               DihedralPeriodicStrength))=1.;
    Value<unsigned int>(S.Interaction(4).
        Parameter(i,DihedralPeriodicShift+DihedralPeriodicFrequency))=1;
    Value<double>(S.Interaction(4).
        Parameter(i,DihedralPeriodicShift+DihedralPeriodicUnitNumberParameter+
                    DihedralPeriodicPhase))=
      Value<double>(S.Interaction(4).Parameter(i,DihedralPeriodicShift+
                                                 DihedralPeriodicPhase));
    Value<double>(S.Interaction(4).
        Parameter(i,DihedralPeriodicShift+DihedralPeriodicUnitNumberParameter+
                    DihedralPeriodicStrength))=0.5;
    Value<unsigned int>(S.Interaction(4).
        Parameter(i,DihedralPeriodicShift+DihedralPeriodicUnitNumberParameter+
                    DihedralPeriodicFrequency))=3;
    S.Interaction(4).ParameterBuild(i);
  }
  Clear(Dsp);

  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(5);
  for(unsigned int i=0;i<5;++i) S.InteractionGroup(0).WorkID(i)=i;

  S.UpdateB(0);

  Propagator<double,FreeSpace>* P=NULL;
  Introduce(P,MolecularDynamics);

  Array<StepPropagatorName>   SPN;
  SPN.Allocate(1);
  SPN[0]=VelVerletConstE;
  P->Allocate(SPN,UniqueMass);
  P->AllocateOutput<MyOut>();

  P->Time(MDTime_NowTime)=0;
  P->IntTime(MDTime_NowStep)=0;
  P->Time(MDTime_TimeStep)=0.0001;
  P->Time(MDTime_TotalPeriod)=10.;
  P->Time(MDTime_OutputInterval)=0.0001;
  P->UpdateTime(Step_Total_OInterval);

  *Pointer<double>(P->Parameter(PropagatorMD_Mass))=1.;
  P->Update();

  P->Step(0)->AllocateRange(1);
  P->Step(0)->Range(0)[0]=0;
  P->Step(0)->Range(0)[1]=NR;
  P->IntroduceSystem(S);

  P->Evolute(S);

  P->DetachSystem();

  return 0;

}

