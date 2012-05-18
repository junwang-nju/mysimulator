
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
  Array1D<double> Hist,Den;
  double avHist,nHist,f;
  bool mfg;
  Den.Allocate(20000);
  Hist.Allocate(20000);
  Fill(Den,0,20000);

  cout.precision(20);
  f=1.;
  for(unsigned int i=0;i<ExTrue;++i)    Sigma[IDMap[i]]=SigmaUpp[IDMap[i]];
  for(unsigned int i=ExTrue;i<NB;++i)   Sigma[IDMap[i]]=SigmaLow[IDMap[i]];
  PEntr=Entr(ID,Sigma,Mat,DTMP,ITMP,EVal);
  Fill(Hist,0,20000);
  while(f>1e-3) {
  for(unsigned int nt=0,u,v,w;nt<10000;++nt) {
    u=static_cast<unsigned int>(RNG.Double()*ExTrue);
    v=static_cast<unsigned int>(RNG.Double()*(NB-ExTrue))+ExTrue;
    w=IDMap[u]; IDMap[u]=IDMap[v];  IDMap[v]=w;
    for(unsigned int i=0;i<ExTrue;++i)    Sigma[IDMap[i]]=SigmaUpp[IDMap[i]];
    for(unsigned int i=ExTrue;i<NB;++i)   Sigma[IDMap[i]]=SigmaLow[IDMap[i]];
    TEntr=Entr(ID,Sigma,Mat,DTMP,ITMP,EVal);
    if(TEntr<-11.13) { Write(TEntr,"\n",IDMap,"\n"); getchar(); }
    if(RNG.Double()<exp(Den[-(int)(PEntr*1000)]-Den[-(int)(TEntr*1000)]))
      PEntr=TEntr;
    else {
      w=IDMap[u]; IDMap[u]=IDMap[v];  IDMap[v]=w;
    }
    Hist[-(int)(PEntr*1000)]+=1;
    Den[-(int)(PEntr*1000)]+=f;
  }
  avHist=0;
  nHist=0;
  for(unsigned int i=0;i<20000;++i)  if(Hist[i]>0) { avHist+=Hist[i]; nHist+=1; }
  avHist/=nHist;
  avHist*=0.9;
  mfg=true;
  for(unsigned int i=0;i<20000;++i)
    if(Hist[i]>0)
      if(Hist[i]<avHist) { mfg=false; break; }
  if(mfg) { f*=0.5; Fill(Hist,0.,20000); }
  }

  //for(unsigned int i=0;i<2000;++i) if(Hist[i]>0) cout<<i<<"\t"<<Hist[i]<<endl;
  
  for(unsigned int i=0;i<20000;++i) if(Den[i]>1) cout<<i<<"\t"<<Den[i]<<endl;
  TEntr=1e10;
  for(unsigned int i=0;i<20000;i++)
    if(Den[i]>1) TEntr=(Den[i]<TEntr?Den[i]:TEntr);
  cout<<"# "<<TEntr<<endl;
  SEntr=0;
  PEntr=0;
  for(unsigned int i=0;i<20000;++i) {
    if(Den[i]>1) {
      SEntr+=exp(Den[i]-TEntr+i*(-0.001));
      PEntr+=exp(Den[i]-TEntr);
    }
  }
  cout<<"# "<<log(SEntr)-log(PEntr)<<endl;

  /*
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
  */

  return 0;

}
