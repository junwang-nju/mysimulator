
#include "matrix/rectangle/eigen-analysis.h"
#include "array/2d/fill.h"
#include "array/1d/io.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double Entr(const Array2D<unsigned int>& ID, const Array1D<double>& Sigma,
            const Array1D<bool>& FG, MatrixRectangle<double>& Mat,
            Array1D<double>& DTMP,Array1D<int>& ITMP,Array1D<double>& EVal) {
  double TSig;
  Fill(Mat,0.);
  for(unsigned int i=0;i<ID.Size();++i) {
    if(FG[i]) {
      TSig=1./(Sigma[i]*Sigma[i]);
      for(unsigned int k=ID[i][0];k<ID[i][1];++k)
      for(unsigned int l=ID[i][0];l<ID[i][1];++l)
        Mat[k][l]+=TSig;
    }
  }
  EigenValue(Mat,EVal,DTMP,ITMP);
  double entropy=0;
  for(unsigned int i=0;i<EVal.Size();++i) entropy+=log(EVal[i]);
  return -entropy*1.5;
}

int main() {

  unsigned int L;
  unsigned int NB;
  L=7;
  NB=(L*(L-1))/2;

  Array2D<unsigned int> ID;
  Array1D<double> Sigma,SigmaUpp,SigmaLow;
  Array1D<bool> FG;
  ID.Allocate(NB,2);
  Sigma.Allocate(NB);
  SigmaUpp.Allocate(NB);
  SigmaLow.Allocate(NB);
  FG.Allocate(NB);
  for(unsigned int i=0;i<L-1;++i) {
    ID[i][0]=i;   ID[i][1]=i+1;
  }
  for(unsigned int i=0,n=L-1;i<L;++i)
  for(unsigned int j=i+2;j<L;++j,++n) {
    ID[n][0]=i;   ID[n][1]=j;
  }
  Fill(FG,true,NB);

  for(unsigned int i=0;i<L-1;++i) {
    SigmaUpp[i]=1.1;    SigmaLow[i]=0.9;
  }
  for(unsigned int i=L-1;i<NB;++i) {
    SigmaUpp[i]=100;    SigmaLow[i]=0.9;
  }
  SigmaUpp[L-1+L-3]=1.1;  SigmaLow[L-1+L-3]=0.9;

  MatrixRectangle<double> Mat;
  Array1D<double> DTMP;
  Array1D<int> ITMP;
  Array1D<double> EVal;
  Mat.Allocate(L-1,L-1);
  DTMP.Allocate(L+L-1);
  ITMP.Allocate(1);
  EVal.Allocate(L-1);

  Array1D<bool> State;
  State.Allocate(NB);
  Fill(State,true,NB);
  int NowCB,Fac,nT,cT;
  double SEntr;
  bool firstFG=true;
  unsigned int Level=21;

  cout.precision(20);
  Fac=1;
  NowCB=NB-1;
  SEntr=0;
  cT=0;
  while(true) {
    nT=0;
    for(unsigned int i=0;i<NB;++i)  nT+=(State[i]?1:0);
    if(nT==Level) {
      Fac=1;
      for(unsigned int i=0;i<NB;++i)
        Sigma[i]=(State[i]?SigmaUpp[i]:SigmaLow[i]);
      SEntr+=Fac*exp(Entr(ID,Sigma,FG,Mat,DTMP,ITMP,EVal));
      cT+=1.;
      //cout<<Entr(ID,Sigma,FG,Mat,DTMP,ITMP,EVal)<<endl;
      //if(firstFG) { cout<<log(SEntr)<<"\t"; firstFG=false; }
    }
    while(!State[NowCB]) { --NowCB; if(NowCB<0) break; }
    if(NowCB<0) break;
    State[NowCB]=false;
    Fac*=-1;
    while(static_cast<unsigned int>(NowCB)<NB-1) {
      ++NowCB; State[NowCB]=true; Fac*=-1;
    }
  }
  cout<<Level<<"\t"<<log(SEntr)-log(cT)<<endl;

  /*
  double TEntr[2][2];
  for(unsigned int i=0;i<2;++i) {
    Sigma[0]=(i==0?1.1:0.9);
    for(unsigned int j=0;j<2;++j) {
      Sigma[1]=(j==0?1.1:0.9);
      TEntr[i][j]=Entr(ID,Sigma,FG,Mat,DTMP,ITMP,EVal);
      cout<<TEntr[i][j]<<endl;
    }
  }
  double avEntr=(TEntr[0][0]+TEntr[1][1])*0.5;
  double SEntr=0,Fi,Fj;
  for(unsigned int i=0;i<2;++i) {
    Fi=(i==0?1:-1);
    for(unsigned int j=0;j<2;++j) {
      Fj=(j==0?1:-1);
      SEntr+=Fi*Fj*exp(TEntr[i][j]-avEntr);
    }
  }
  SEntr=log(SEntr)+avEntr;
  cout<<"Sum: "<<SEntr<<endl;
  */
  /*
  cout.precision(20);
  double TEntr[2][2][2];
  for(unsigned int i=0;i<2;++i) {
    Sigma[0]=(i==0?1.1:0.9);
    for(unsigned int j=0;j<2;++j) {
      Sigma[1]=(j==0?1.1:0.9);
      for(unsigned int k=0;k<2;++k) {
        Sigma[2]=(k==0?1.1:0.9);
        TEntr[i][j][k]=Entr(ID,Sigma,FG,Mat,DTMP,ITMP,EVal);
        cout<<TEntr[i][j][k]<<endl;
      }
    }
  }
  double avEntr=(TEntr[0][0][0]+TEntr[1][1][1])*0.5;
  double SEntr=0,Fi,Fj,Fk;
  for(unsigned int i=0;i<2;++i) {
    Fi=(i==0?1:-1);
    for(unsigned int j=0;j<2;++j) {
      Fj=(j==0?1:-1);
      for(unsigned int k=0;k<2;++k) {
        Fk=(k==0?1:-1);
        SEntr+=Fi*Fj*Fk*exp(TEntr[i][j][k]-avEntr);
      }
    }
  }
  SEntr=log(SEntr)+avEntr;
  cout<<"Sum: "<<SEntr<<endl;
  */

  return 0;

}
