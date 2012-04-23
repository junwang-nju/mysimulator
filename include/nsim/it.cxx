
#include "matrix/rectangle/eigen-analysis.h"
#include "array/2d/fill.h"
#include "array/1d/io.h"
using namespace mysimulator;

#include <iostream>
#include <cmath>
using namespace std;

int main() {
  unsigned int L=100;
  unsigned int NB=L+1;

  Array2D<unsigned int> ID;
  Array1D<double> Sigma;
  ID.Allocate(NB,2);
  Sigma.Allocate(NB);
  for(unsigned int i=0;i<L-1;++i) {
    ID[i][0]=i;   ID[i][1]=i+1;   Sigma[i]=1.;
  }
  ID[L-1][0]=0;   ID[L-1][1]=L-1;   Sigma[L-1]=1.5;
  ID[L][0]=0;    ID[L][1]=2;      Sigma[L]=1.5;

  MatrixRectangle<double> Mat;
  Array1D<double> DTMP;
  Array1D<int> ITMP;
  Array1D<double> EVal;
  double tsig,entropy;
  Mat.Allocate(L-1,L-1);
  DTMP.Allocate(L+L-1);
  ITMP.Allocate(1);
  EVal.Allocate(L-1);
  Fill(Mat,0.);
  for(unsigned int i=0;i<NB;++i) {
    tsig=1./(Sigma[i]*Sigma[i]);
    for(unsigned int k=ID[i][0];k<ID[i][1];++k)
    for(unsigned int l=ID[i][0];l<ID[i][1];++l)
      Mat[k][l]+=tsig;
  }
  EigenValue(Mat,EVal,DTMP,ITMP);
  Write(EVal,"\n");

  entropy=0;
  for(unsigned int i=0;i<L-1;++i) entropy+=log(EVal[i]);
  entropy*=-3;
  cout<<entropy<<endl;

  return 0;
}
