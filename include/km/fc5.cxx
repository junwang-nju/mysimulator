
#include "array2d-numeric/interface.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

void GH(const Array2DNumeric<double>& X,Array2DNumeric<double>& Hess,
        ArrayNumeric<double>& Dsp) {
  Hess.Fill(0);
  double T;
  Dsp.Copy(X[3]);
  Dsp.NegShift(X[0]);
  T=Dsp.Norm();
  Dsp.Scale(1./T);
  for(unsigned int i=0;i<3;++i) Hess[i+3][i+3]+=20-20/T;
  for(unsigned int i=0;i<3;++i)
  for(unsigned int j=0;j<3;++j) Hess[i+3][j+3]+=20/T*Dsp[i]*Dsp[j];
  Dsp.Copy(X[3]);
  Dsp.NegShift(X[1]);
  T=Dsp.Norm();
  Dsp.Scale(1./T);
  for(unsigned int i=0;i<3;++i) Hess[i+3][i+3]+=20-20/T;
  for(unsigned int i=0;i<3;++i)
  for(unsigned int j=0;j<3;++j) Hess[i+3][j+3]+=20/T*Dsp[i]*Dsp[j];
  Dsp.Copy(X[3]);
  Dsp.NegShift(X[2]);
  T=Dsp.Norm();
  Dsp.Scale(1./T);
  double TT;
  for(unsigned int i=0;i<6;++i) Hess[i][i]+=100-100/T;
  for(unsigned int i=0;i<3;++i)
  for(unsigned int j=0;j<3;++j) {
    TT=100/T*Dsp[i]*Dsp[j];
    Hess[i][j]+=TT;
    Hess[i][j+3]-=TT;
    Hess[i+3][j]-=TT;
    Hess[i+3][j+3]+=TT;
  }
  Dsp.Copy(X[3]);
  Dsp.NegShift(X[4]);
  T=Dsp.Norm();
  Dsp.Scale(1./T);
  for(unsigned int i=0;i<6;++i) Hess[i+3][i+3]+=20-20/T;
  for(unsigned int i=0;i<3;++i)
  for(unsigned int j=0;j<3;++j) {
    TT=20/T*Dsp[i]*Dsp[j];
    Hess[i+3][j+3]+=TT;
    Hess[i+3][j+6]-=TT;
    Hess[i+6][j+3]-=TT;
    Hess[i+6][j+6]+=TT;
  }
}

void GV(const Array2DNumeric<double>& X,Array2DNumeric<double>& V,
        ArrayNumeric<double>& Dsp) {
  static const double Gamma=10.;
  static const double iGamma=1./Gamma;
  double T;
  V.Fill(0);
  Dsp.Copy(X[3]);
  Dsp.NegShift(X[0]);
  T=Dsp.Norm();
  for(unsigned int i=0;i<3;i++) V[3][i]+=20*(T-1.)/T*Dsp[i];
  Dsp.Copy(X[3]);
  Dsp.NegShift(X[1]);
  T=Dsp.Norm();
  for(unsigned int i=0;i<3;i++) V[3][i]+=20*(T-1.)/T*Dsp[i];
  Dsp.Copy(X[3]);
  Dsp.NegShift(X[2]);
  T=Dsp.Norm();
  double TT;
  for(unsigned int i=0;i<3;i++) {
    TT=100*(T-1.)/T*Dsp[i];
    V[3][i]+=TT;
    V[2][i]-=TT;
  }
  Dsp.Copy(X[3]);
  Dsp.NegShift(X[4]);
  T=Dsp.Norm();
  for(unsigned int i=0;i<3;i++) V[3][i]+=20*(T-1.)/T*Dsp[i];
  V.Scale(-iGamma);
}

int main() {
  Array2DNumeric<double> X,F,V;
  Array2DNumeric<double> Hess;
  ArrayNumeric<double> Dsp,GT,XM2,XM3;

  X.Allocate(5,3);
  F.Allocate(5,3);
  V.Allocate(5,3);
  XM2.Allocate(3);
  XM3.Allocate(3);

  Hess.Allocate(9,9);
  Dsp.Allocate(3);
  GT.Allocate(6);

  double T,MT;

  T=__SqRoot(0.5);
  X[0][0]=1;    X[0][1]=0;    X[0][2]=0;
  X[1][0]=1.5;  X[1][1]=0.5;  X[1][2]=T;
  X[2][0]=1.5;  X[2][1]=-0.5; X[2][2]=T;
  X[3][0]=2;    X[3][1]=0;    X[3][2]=0;
  X[4][0]=3;    X[4][1]=0.;   X[4][2]=0.;

  V.Fill(0);
  V[4][0]=1.;

  GH(X,Hess,Dsp);
  GV(X,V,Dsp);
  GT.Fill(0);
  for(unsigned int i=0;i<6;++i) {
    for(unsigned int j=0;j<3;++j) GT[i]+=Hess[i][j]*V[2][j];
    for(unsigned int j=0;j<3;++j) GT[i]+=Hess[i][j+3]*V[3][j];
    for(unsigned int j=0;j<3;++j) GT[i]+=Hess[i][j+6]*V[4][j];
  }
  T=GT.Norm();

  MT=1e10;
  for(X[2][0]=1;X[2][0]<=2;X[2][0]+=0.01)
  for(X[2][1]=-1;X[2][1]<=1;X[2][1]+=0.01)
  for(X[2][2]=-1;X[2][2]<=1;X[2][2]+=0.01)
  for(X[3][0]=1;X[3][0]<=3;X[3][0]+=0.01)
  for(X[3][1]=-1;X[3][1]<=1;X[3][1]+=0.01)
  for(X[3][2]=-1;X[3][2]<=1;X[3][2]+=0.01) {
    GH(X,Hess,Dsp);
    GV(X,V,Dsp);
    GT.Fill(0);
    for(unsigned int i=0;i<3;++i) {
      for(unsigned int j=0;j<3;++j) GT[i]+=Hess[i][j]*V[2][j];
      for(unsigned int j=0;j<3;++j) GT[i]+=Hess[i][j+3]*V[3][j];
      for(unsigned int j=0;j<3;++j) GT[i]+=Hess[i][j+6]*V[4][j];
    }
    T=GT.Norm();
    if(T<MT) { MT=T; XM2.Copy(X[2]); XM3.Copy(X[3]); cout<<MT<<endl; }
  }

  cout<<endl;
  cout<<MT<<endl;
  cout<<XM2[0]<<"\t"<<XM2[1]<<"\t"<<XM2[2]<<endl;
  cout<<XM3[0]<<"\t"<<XM3[1]<<"\t"<<XM3[2]<<endl;

  return 0;
}

