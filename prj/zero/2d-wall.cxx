
#include "data/basic/vector.h"
#include "operation/basic/vector-io.h"
#include "data/basic/console-output.h"
#include <cstdio>
#include <iostream>
using namespace std;

void nextXY(const int X0, const int Y0, const int dirc, int& X, int& Y) {
  X=X0;   Y=Y0;
  switch(dirc) {
    case 0: ++X;  break;
    case 1: ++Y;  break;
    case 2: --Y;  break;
    case 3: --X;  break;
  };
}

int main() {
  int L=16;
  int L1=L-1;

  Vector<int> dirc;
  Vector<int> X,Y;
  int YTurnHead,runHead;
  bool incflag;

  allocate(dirc,L1);
  allocate(X,L);
  allocate(Y,L);
  X[0]=0;     Y[0]=0;
  for(int i=0;i<L1;++i)  dirc[i]=-1;
  dirc[0]=0;
  YTurnHead=0;
  runHead=0;

  unsigned int NS=0;
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
      //if(YTurnHead==0)  YTurnHead=L1;
      ++NS;
      for(int i=0;i<L;++i) COut<<X[i]<<"  "<<Y[i]<<"  ";
      COut<<Endl;
    }
    if(runHead==L1) incflag=false;
    if(!incflag)    --runHead;
    //if(YTurnHead>runHead) YTurnHead=runHead;
    ++dirc[runHead];
    //if((dirc[runHead]>1)&&(YTurnHead==runHead)) dirc[runHead]=4;
    while(dirc[runHead]>3) {
      dirc[runHead]=-1;
      --runHead;
      if(runHead<0) break;
      //if(YTurnHead>runHead) YTurnHead=runHead;
      ++dirc[runHead];
      //if((dirc[runHead]>1)&&(YTurnHead==runHead)) dirc[runHead]=4;
    }
  } while(runHead>=0);
  cout<<NS<<endl;
  
  return 0;
}

