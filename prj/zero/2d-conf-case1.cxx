
#include "vector.h"
#include "property-list.h"
#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

int main() {
  unsigned int L=30;
  unsigned int L1=L-1;

  PropertyList<int> RowAlign;
  PropertyList<int> ColumnAlign;
  Vector<unsigned int> sz;
  allocate(sz,L+L+1);
  assign(sz,L+L+1);
  allocate(RowAlign,sz);
  allocate(ColumnAlign,sz);
  assign(RowAlign,-1);
  assign(ColumnAlign,-1);

  Vector<int> dirc;
  Vector<int> X,Y;
  Vector<double> Ene;
  unsigned int YTurnHead,runHead;
  bool incflag;

  allocate(dirc,L1);
  allocate(X,L);
  allocate(Y,L);
  allocate(Ene,L);
  X[0]=L;     Y[0]=L;
  RowAlign[L][L]=0;
  ColumnAlign[L][L]=0;
  Ene[0]=0;
  for(unsigned int i=0;i<L1;++i)  dirc[i]=-1;
  dirc[0]=0;
  YTurnHead=0;
  runHead=0;

  unsigned int NS=0;
  Vector<unsigned int> Hist;
  allocate(Hist,30);
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
    incflag=(RowAlign[rX][rY]==-1?true:false);
    if(incflag) {
      Ene[runHead]=Ene[runHead-1]-1;
      if(RowAlign[rX][rY-1]!=-1)  Ene[runHead]+=1.;
      if(RowAlign[rX][rY+1]!=-1)  Ene[runHead]+=1.;
      if(ColumnAlign[rY][rX-1]!=-1)   Ene[runHead]+=1.;
      if(ColumnAlign[rY][rX+1]!=-1)   Ene[runHead]+=1.;
      if(runHead==L1) {
        if(YTurnHead==0)  YTurnHead=L1;
        ++Hist[static_cast<unsigned int>(Ene[L1]+0.5)];
        ++NS;
        incflag=false;
      } else {
        X[runHead]=rX;  Y[runHead]=rY;
        RowAlign[rX][rY]=runHead;
        ColumnAlign[rY][rX]=runHead;
      }
    }
    if(!incflag)    --runHead;
    if(YTurnHead>runHead) YTurnHead=runHead;
    ++dirc[runHead];
    if(dirc[runHead]+dirc[runHead-1]==3)  ++dirc[runHead];
    if((dirc[runHead]>1)&&(YTurnHead==runHead)) dirc[runHead]=4;
    while(dirc[runHead]>3) {
      dirc[runHead]=-1;
      RowAlign[X[runHead]][Y[runHead]]=-1;
      ColumnAlign[Y[runHead]][X[runHead]]=-1;
      --runHead;
      if(runHead<1) break;
      if(YTurnHead>runHead) YTurnHead=runHead;
      ++dirc[runHead];
      if(dirc[runHead]+dirc[runHead-1]==3)  ++dirc[runHead];
      if((dirc[runHead]>1)&&(YTurnHead==runHead)) dirc[runHead]=4;
    }
  } while(runHead>=1);
  cout<<NS<<endl;
  for(unsigned int i=0;i<Hist.size;++i) cout<<i<<"\t"<<Hist[i]<<endl;
  
  return 0;
}

