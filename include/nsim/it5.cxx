
#include "matrix/rectangle/eigen-analysis.h"
#include "array/2d/fill.h"
#include "array/1d/io.h"
#include "random/mt/interface.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double Entr(const Array2D<unsigned int>& ID, const Array1D<double>& Sigma,
            MatrixRectangle<double>& Mat,
            Array1D<double>& DTMP,Array1D<int>& ITMP,Array1D<double>& EVal) {
  double TSig;
  Fill(Mat,0.);
  for(unsigned int i=0;i<ID.Size();++i) {
    TSig=1./(Sigma[i]*Sigma[i]);
    for(unsigned int k=ID[i][0];k<ID[i][1];++k)
    for(unsigned int l=ID[i][0];l<ID[i][1];++l)
      Mat[k][l]+=TSig;
  }
  EigenValue(Mat,EVal,DTMP,ITMP);
  double entropy=0;
  for(unsigned int i=0;i<EVal.Size();++i) entropy+=log(EVal[i]);
  return -entropy*1.5;
}

unsigned int NTrue(const Array1D<bool>& FG) {
  unsigned int n=0;
  for(unsigned int i=0;i<FG.Size();++i) if(FG[i]) n++;
  return n;
}

int main() {

  unsigned int L;
  unsigned int NB;
  L=7;
  NB=(L*(L-1))/2;

  Array2D<unsigned int> ID;
  Array1D<double> Sigma,SigmaUpp,SigmaLow;
  ID.Allocate(NB,2);
  Sigma.Allocate(NB);
  SigmaUpp.Allocate(NB);
  SigmaLow.Allocate(NB);
  for(unsigned int i=0;i<L-1;++i) {
    ID[i][0]=i;   ID[i][1]=i+1;
  }
  for(unsigned int i=0,n=L-1;i<L;++i)
  for(unsigned int j=i+2;j<L;++j,++n) {
    ID[n][0]=i;   ID[n][1]=j;
  }

  for(unsigned int i=0;i<L-1;++i) {
    SigmaUpp[i]=1.1;    SigmaLow[i]=0.9;
  }
  for(unsigned int i=L-1;i<NB;++i) {
    SigmaUpp[i]=100;    SigmaLow[i]=0.9;
  }
  SigmaUpp[L-1+L-3]=1.1;  SigmaLow[L-1+L-3]=0.9;
  //SigmaUpp[L-1+L-1]=1.1;  SigmaLow[L-1+L-1]=0.9;
  //SigmaUpp[7]=1.1;  SigmaLow[7]=0.9;
  //SigmaUpp[15]=1.1;  SigmaLow[15]=0.9;
  //SigmaUpp[19]=1.1;  SigmaLow[19]=0.9;

  MatrixRectangle<double> Mat;
  Array1D<double> DTMP;
  Array1D<int> ITMP;
  Array1D<double> EVal;
  Mat.Allocate(L-1,L-1);
  DTMP.Allocate(L+L-1);
  ITMP.Allocate(1);
  EVal.Allocate(L-1);

  Array1D<unsigned int> IDMap;
  IDMap.Allocate(NB);
  for(unsigned int i=0;i<NB;++i)  IDMap[i]=i;
  double SEntr,TEntr,PEntr;
  unsigned int ExTrue=NB-8;

  MersenneTwister<StandardMT> RNG;
  RNG.Allocate();
  RNG.InitWithTime();

  cout.precision(20);
  for(unsigned int i=0;i<ExTrue;++i)    Sigma[IDMap[i]]=SigmaUpp[IDMap[i]];
  for(unsigned int i=ExTrue;i<NB;++i)   Sigma[IDMap[i]]=SigmaLow[IDMap[i]];
  PEntr=Entr(ID,Sigma,Mat,DTMP,ITMP,EVal);
  for(unsigned int nt=0,u,v,w;nt<1000;++nt) {
    u=static_cast<unsigned int>(RNG.Double()*ExTrue);
    v=static_cast<unsigned int>(RNG.Double()*(NB-ExTrue))+ExTrue;
    w=IDMap[u]; IDMap[u]=IDMap[v];  IDMap[v]=w;
    for(unsigned int i=0;i<ExTrue;++i)    Sigma[IDMap[i]]=SigmaUpp[IDMap[i]];
    for(unsigned int i=ExTrue;i<NB;++i)   Sigma[IDMap[i]]=SigmaLow[IDMap[i]];
    TEntr=Entr(ID,Sigma,Mat,DTMP,ITMP,EVal);
    //cout<<TEntr<<"\t"<<PEntr<<endl; getchar();
    if(RNG.Double()<exp(TEntr-PEntr)) PEntr=TEntr;
    else {
      w=IDMap[u]; IDMap[u]=IDMap[v];  IDMap[v]=w;
    }
  }
  SEntr=0;
  for(unsigned int nt=0,u,v,w;nt<10000;++nt) {
    u=static_cast<unsigned int>(RNG.Double()*ExTrue);
    v=static_cast<unsigned int>(RNG.Double()*(NB-ExTrue))+ExTrue;
    w=IDMap[u]; IDMap[u]=IDMap[v];  IDMap[v]=w;
    for(unsigned int i=0;i<ExTrue;++i)    Sigma[IDMap[i]]=SigmaUpp[IDMap[i]];
    for(unsigned int i=ExTrue;i<NB;++i)   Sigma[IDMap[i]]=SigmaLow[IDMap[i]];
    TEntr=Entr(ID,Sigma,Mat,DTMP,ITMP,EVal);
    if(RNG.Double()<exp(TEntr-PEntr)) PEntr=TEntr;
    else {
      w=IDMap[u]; IDMap[u]=IDMap[v];  IDMap[v]=w;
    }
    SEntr+=exp(-PEntr);
  }
  cout<<ExTrue<<"\t"<<log(10000.)-log(SEntr)<<endl;

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
