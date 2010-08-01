
#include "vector.h"
#include <cstdio>
#include <iostream>
using namespace std;

double E(const Vector<int>& X, const Vector<int>& Y) {
  assert(X.size==Y.size);
  unsigned int n=X.size;
  double e=0;
  for(unsigned int i=0;i<n;++i)
  for(unsigned int j=i+3;j<n;++j)
    if(abs(X[i]-X[j])+abs(Y[i]-Y[j])==1)  e+=-1.;
  e+=0.0*abs(X[n-1]-X[0]);
  return e;
}

int main() {
  unsigned int L=16;
  unsigned int L1=L-1;

  Vector<int> dirc;
  Vector<int> X,Y;
  unsigned int YTurnHead,runHead;
  bool incflag;

  allocate(dirc,L1);
  allocate(X,L);
  allocate(Y,L);
  X[0]=0;     Y[0]=0;
  for(unsigned int i=0;i<L1;++i)  dirc[i]=-1;
  dirc[0]=0;
  YTurnHead=0;
  runHead=0;

  unsigned int NS=0;
  Vector<unsigned int> Hist;
  allocate(Hist,10);
  int rX,rY;
  do {
    ++runHead;
    rX=X[runHead-1];
    rY=Y[runHead-1];
    switch(dirc[runHead-1]) {
      case 0: ++rX;  break;
      case 1: ++rY;  break;
      case 2: --rY;  break;
      case 3: --rX;  break;
    };
    incflag=true;
    X[runHead]=rX;  Y[runHead]=rY;
    for(int i=runHead-2;i>=0;i-=2)
      if((X[i]==rX)&&(Y[i]==rY)) { incflag=false; break; }
    if(incflag&&(runHead==L1)) {
      if(YTurnHead==0)  YTurnHead=L1;
      ++Hist[static_cast<unsigned int>(-E(X,Y)+0.5)];
      ++NS;
    }
    if(runHead==L1) incflag=false;
    if(!incflag)    --runHead;
    if(YTurnHead>runHead) YTurnHead=runHead;
    ++dirc[runHead];
    if((dirc[runHead]>1)&&(YTurnHead==runHead)) dirc[runHead]=4;
    while(dirc[runHead]>3) {
      dirc[runHead]=-1;
      --runHead;
      if(runHead<1) break;
      if(YTurnHead>runHead) YTurnHead=runHead;
      ++dirc[runHead];
      if((dirc[runHead]>1)&&(YTurnHead==runHead)) dirc[runHead]=4;
    }
  } while(runHead>=1);
  cout<<NS<<endl;
  for(unsigned int i=0;i<Hist.size;++i) cout<<i<<"\t"<<Hist[i]<<endl;
  
  return 0;
}

