
#include "data/basic/vector.h"
#include "operation/basic/vector-io.h"
#include "data/basic/console-output.h"
#include "operation/basic/vector-io.h"
#include <cstdio>
#include <iostream>
using namespace std;

void nextXYZ(const int X0, const int Y0, const int Z0,
             const int dirc, int& X, int& Y, int& Z) {
  X=X0;   Y=Y0;   Z=Z0;
  switch(dirc) {
    case 0: ++X;  break;
    case 1: ++Y;  break;
    case 2: ++Z;  break;
    case 3: --Z;  break;
    case 4: --Y;  break;
    case 5: --Z;  break;
  };
}

int main() {
  int L=18;
  int L1=L-1;

  Vector<int> dirc;
  Vector<int> X,Y,Z;
  int YTurnHead,runHead;
  bool incflag;

  allocate(dirc,L1);
  allocate(X,L);
  allocate(Y,L);
  allocate(Z,L);
  X[0]=0;     Y[0]=0;     Z[0]=0;
  for(int i=0;i<L1;++i)  dirc[i]=-1;
  dirc[0]=0;
  YTurnHead=0;
  runHead=0;

  Vector<unsigned long long> E(L+1);
  int rE;
  copy(E,0ULL);

  unsigned long long NS=0;
  int rX,rY,rZ;
  do {
    ++runHead;
    rX=X[runHead-1];
    rY=Y[runHead-1];
    rZ=Z[runHead-1];
    switch(dirc[runHead-1]) {
      case 0: ++rX;  break;
      case 1: ++rY;  break;
      case 2: ++rZ;  break;
      case 3: --rZ;  break;
      case 4: --rY;  break;
      case 5: --rX;  break;
    };
    incflag=true;
    X[runHead]=rX;  Y[runHead]=rY;    Z[runHead]=rZ;
    for(int i=runHead-2;i>=0;i-=2)
      if((X[i]==rX)&&(Y[i]==rY)) { incflag=false; break; }
    if(incflag&&(runHead==L1)) {
      ++NS;
      //COut<<dirc<<Endl;
      for(int u=0;u<30;++u) {
        rE=0;
        for(int v=0,w;v<L;++v) {
          w=Z[v]+u;
          if((w<0)||(w>30)) { rE=-1; break; }
          else if(w==0) ++rE;
        }
        if(rE>=0) E[rE]++;
      }
    }
    if(runHead==L1) incflag=false;
    if(!incflag)    --runHead;
    ++dirc[runHead];
    while(dirc[runHead]>5) {
      dirc[runHead]=-1;
      --runHead;
      if(runHead<1) break;
      ++dirc[runHead];
    }
  } while(runHead>0);

  cout<<"# "<<NS<<endl;
  for(int i=0;i<=L;++i) cout<<i<<"\t"<<E[i]<<endl;
  return 0;
}

