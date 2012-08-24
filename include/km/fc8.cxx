
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

#include "array2d-numeric/interface.h"
using namespace mysimulator;

int main(int argc, char** argv) {
  if(argc<2) return 0;
  const unsigned int N=atoi(argv[1]);
  Array2DNumeric<double> X;
  ArrayNumeric<int> FG;
  ArrayNumeric<double> Dsp;
  X.Allocate(N,3);
  FG.Allocate(N);
  Dsp.Allocate(3);
  double T;
  ifstream ifs;
  ifs.open("2");
  for(unsigned int i=0;i<N;++i)
    ifs>>T>>X[i][0]>>X[i][1]>>X[i][2];

  int NX,NC;
  FG.Fill(-1);
  FG[0]=1;
  NX=0;
  while(true){ 
    for(unsigned int i=0;i<N;++i) {
      if(FG[i]>0) continue;
      Dsp.Copy(X[i]);
      Dsp.NegShift(X[NX]);
      T=Dsp.Norm();
      if(T<0.1) FG[i]=FG[NX];
    }
    NC=0;
    for(unsigned int i=0;i<N;++i)
      if(FG[i]==-1) { FG[i]=FG[NX]+1; NX=i; NC=1; break; }
    if(NC==0) break;
  }

  NC=FG[NX];
  for(int k=1;k<=NC;++k) {
    NX=0;
    for(unsigned int i=0;i<N;i++)
      if(FG[i]==k)  { cout<<X[i][0]<<'\t'<<X[i][1]<<'\t'<<X[i][2]<<endl; NX++; }
    cout<<"==========  Group "<<k<<"  ==============  "<<NX<<endl;
  }

  cout<<endl;
  for(int k=1;k<=NC;++k) {
    Dsp.Fill(0);
    NX=0;
    for(unsigned int i=0;i<N;++i)
      if(FG[i]==k) { Dsp.Shift(X[i]); ++NX; }
    cout<<"==========  Group "<<k<<"  ==============  "<<NX<<endl;
    Dsp.Scale(1./NX);
    cout<<Dsp[0]<<"\t"<<Dsp[1]<<"\t"<<Dsp[2]<<endl;
  }
  return 0;
}

