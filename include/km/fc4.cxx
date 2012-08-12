
#include "system/interface.h"
#include "boundary/free/interface.h"
#include "array2d/interface.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
using namespace std;

void Hessian(Array2DNumeric<Array2DNumeric<double> >& Hess,
             const System<double,FreeSpace>& S, ArrayNumeric<double>& Dsp,
             const unsigned int NB) {
  Hess.Fill(0);
  double D,DstSQ,Dst,TMP,TMPD,DR;
  unsigned int I,J;
  static FreeSpace FS;
  for(unsigned int i=0;i<NB;++i) {
    D=2*Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength));
    DR=D*Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength));
    I=S.Interaction(i).Index(0)[0];
    J=S.Interaction(i).Index(0)[1];
    DstSQ=DistanceSQ(Dsp,S.Location()[I],S.Location()[J],FS);
    Dst=__SqRoot(DstSQ);
    TMPD=D-DR/Dst;
    for(unsigned int k=0;k<3;++k)
    for(unsigned int l=0;l<3;++l) {
      TMP=DR/DstSQ*Dsp[k]*Dsp[l];
      if(k==l)  TMP+=TMPD;
      Hess[I][k][I][l]+=TMP;
      Hess[I][k][J][l]-=TMP;
      Hess[J][k][I][l]-=TMP;
      Hess[J][k][J][l]+=TMP;
    }
  }
}

double HG(const Array2DNumeric<Array2DNumeric<double> >& Hess,
          System<double,FreeSpace>& S, const unsigned int NMer) {
  static const double Gamma=10;
  double Sum=0,D=0;
  S.Gradient()[0].Fill(0);
  S.Gradient()[NMer-1].Copy(S.Velocity()[NMer-1]);
  S.Gradient()[NMer-1].Scale(Gamma);
  for(unsigned int i=1;i<NMer-1;++i)
  for(unsigned int k=0;k<3;++k) {
    D=_Dot(Hess[i][k],S.Gradient());
    Sum+=D*D;
  }
  return __SqRoot(Sum);
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

  Hess.Allocate(NMer,3);
  for(unsigned int i=0;i<NMer;++i)
  for(unsigned int k=0;k<3;++k) Hess[i][k].Allocate(NMer,3);

  ArrayNumeric<double> Dsp;
  Dsp.Allocate(3);

  const double Del=1e-8;
  double T,TP,Step;
  unsigned int NG;
  Array2DNumeric<double> XBk;
  XBk.Imprint(S.Location());

  Hessian(Hess,S,Dsp,NB);
  for(unsigned int i=0;i<NB;++i) S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  T=HG(Hess,S,NMer);
  while(true) {
    NG=0;
    for(unsigned int i=1;i<NMer-1;++i)
    for(unsigned int k=0;k<3;++k) {
      XBk.BlasCopy(S.Location());
      Step=1e-3;
      while(true) {
        S.Location()[i][k]+=Step;
        Hessian(Hess,S,Dsp,NB);
        for(unsigned int u=0;u<NB;++u) S.Interaction(u).ClearFlag();
        S.UpdateG(0);
        TP=HG(Hess,S,NMer);
        //cout<<i<<"\t"<<k<<"\t"<<Step<<"\t"<<TP<<"\t"<<T<<endl;  getchar();
        if(TP<T)  { ++NG; T=TP; break; }
        S.Location()[i][k]-=Step*2.;
        Hessian(Hess,S,Dsp,NB);
        for(unsigned int u=0;u<NB;++u) S.Interaction(u).ClearFlag();
        S.UpdateG(0);
        TP=HG(Hess,S,NMer);
        //cout<<i<<"\t"<<k<<"\t"<<Step<<"\t"<<TP<<"\t"<<T<<endl;  getchar();
        if(TP<T)  { ++NG; T=TP; break; }
        S.Location()[i][k]+=Step;
        Step*=0.5;
        if(Step<Del) break;
      }
      //S.Location().BlasCopy(XBk);
    }
    cout<<NG<<"\t"<<T<<endl;
    if(NG==0) break;
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

  cout<<endl;
  Hessian(Hess,S,Dsp,NB);
  S.UpdateG(0);
  T=HG(Hess,S,NMer);
  cout<<T<<endl;

  return 0;
}

