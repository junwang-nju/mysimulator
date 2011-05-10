
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
  int corr[4][4],ncorr;
  for(int i=0;i<4;++i)
  for(int j=0;j<4;++j)  corr[i][j]=0;
  ncorr=0;

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

  double p00[L],pall[L],tmprob;
  for(int i=0;i<L;++i)
    p00[i]=pall[i]=0.;
  long long int b00[L+1],b0a[L+1];
  for(int i=0;i<=L;++i) b00[i]=b0a[i]=0;

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
      //for(int i=0;i<L;++i) COut<<X[i]<<"  "<<Y[i]<<"  ";
      //COut<<Endl;

      /*
      for(int q=0;q<L1-1;++q) {
        corr[dirc[q]][dirc[q+1]]++;
        ncorr++;
      }
      */
          for(int q=0;q<L1-17;++q) {
            if(dirc[q]==0) {
              b0a[0]++;
              if(dirc[q+17]==0)  b00[0]++;
            }
          }
      for(int w=0;w<=30;++w) {
        tE=0;
        ofg=true;
        /*
        for(int z=0;z<L;++z) {
          rY=Y[z]+w;
          if((rY<0)||(rY>30)) { ofg=false; break; }
          if(rY==0) ++tE;
        }
        if(ofg) EH[tE]++;
        */
        if(ofg) {
          /*
          for(int q=0;q<L1-17;++q) {
            if(dirc[q]==0) {
              b0a[tE]++;
              if(dirc[q+17]==0)  b00[tE]++;
            }
          }
          */
          /*
          if(tE>16) {
            //cout<<tE;
            //for(int q=0;q<L1;++q) cout<<'\t'<<dirc[q];
            //cout<<endl;
            //for(int q=0;q<L1-1;++q) {
            //  corr[dirc[q]][dirc[q+1]]++;
            //  ncorr++;
            //}
            tmprob=exp(-tE/1.5);
            //tmprob=1.;
            //for(int y=1;y<L1-2;++y) {
            { int y=1;
              for(int q=0;q<L1-y;++q) {
                if((dirc[q]==0)&&(dirc[q+y]==0))  p00[y]+=tmprob;
                if(dirc[q]==0) pall[y]+=tmprob;
              }
            }
          }
          */
        }
      }
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
  for(int i=0;i<L+1;++i)
    cout<<i<<"\t"<<EH[i]<<endl;
  //cout<<NS<<endl;
  //for(int i=0;i<4;++i) {
  //  for(int j=0;j<4;++j) 
  //    cout<<i<<"\t\t"<<j<<"\t\t"<<corr[i][j]/(ncorr+0.)<<endl;
  //}
  //for(int q=1;q<L;++q)
  //  cout<<q<<"\t\t"<<p00[q]/pall[q]<<endl;
  for(int i=0;i<=L;++i)
    cout<<i<<"\t\t"<<b00[i]<<"\t\t"<<b0a[i]<<endl;
  return 0;
}

