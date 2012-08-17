
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

void HG(Array2DNumeric<Array2DNumeric<double> >& Hess,
        System<double,FreeSpace>& S, const unsigned int NMer,
        const unsigned int NB,ArrayNumeric<double>& Dsp,
        Array2DNumeric<double>& GT) {
  static const double Gamma=10;
  static const double iGamma=1./Gamma;
  Hessian(Hess,S,Dsp,NB);
  for(unsigned int u=0;u<NB;++u) S.Interaction(u).ClearFlag();
  S.UpdateG(0);
  S.Gradient().BlasScale(-iGamma);
  S.Gradient()[0].Fill(0);
  S.Gradient()[NMer-1].Copy(S.Velocity()[NMer-1]);
  GT.BlasFill(0);
  for(unsigned int i=1;i<NMer-1;++i)
  for(unsigned int k=0;k<3;++k)
    GT[i][k]=_Dot(Hess[i][k],S.Gradient());
}

int main() {
  System<double,FreeSpace> S;

  const unsigned int NMer=6;
  S.AllocateKind(NMer);
  for(unsigned int i=0;i<NMer;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(3);

  S.Location().Fill(0);
  S.Location()[1][0]=1;
  S.Location()[2][0]=2;
  S.Location()[3][0]=2; S.Location()[3][1]=1;
  S.Location()[4][0]=2; S.Location()[4][1]=1; S.Location()[4][2]=1;
  S.Location()[5][0]=3;

  //S.Location()[2][0]=1.5; S.Location()[2][2]=__SqRoot(0.5); S.Location()[2][1]=0.5;
  //S.Location()[3][0]=1.5; S.Location()[3][2]=__SqRoot(0.5); S.Location()[3][1]=-0.5;
  //S.Location()[4][0]=2; S.Location()[4][1]=0; S.Location()[4][2]=0.1;

  //ifstream ifs;
  //ifs.open("bbb");
  //for(unsigned int i=0;i<NMer;++i)
  //for(unsigned int k=0;k<3;++k)
  //  ifs>>S.Location()[i][k];
  //ifs.close();

  S.Velocity().Fill(0);

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

  S.UpdateB(0);

  Array2DNumeric<Array2DNumeric<double> > Hess;
  Array2DNumeric<double> GT;
  ArrayNumeric<double> Dsp,OL;

  Dsp.Allocate(3);
  OL.Allocate(3);
  GT.Allocate(NMer,3);
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
  double T,TP,Step;
  unsigned int MI,NG;

  HG(Hess,S,NMer,NB,Dsp,GT);
  T=GT.Norm();

  S.Velocity()[NMer-1][0]=1.;

  NG=0;
  Step=0.001;
  while(true) {
    MI=UG.Double()*(NMer-1)+1;
    OL.Copy(S.Location()[MI]);
    for(unsigned int k=0;k<3;++k)
      S.Location()[MI][k]+=BG.Double()*Step;
    HG(Hess,S,NMer,NB,Dsp,GT);
    TP=GT.Norm();
    if(TP<T) {
      T=TP; cout<<T<<"\t"<<NG<<endl;
      if(NG>200) Step=1e-5; else Step=1e-4;
      NG=0;
    } else { S.Location()[MI].Copy(OL); NG++; }
    if(T<1e-3)  break;
  }


  for(unsigned int i=0;i<NMer;++i) {
    for(unsigned int k=0;k<3;++k) cout<<"\t"<<S.Location()[i][k];
    cout<<endl;
  }

  cout<<endl;
  for(unsigned int u=0;u<NB;++u) S.Interaction(u).ClearFlag();
  S.UpdateE(0);
  for(unsigned int i=0;i<NB;++i)
    cout<<i<<"\t"<<S.Interaction(i).Energy()<<endl;

  return 0;
}

