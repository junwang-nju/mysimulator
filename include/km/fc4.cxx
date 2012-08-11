
#include "system/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  System<double,FreeSpace> S;

  const unsigned int NMer=6;
  A.AllocateKind(NMer);
  for(unsigned int i=0;i<NMer;++i) S.Kind(i)=ParticleUnit;
  A.AllocateXVGE(3);

  S.Location().Fill(0);
  S.Location()[1][0]=1;
  S.Location()[2][0]=2;
  S.Location()[3][0]=2; S.Location()[3][1]=1;
  S.Location()[4][0]=2; S.Location()[4][1]=1; S.Location()[4][2]=1;
  S.Location()[5][0]=4;

  S.Velocity().Fill(0);

  Array2DNumeric<InteractionFuncName> IFN;
  const unsigned int NB=8;
  IFN.Allocate(NB,1);
  for(unsigned int i=0;i<NB;++i) IFN[i]=Harmonic;
  S.AllocateInteraction(IFN,3);

  S.Interaction(0).Index(0)[0]=0;   S.Interaction(0).Index(0)[1]=1;
  S.Interaction(1).Index(0)[0]=1;   S.Interaction(1).Index(0)[1]=2;
  S.Interaction(2).Index(0)[0]=2;   S.Interaction(2).Index(0)[1]=3;
  S.Interaction(3).Index(0)[0]=3;   S.Interaction(3).Index(0)[1]=4;
  S.Interaction(4).Index(0)[0]=1;   S.Interaction(4).Index(0)[1]=3;
  S.Interaction(5).Index(0)[0]=1;   S.Interaction(5).Index(0)[1]=4;
  S.Interaction(6).Index(0)[0]=2;   S.Interaction(6).Index(0)[1]=4;
  S.Interaction(6).Index(0)[0]=4;   S.Interaction(7).Index(0)[1]=5;

  for(unsigned int i=0;i<NB;++i)
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength))=1.;

  Value<double>(S.Interaction(0).Parameter(0,HarmonicEqStrength))=20;
  Value<double>(S.Interaction(1).Parameter(0,HarmonicEqStrength))=100;
  Value<double>(S.Interaction(2).Parameter(0,HarmonicEqStrength))=100;
  Value<double>(S.Interaction(3).Parameter(0,HarmonicEqStrength))=100;
  Value<double>(S.Interaction(4).Parameter(0,HarmonicEqStrength))=20;
  Value<double>(S.Interaction(5).Parameter(0,HarmonicEqStrength))=20;
  Value<double>(S.Interaction(6).Parameter(0,HarmonicEqStrength))=20;
  Value<double>(S.Interaction(7).Parameter(0,HarmonicEqStrength))=20;

  for(unsigned int i=0;i<NB;++i) S.Interaction(i).ParameterBuild(0);

  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(NB);
  for(unsigned int i=0;i<NB;++i)  S.InteractionGroup(0).WorkID(i)=i;

  Array2DNumeric<Array2DNumeric<double> > Hess;

  Hess.Allocate(NMer,3);
  for(unsigned int i=0;i<NMer;++i)
  for(unsigned int k=0;k<3;++k) Hess[i][k].Allocate(NMer,3);

  double D,Dst,TMP;
  unsigned int I,J;
  ArrayNumeric<double> Dsp;
  FreeSpace FS;
  Dsp.Allocate(3);

  for(unsigned int i=0;i<NB;++i) {
    D=2*Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength));
    I=S.Interaction(i).Index(0)[0];
    J=S.Interaction(i).Index(0)[1];
    Dst=Distance(Dsp,S.Location()[I],S.Location()[J],FS);
    Dsp.Scale(1./Dst);
    for(unsigned int k=0;k<3;++k)
    for(unsigned int l=0;l<3;++l) {
      TMP=D*Dsp[k]*Dsp[l];
      Hess[I][k][I][l]+=TMP;
      Hess[I][k][J][l]-=TMP;
      Hess[J][k][I][l]-=TMP;
      Hess[J][k][J][l]+=TMP;
    }
  }

  return 0;
}

