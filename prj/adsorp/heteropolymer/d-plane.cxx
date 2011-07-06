
#include "list/allocate.h"
#include "list/fill.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {
  const int L=16;
  Vector<int> dirc;
  Vector<int> X,Y;

  const unsigned int NC=9;
  const unsigned int CA[NC]={0,1,2, 4, 5,6, 8, 9,10};
  const unsigned int CB[NC]={7,6,5,11,10,9,15,14,13};
  //const unsigned int NC=16;
  //const unsigned int CA[NC]={0,1,2,3, 5, 6, 7, 8,10,11,12,13,15,16,17,18};
  //const unsigned int CB[NC]={9,8,7,6,14,13,12,11,19,18,17,16,24,23,22,21};
  const int D=6;
  const int NT=4;
  int En;
  int Ew;
  List<unsigned long long> Hist;
  Vector<unsigned int> sz;
  allocate(sz,NC+1);
  fill(sz,D*NT+1U);
  allocate(Hist,sz);
  fill(Hist,0ULL);

  const double DMin=0.0-1e-8;
  const double DMax=1.0-1e-8;
  double cX,cY;
  int minY,SYLow,SYUpp;

  allocate(dirc,L-1);
  allocate(X,L);
  allocate(Y,L);
  X[0]=Y[0]=0;
  fill(dirc,-1);

  int rX,rY,rHead;
  bool incflag,okfg;
  unsigned long long NS=0;
  dirc[0]=0;
  rHead=0;
  do {
    rHead++;
    rX=X[rHead-1];
    rY=Y[rHead-1];
    switch(dirc[rHead-1]) {
      case 0: ++rX; break;
      case 1: ++rY; break;
      case 2: --rY; break;
      case 3: --rX; break;
    }
    incflag=true;
    for(int i=rHead-2;i>=0;i-=2)
      if((X[i]==rX)&&(Y[i]==rY))  { incflag=false; break; }
    if(incflag) {
      X[rHead]=rX;  Y[rHead]=rY;
      if(rHead==L-1) {
        NS++;
        En=0;
        for(unsigned int i=0;i<NC;++i) {
          if(abs(X[CA[i]]-X[CB[i]])+abs(Y[CA[i]]-Y[CB[i]])==1)
            En++;
        }
        cX=cY=0;
        minY=0;
        for(int i=0;i<L;++i) {
          cX+=X[i]; cY+=Y[i];
          if(Y[i]<minY) minY=Y[i];
        }
        cX/=(L+0.);   cY/=(L+0.);
        if(cY<DMin-1e-8) {
          SYLow=static_cast<int>(DMin-1e-8-cY)+1;
          SYUpp=static_cast<int>(DMax-cY);
        } else if(cY>DMax+1e-8) {
          SYLow=-static_cast<int>(cY-DMin);
          SYUpp=-(static_cast<int>(cY-DMax-1e-8)+1);
        } else {
          SYLow=-static_cast<int>(cY-DMin);
          SYUpp=static_cast<int>(DMax-cY);
        }
        minY=-minY;
        okfg=true;
        if(SYUpp<minY)  okfg=false;
        else if(SYLow<minY) SYLow=minY;
        //cout<<"========="<<SYLow<<"\t"<<SYUpp<<"\t"<<minY<<endl;
        if(okfg) {
          for(int s=SYLow;s<=SYUpp;++s) {
            Ew=0;
            for(int i=0;i<NT;++i)
              if(Y[i]+s<D) Ew+=D-(Y[i]+s);
            Hist[En][Ew]++;
            if((En==0)&&(Ew==24))
              cout<<"-----  "<<NS<<"\t"<<cY+s<<endl;
            //cout<<En<<"\t"<<Ew<<endl;getchar();
          }
        }
        incflag=false;
      }
    }
    if(!incflag) --rHead;
    ++dirc[rHead];
    while(dirc[rHead]>3) {
      dirc[rHead]=-1;
      --rHead;
      if(rHead<0) break;
      ++dirc[rHead];
    }
  } while(rHead>=0);
  cout<<"# "<<NS<<endl;
  for(unsigned int i=0;i<=NC;++i)
  for(int j=0;j<=D*NT;++j) {
    if(Hist[i][j]>0)
      cout<<i<<"\t"<<j<<"\t"<<Hist[i][j]<<endl;
  }

  return 0;
}
