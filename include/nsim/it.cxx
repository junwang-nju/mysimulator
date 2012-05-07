
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
  return -entropy*3;
}

int main() {

  ifstream ifs("2ci2.cnt");

  unsigned int L;
  unsigned int NB;
  unsigned int NC;
  ifs>>L;
  ifs>>NC;
  NB=L-1+NC;

  Array2D<unsigned int> ID;
  Array1D<double> Sigma;
  Array1D<bool> FG;
  ID.Allocate(NB,2);
  Sigma.Allocate(NB);
  FG.Allocate(NB);
  for(unsigned int i=0;i<L-1;++i) {
    ID[i][0]=i;   ID[i][1]=i+1;   Sigma[i]=3.8;
  }
  for(unsigned int i=L-1;i<NB;++i) {
    ifs>>ID[i][0]>>ID[i][1]>>Sigma[i];
  }
  Fill(FG,true,NB);

  MatrixRectangle<double> Mat;
  Array1D<double> DTMP;
  Array1D<int> ITMP;
  Array1D<double> EVal;
  Mat.Allocate(L-1,L-1);
  DTMP.Allocate(L+L-1);
  ITMP.Allocate(1);
  EVal.Allocate(L-1);

  double NEntr=Entr(ID,Sigma,FG,Mat,DTMP,ITMP,EVal),TEntr,PEntr;
  int NOUT,TID;
  Array1D<double> REntr;
  Array1D<double> SEntr;
  REntr.Allocate(NC);
  SEntr.Allocate(NC);
  cout.precision(12);
  PEntr=0;
  NOUT=0;
  for(unsigned int g=0;g<NC;++g) {
    Fill(REntr,0.,NC);
    for(unsigned int i=L-1;i<NB;++i) {
      if(!FG[i])  { REntr[i-L+1]=-1; continue; }
      FG[i]=false;
      //cout<<i-L+1<<"\t"<<ID[i][0]<<"\t"<<ID[i][1]<<"\t";
      //cout<<Entr(ID,Sigma,FG,Mat,DTMP,ITMP,EVal)-NEntr<<endl;
      REntr[i-L+1]=Entr(ID,Sigma,FG,Mat,DTMP,ITMP,EVal)-NEntr;
      FG[i]=true;
    }
    TEntr=-10;
    TID=-1;
    for(unsigned int i=0;i<NC;++i)
      if(REntr[i]>TEntr)  { TEntr=REntr[i]; TID=i; }
    cout<<NOUT<<"\t"<<TID<<"\t"<<ID[TID+L-1][0]<<"\t"<<ID[TID+L-1][1];
    cout<<"\t"<<TEntr;
    cout<<"\t"<<TEntr-PEntr<<endl;
    FG[TID+L-1]=false;
    SEntr[NOUT]=TEntr;
    PEntr=TEntr;
    NOUT++;
  }

  return 0;
}
