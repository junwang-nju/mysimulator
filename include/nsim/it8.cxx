
#include "array/2d/fill.h"
#include "array/1d/copy.h"
#include "random/mt/interface.h"
#include "matrix/rectangle/eigen-analysis.h"
using namespace mysimulator;

#include <iostream>
#include <cmath>
using namespace std;

double Entropy(const Array2D<unsigned int>& ID,const Array1D<double>& Sigma,
               MatrixRectangle<double>& Mat,Array1D<double>& DTMP,
               Array1D<int>& ITMP,Array1D<double>& EVal) {
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
  return -1.5*entropy;
}

bool IsFlat(const Array1D<double>& Hist, const double& low) {
  double avHist,nHist;
  avHist=nHist=0.;
  for(unsigned int i=0;i<Hist.Size();++i)
    if(Hist[i]>0.01) {
      avHist+=Hist[i];
      nHist+=1.;
    }
  avHist/=nHist;
  avHist*=low;
  bool mFG=true;
  for(unsigned int i=0;i<Hist.Size();++i)
    if((Hist[i]>0.01)&&(Hist[i]<avHist))  { mFG=false; break; }
  return mFG;
}

int main() {
  const unsigned int L=7;
  const unsigned int NB=(L*(L-1))/2;

  Array2D<unsigned int> ID;
  Array1D<double> SigmaUpp,SigmaLow;
  ID.Allocate(NB,2);
  SigmaUpp.Allocate(NB);
  SigmaLow.Allocate(NB);
  for(unsigned int i=0,n=0;i<L;++i)
  for(unsigned int j=i+1;j<L;++j,++n) {
    ID[n][0]=i; ID[n][1]=j;
    if(j-i==1)  { SigmaUpp[n]=1.1;  SigmaLow[n]=0.9; }
    else        { SigmaUpp[n]=100;  SigmaLow[n]=0.9; }
  }
  SigmaUpp[L-2]=1.1;
  SigmaLow[L-2]=0.9;

  MatrixRectangle<double> Mat;
  Array1D<double> DTMP,EVal;
  Array1D<int> ITMP;
  Mat.Allocate(L-1,L-1);
  DTMP.Allocate(L+L-1);
  ITMP.Allocate(1);
  EVal.Allocate(L-1);

  Array1D<double> Sigma;
  Array1D<unsigned int> Map;
  double SEntr,TEntr,PEntr,dstep;
  MersenneTwister<StandardMT> RNG;
  Array1D<double> Dens,Hist;
  unsigned int Level,nSpec;
  Sigma.Allocate(NB);
  Map.Allocate(NB);
  RNG.Allocate();
  RNG.InitWithTime();
  assert(Entropy(ID,SigmaUpp,Mat,DTMP,ITMP,EVal)<0);
  TEntr=-Entropy(ID,SigmaLow,Mat,DTMP,ITMP,EVal);
  nSpec=1000*static_cast<unsigned int>(TEntr+1);
  Dens.Allocate(nSpec);
  Hist.Allocate(nSpec);

  Array1D<double> LEntr;
  LEntr.Allocate(NB+1);

  assert(NB>=6);
  cout.precision(20);

  LEntr[0]=Entropy(ID,SigmaLow,Mat,DTMP,ITMP,EVal);
  SEntr=0;
  for(unsigned int i=0;i<NB;++i) {
    Copy(Sigma,SigmaLow,NB);
    Sigma[i]=SigmaUpp[i];
    SEntr+=exp(Entropy(ID,Sigma,Mat,DTMP,ITMP,EVal));
  }
  LEntr[1]=log(SEntr)-log(NB);
  SEntr=0;
  PEntr=0;
  for(unsigned int i=0;i<NB;++i)
  for(unsigned int j=i+1;j<NB;++j) {
    Copy(Sigma,SigmaLow,NB);
    Sigma[i]=SigmaUpp[i];
    Sigma[j]=SigmaUpp[j];
    SEntr+=exp(Entropy(ID,Sigma,Mat,DTMP,ITMP,EVal));
    PEntr+=1.;
  }
  LEntr[2]=log(SEntr)-log(PEntr);
  cout<<0<<"\t"<<LEntr[0]<<endl;
  cout<<1<<"\t"<<LEntr[1]<<endl;
  cout<<2<<"\t"<<LEntr[2]<<endl;

  for(Level=3;Level<=NB-3;++Level) {

    for(unsigned int i=0;i<NB;++i)  Map[i]=i;
    dstep=1.;
    Fill(Dens,0.,nSpec);
    Fill(Hist,0.,nSpec);
    for(unsigned int i=0;i<Level;++i)   Sigma[Map[i]]=SigmaUpp[Map[i]];
    for(unsigned int i=Level;i<NB;++i)  Sigma[Map[i]]=SigmaLow[Map[i]];
    PEntr=Entropy(ID,Sigma,Mat,DTMP,ITMP,EVal);
    while(dstep>1e-3) {
      for(unsigned int nt=0,u,v,w;nt<10000;++nt) {
        u=static_cast<unsigned int>(RNG.Double()*Level);
        v=static_cast<unsigned int>(RNG.Double()*(NB-Level))+Level;
        w=Map[u]; Map[u]=Map[v];  Map[v]=w;
        Sigma[Map[u]]=SigmaUpp[Map[u]];
        Sigma[Map[v]]=SigmaLow[Map[v]];
        TEntr=Entropy(ID,Sigma,Mat,DTMP,ITMP,EVal);
        if(RNG.Double()<exp(Dens[static_cast<int>(-PEntr*1000)]-
                            Dens[static_cast<int>(-TEntr*1000)]))
          PEntr=TEntr;
        else {
          w=Map[u]; Map[u]=Map[v];  Map[v]=w;
          Sigma[Map[u]]=SigmaUpp[Map[u]];
          Sigma[Map[v]]=SigmaLow[Map[v]];
        }
        Hist[static_cast<int>(-PEntr*1000)]+=1.;
        Dens[static_cast<int>(-PEntr*1000)]+=dstep;
      }
      if(IsFlat(Hist,0.9))  { dstep*=0.5; Fill(Hist,0.,nSpec); }
    }

    TEntr=1e10;
    for(unsigned int i=0;i<nSpec;++i)
      if((Dens[i]>1e-8)&&(Dens[i]<TEntr)) TEntr=Dens[i];
    SEntr=PEntr=0;
    for(unsigned int i=0;i<nSpec;++i)
      if(Dens[i]>1e-8) {
        dstep=Dens[i]-TEntr;
        SEntr+=exp(dstep+i*(-0.001));
        PEntr+=exp(dstep);
      }
    LEntr[Level]=log(SEntr)-log(PEntr);
    cout<<Level<<"\t"<<LEntr[Level]<<endl;
  }
  SEntr=0;
  PEntr=0;
  for(unsigned int i=0;i<NB;++i)
  for(unsigned int j=i+1;j<NB;++j) {
    Copy(Sigma,SigmaUpp,NB);
    Sigma[i]=SigmaLow[i];
    Sigma[j]=SigmaLow[j];
    SEntr+=exp(Entropy(ID,Sigma,Mat,DTMP,ITMP,EVal));
    PEntr++;
  }
  LEntr[NB-2]=log(SEntr)-log(PEntr);
  SEntr=0;
  for(unsigned int i=0;i<NB;++i) {
    Copy(Sigma,SigmaUpp,NB);
    Sigma[i]=SigmaLow[i];
    SEntr+=exp(Entropy(ID,Sigma,Mat,DTMP,ITMP,EVal));
  }
  LEntr[NB-1]=log(SEntr)-log(NB);
  LEntr[NB]=Entropy(ID,SigmaUpp,Mat,DTMP,ITMP,EVal);
  cout<<NB-2<<"\t"<<LEntr[NB-2]<<endl;
  cout<<NB-1<<"\t"<<LEntr[NB-1]<<endl;
  cout<<NB<<"\t"<<LEntr[NB]<<endl;

  SEntr=0;
  if(NB&1) PEntr=-1;
  TEntr=0;
  for(unsigned int i=0;i<=NB;++i) {
    if((i!=0)&&(i!=NB)) TEntr+=log(NB-i)-log(i);
    SEntr+=PEntr*exp(LEntr[i]+TEntr);
    PEntr*=-1;
  }
  cout<<log(SEntr)<<endl;

  return 0;
}

