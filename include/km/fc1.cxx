
#include "system/interface.h"
#include "array2d/interface.h"
#include "boundary/free/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

double F(System<double,FreeSpace>& S,Array2DNumeric<double>& XBk,
                                     Array2DNumeric<double>& GP,
                                     Array2DNumeric<double>& GN) {
  static const double DT=1e-5;
  static const double Gamma=10;
  static const double IGamma=1./Gamma;
  for(unsigned int i=0;i<6;++i) S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  for(unsigned int i=1;i<=2;++i) {
    S.Velocity()[i].Copy(S.Gradient()[i]);
    S.Velocity()[i].Scale(-IGamma);
  }
  XBk.BlasCopy(S.Location());
  S.Location().BlasShift(DT,S.Velocity());
  for(unsigned int i=0;i<6;++i) S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  GP.BlasCopy(S.Gradient());
  S.Location().BlasShift(-2*DT,S.Velocity());
  for(unsigned int i=0;i<6;++i) S.Interaction(i).ClearFlag();
  S.UpdateG(0);
  GN.BlasCopy(S.Gradient());
  GP.NegShift(GN);
  double T=0;
  for(unsigned int i=1;i<=2;++i)  T+=GP[i].NormSQ();
  T=__SqRoot(T)/DT*0.5;
  S.Location().BlasCopy(XBk);
  return T;
}

void G(System<double,FreeSpace>& S,Array2DNumeric<double>& GF,
                                   Array2DNumeric<double>& XBk,
                                   Array2DNumeric<double>& XBk2,
                                   Array2DNumeric<double>& GP,
                                   Array2DNumeric<double>& GN) {
  static const double dd=1e-8;
  double TP,TN;
  for(unsigned int i=1;i<=2;++i)
  for(unsigned int k=0;k<2;++k) {
    XBk2.BlasCopy(S.Location());
    S.Location()[i][k]+=dd;
    TP=F(S,XBk,GP,GN);
    S.Location()[i][k]-=dd+dd;
    TN=F(S,XBk,GP,GN);
    S.Location().BlasCopy(XBk2);
    GF[i][k]=-(TP-TN)/dd*0.5;
  }
}

int main() {
  System<double,FreeSpace> S;
  Array2DNumeric<double> XBk,XBk2,GP,GN,GF;

  S.AllocateKind(4);
  for(unsigned int i=0;i<4;++i) S.Kind(i)=ParticleUnit;
  S.AllocateXVGE(2);

  S.Location().Fill(0);
  S.Location()[0][0]=0.;
  S.Location()[1][0]=__SqRoot(3.)/2.;      S.Location()[1][1]=1;
  S.Location()[2][0]=__SqRoot(3.)/2.;      S.Location()[2][1]=-0.5;
  S.Location()[3][0]=2.;

  S.Velocity().Fill(0);
  S.Velocity()[3][0]=1;

  XBk.Imprint(S.Location());
  XBk2.Imprint(S.Location());
  GP.Imprint(S.Location());
  GN.Imprint(S.Location());
  GF.Imprint(S.Location());

  Array2D<InteractionFuncName> IFN;
  IFN.Allocate(6,1);
  for(unsigned int i=0;i<6;++i) IFN[i][0]=Harmonic;
  S.AllocateInteraction(IFN,2);
  for(unsigned int i=0,n=0;i<4;++i)
  for(unsigned int j=i+1;j<4;++j,++n) {
    S.Interaction(n).Index(0)[0]=i;
    S.Interaction(n).Index(0)[1]=j;
  }
  for(unsigned int i=0;i<6;++i) {
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqLength))=1.;
    Value<double>(S.Interaction(i).Parameter(0,HarmonicEqStrength))=//100.;
      (S.Interaction(i).Index(0)[1]-S.Interaction(i).Index(0)[0]==1?100:10);
    S.Interaction(i).ParameterBuild(0);
  }
  S.AssignNumberInteractionGroup(1);
  S.InteractionGroup(0).Allocate(IFN.Size());
  for(unsigned int i=0;i<IFN.Size();++i) S.InteractionGroup(0).WorkID(i)=i;

  double NG,Step;
  double TP,T;

  T=F(S,XBk,GP,GN);
  while(true) {
    G(S,GF,XBk,XBk2,GP,GN);
    XBk.BlasCopy(S.Location());
    NG=0;
    for(unsigned int i=1;i<=2;++i) NG+=GF[i].NormSQ();
    if(NG<1e-12) break;
    else {
      NG=1./__SqRoot(NG);
      GF.BlasScale(NG);
      Step=0.1;
      while (Step>1e-8) {
        S.Location().BlasCopy(XBk);
        for(unsigned int i=1;i<=2;++i)  S.Location()[i].Shift(Step,GF[i]);
        TP=F(S,XBk2,GP,GN);
        if(TP<T)  { T=TP; break; }
        else Step*=0.5;
      }
      cout<<Step<<"\t"<<T<<endl;
      if(Step<1e-8) break;
    }
  }

  cout.precision(8);
  cout<<T<<endl;
  for(unsigned int i=0;i<4;++i) {
    for(unsigned int k=0;k<2;++k) cout<<"\t"<<S.Location()[i][k];
    for(unsigned int k=0;k<2;++k) cout<<"\t"<<S.Velocity()[i][k];
    cout<<endl;
  }

  for(unsigned int i=0;i<6;++i) S.Interaction(i).ClearFlag();
  S.UpdateE(0);
  cout<<endl;
  cout<<S.Energy()<<endl;
  for(unsigned int i=0;i<6;++i) cout<<i<<"\t"<<S.Interaction(i).Energy()<<endl;

  return 0;
}

