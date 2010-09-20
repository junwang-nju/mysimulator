
#include "vector.h"
#include <cstdio>
#include <iostream>
using namespace std;

void nextXY(const int X0, const int Y0, const int Z0,
            const int dirc,
            int& X, int& Y, int& Z) {
  X=X0;   Y=Y0;   Z=Z0;
  switch(dirc) {
    case 0: ++X;  break;
    case 1: ++Y;  break;
    case 2: ++Z;  break;
    case 3: --Z;  break;
    case 4: --Y;  break;
    case 5: --X;  break;
  };
}

int main() {
  unsigned int L=12;
  unsigned int L1=L-1;

  Vector<int> dirc;
  Vector<int> X,Y,Z;
  unsigned int YTurnHead,ZTurnHead,runHead;
  bool incflag;

  allocate(dirc,L1);
  allocate(X,L);
  allocate(Y,L);
  allocate(Z,L);
  X[0]=0;     Y[0]=0;       Z[0]=0;
  for(unsigned int i=0;i<L1;++i)  dirc[i]=-1;
  dirc[0]=0;
  YTurnHead=0;
  ZTurnHead=0;
  runHead=0;

  unsigned long long int NS=0;
  int rX,rY,rZ;
  do {
    ++runHead;
    rX=X[runHead-1];
    rY=Y[runHead-1];
    rZ=Z[runHead-1];
    switch(dirc[runHead-1]) {
      case 0: ++rX;   break;
      case 1: ++rY;   break;
      case 2: ++rZ;   break;
      case 3: --rZ;   break;
      case 4: --rY;   break;
      case 5: --rX;   break;
    };
    incflag=true;
    X[runHead]=rX;  Y[runHead]=rY;  Z[runHead]=rZ;
    for(int i=runHead-2;i>=0;i-=2)
      if((X[i]==rX)&&(Y[i]==rY)&&(Z[i]==rZ)) { incflag=false; break; }
    if(incflag&&(runHead==L1)) {
      if(YTurnHead==0)  YTurnHead=L1-1;
      if(ZTurnHead==0)  ZTurnHead=L1-1;
      cout<<dirc<<endl;
      ++NS;
    }
    if(runHead==L1) incflag=false;
    if(!incflag)    --runHead;
    if(YTurnHead>runHead) { YTurnHead=runHead;  ZTurnHead=0; }
    else if((ZTurnHead>runHead)&&(dirc[runHead]==1))  ZTurnHead=runHead;
    ++dirc[runHead];
    if((dirc[runHead]==3)&&(ZTurnHead==runHead)) { dirc[runHead]=4; ZTurnHead=0; }
    else if((dirc[runHead]>1)&&(YTurnHead==runHead)) dirc[runHead]=6;
    while(dirc[runHead]>5) {
      dirc[runHead]=-1;
      --runHead;
      if(runHead<1) break;
      if(YTurnHead>runHead) { YTurnHead=runHead;  ZTurnHead=0; }
      else if((ZTurnHead>runHead)&&(dirc[runHead]==1))  ZTurnHead=runHead;
      ++dirc[runHead];
      if((dirc[runHead]==3)&&(ZTurnHead==runHead)) { dirc[runHead]++; ZTurnHead=0; }
      else if((dirc[runHead]>1)&&(YTurnHead==runHead)) dirc[runHead]=6;
    }
  } while(runHead>=1);
  cout<<NS<<endl;
  
  return 0;
}

