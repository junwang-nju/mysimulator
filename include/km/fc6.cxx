
#include "system/interface.h"
#include "boundary/free/interface.h"
#include "array2d/interface.h"
#include "random/interface.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
using namespace std;

void Hessian(Array2DNumeric<Array2DNumeric<double> >& Hess,
             const System<double,FreeSpace>& S, ArrayNumeric<double>& Dsp,
             const unsigned int NB) {
  Hess.Fill(0);
  double D,iDst,Dst,TMP,TMPD,DR;
  unsigned int I,J;
  static FreeSpace FS;
  for(unsigned int i=0;i<NB;++i) {
    D=2*Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength));
    DR=D*Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength));
    I=S.Interaction(i).Index(0)[0];
    J=S.Interaction(i).Index(0)[1];
    Dst=DistanceSQ(Dsp,S.Location()[I],S.Location()[J],FS);
    iDst=1./Dst;
    Dsp.Scale(iDst);
    DR*=iDst;
    TMPD=D-DR;
    for(unsigned int k=0;k<3;++k)
    for(unsigned int l=0;l<3;++l) {
      TMP=DR*Dsp[k]*Dsp[l];
      if(k==l)  TMP+=TMPD;
      Hess[I][k][I][l]+=TMP;
      Hess[I][k][J][l]-=TMP;
      Hess[J][k][I][l]-=TMP;
      Hess[J][k][J][l]+=TMP;
    }
  }
}

int main() {
  System<double,FreeSpace> S;

  const unsigned int NMer=6;
  S.AllocateKind(NMer);
  for(unsigned int i=0;i<NMer;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(3);

  Array2D<InteractionFuncName> IFN;
  const unsigned int NB=8;
  IFN.Allocate(NB,1);
  for(unsigned int i=0;i<NB;++i) IFN[i][0]=Harmonic;
  S.AllocateInteraction(IFN,3);

  S.Interaction(0).Index(0)[0]=0;   S.Interaction(0).Index(0)[1]=1;
  S.Interaction(1).Index(0)[0]=1;   S.Interaction(1).Index(0)[1]=2;
  S.Interaction(2).Index(0)[0]=2;   S.Interaction(2).Index(0)[1]=3;
  S.Interaction(3).Index(0)[0]=3;   S.Interaction(3).Index(0)[1]=4;
  S.Interaction(4).Index(0)[0]=1;   S.Interaction(4).Index(0)[1]=3;
  S.Interaction(5).Index(0)[0]=1;   S.Interaction(5).Index(0)[1]=4;
  S.Interaction(6).Index(0)[0]=2;   S.Interaction(6).Index(0)[1]=4;
  S.Interaction(7).Index(0)[0]=4;   S.Interaction(7).Index(0)[1]=5;

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

  S.Location().Fill(0);
  S.Location()[1][0]=1;
  S.Location()[2][0]=2;
  S.Location()[3][0]=2; S.Location()[3][1]=1;
  S.Location()[4][0]=2; S.Location()[4][1]=1; S.Location()[4][2]=1;
  S.Location()[5][0]=3;

  S.Location()[2][0]=1.5; S.Location()[2][2]=__SqRoot(0.5); S.Location()[2][1]=0.5;
  S.Location()[3][0]=1.5; S.Location()[3][2]=__SqRoot(0.5); S.Location()[3][1]=-0.5;
  S.Location()[4][0]=2; S.Location()[4][1]=0; S.Location()[4][2]=0.;

  S.Velocity().Fill(0);

  S.UpdateB(0);

  Array2DNumeric<Array2DNumeric<double> > Hess;
  Array2DNumeric<double> GT,MX;
  ArrayNumeric<double> Dsp;

  Dsp.Allocate(3);
  GT.Allocate(NMer,3);
  MX.Allocate(NMer,3);
  Hess.Allocate(NMer,3);
  for(unsigned int i=0;i<NMer;++i)
  for(unsigned int k=0;k<3;++k) Hess[i][k].Allocate(NMer,3);

  BoxMuller<MersenneTwisterDSFMT<19937> > BG;
  MersenneTwisterDSFMT<216091> UG;
  BG.Allocate();
  BG.Init(2139731);
  UG.Allocate();
  UG.Init(24972847);

  cout.precision(10);

  const double Gamma=10;
  const double iGamma=1./Gamma;
  double T,MT;

  S.Velocity()[NMer-1][0]=1.;

  Hessian(Hess,S,Dsp,NB);
  for(unsigned int u=0;u<NB;++u) S.Interaction(u).ClearFlag();
  S.UpdateG(0);
  S.Velocity()[NMer-2].Copy(S.Gradient()[NMer-2]);
  S.Velocity()[NMer-2].Scale(-iGamma);
  GT.Fill(0);
  for(unsigned int j=0;j<3;++j)
    GT[NMer-2][j]+=_Dot(Hess[NMer-2][j],S.Velocity());
  T=GT.Norm();

  double DX,DY,DZ,CX,CY,CZ,THM;
  unsigned int NR;

  DX=2;
  DY=2;
  DZ=2;
  CX=2;
  CY=0;
  CZ=0;
  THM=1.;

  MT=T; MX[NMer-2].Copy(S.Location()[NMer-2]);
  while(true) {
    NR=0;
    while(true) {
      S.Location()[NMer-2][0]=UG.Double()*DX+(CX-DX*0.5);
      S.Location()[NMer-2][1]=UG.Double()*DY+(CY-DY*0.5);
      S.Location()[NMer-2][2]=UG.Double()*DZ+(CZ-DZ*0.5);
      Hessian(Hess,S,Dsp,NB);
      for(unsigned int u=0;u<NB;++u) S.Interaction(u).ClearFlag();
      S.UpdateG(0);
      S.Velocity()[NMer-2].Copy(S.Gradient()[NMer-2]);
      S.Velocity()[NMer-2].Scale(-iGamma);
      GT.Fill(0);
      for(unsigned int j=0;j<3;++j)
        GT[NMer-2][j]+=_Dot(Hess[NMer-2][j],S.Velocity());
      T=GT.Norm();
      if(T<MT) {
        MT=T; MX[NMer-2].Copy(S.Location()[NMer-2]);
        cout<<MT<<endl;
        cout<<"\t"<<MX[NMer-2][0]<<"\t"<<MX[NMer-2][1]<<"\t"<<MX[NMer-2][2]<<endl;
      }
      NR++;
      if(MT<THM) break;
      if(NR>=1e7)  break;
    }
    if(MT<1e-3) break;
    if(MT>THM) {
      CX=MX[NMer-2][0];
      CY=MX[NMer-2][1];
      CZ=MX[NMer-2][2];
      DX*=0.9;
      DY*=0.9;
      DZ*=0.9;
      cout<<"======== Shrink ========= "<<DX<<endl;
    } else {
      CX=MX[NMer-2][0];
      CY=MX[NMer-2][1];
      CZ=MX[NMer-2][2];
      DX*=0.8;
      DY*=0.8;
      DZ*=0.8;
      THM=MT*0.5;
      cout<<"======== New Step ========= "<<DX<<endl;
    }
  }

  return 0;
}

