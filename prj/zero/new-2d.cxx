
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
  int L=18;
  int L1=L-1;

  Vector<int> dirc;
  Vector<int> X,Y;
  Vector<long long int> EH;
  int YTurnHead,runHead,tE;
  bool incflag,ofg;
  Vector<Vector<unsigned long long> > dStat;

  allocate(dirc,L1);
  allocate(X,L);
  allocate(Y,L);
  X[0]=0;     Y[0]=0;
  for(int i=0;i<L1;++i)  dirc[i]=-1;
  dirc[0]=0;
  YTurnHead=0;
  runHead=0;

  allocate(EH,L+1);
  for(int i=0;i<L+1;++i)  EH[i]=0;
  allocate(dStat,L1);
  for(int i=0;i<L1;++i)   allocate(dStat[i],4);
  for(int i=0;i<L1;++i)   copy(dStat[i],0);

  int maxX,minX,maxY,minY;
  int nMaxX,nMinX,nMaxY,nMinY;

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
      ++NS;
      for(int w=0;w<L1;++w)
        dStat[w][dirc[w]]++;
      maxX=-L-1;  minX=L+1;
      maxY=-L-1;  minY=L+1;
      nMaxX=0;    nMinX=0;
      nMaxY=0;    nMinY=0;
      for(int w=0;w<L;++w) {
        if(maxX<X[w]) { maxX=X[w]; nMaxX=1; }
        else if(maxX==X[w]) { nMaxX++; }
        if(minX>X[w]) { minX=X[w]; nMinX=1; }
        else if(minX==X[w]) { ++nMinX; }
        if(maxY<Y[w]) { maxY=Y[w]; nMaxY=1; }
        else if(maxY==Y[w]) { nMaxY++; }
        if(minY>Y[w]) { minY=Y[w]; nMinY=1; }
        else if(minY==Y[w]) { ++nMinY; }
      }
      //assume MaxY-MinY<30 and MaxX-MinX<30;
      EH[nMinY]++;  // along x
      EH[nMaxY]++;  // along -x;
      EH[nMinX]++;  // along y
      EH[nMaxX]++;  // along -y
      EH[0]+=(30-(maxY-minY))*2;
      EH[0]+=(30-(maxX-minX))*2;
    }
    if(runHead==L1) incflag=false;
    if(!incflag)    --runHead;
    ++dirc[runHead];
    while(dirc[runHead]>3) {
      dirc[runHead]=-1;
      --runHead;
      if(runHead<1) break;
      ++dirc[runHead];
    }
  } while(runHead>0);
  //cout<<NS<<endl;
  //for(int i=0;i<L+1;++i)
  //  cout<<i<<"\t"<<EH[i]<<endl;
  for(int i=0;i<L1;++i) {
    cout<<i;
    for(int k=0;k<4;++k)  cout<<"\t"<<dStat[i][k];
    cout<<endl;
  }
  return 0;
}

