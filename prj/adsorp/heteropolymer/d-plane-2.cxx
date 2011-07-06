
#include "list/allocate.h"
#include "list/fill.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

#define LOOP  TCT=CT[0];  for(int i=1;i<D;++i)  TCT=TCT*(NT+1)+CT[i];\
              if(NTMap[TCT]==-1) { NTMap[TCT]=CTID; CTID++; }\
              for(int k=1;k<D;++k) {\
                for(int i=D-1;i>0;--i) CT[i]=CT[i-1]; CT[0]=0;\
                TCT=CT[0];  for(int i=1;i<D;++i)  TCT=TCT*(NT+1)+CT[i];\
                if(NTMap[TCT]==-1) { NTMap[TCT]=CTID; CTID++; }\
              }


int main() {
  //const int L=16;
  const int L=25;
  Vector<int> dirc;
  Vector<int> X,Y;

  //const int NC=9;
  //const unsigned int CA[NC]={0,1,2, 4, 5,6, 8, 9,10};
  //const unsigned int CB[NC]={7,6,5,11,10,9,15,14,13};
  const int NC=16;
  const unsigned int CA[NC]={0,1,2,3, 5, 6, 7, 8,10,11,12,13,15,16,17,18};
  const unsigned int CB[NC]={9,8,7,6,14,13,12,11,19,18,17,16,24,23,22,21};
  const int D=6;
  //const int NT=4;
  const int NT=5;
  int CT[D],TCT,CTID;
  int NTType;
  NTType=1;
  for(int i=0;i<D;++i)  NTType*=(NT+1);
  Vector<int> NTMap;
  allocate(NTMap,NTType);
  fill(NTMap,-1);
  CTID=0;
  for(int i=0;i<D;++i) CT[i]=0;
  //CT[0]=4;
  CT[0]=5;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  //CT[0]=3;  CT[1]=1;
  CT[0]=4;  CT[1]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  //CT[0]=2;  CT[1]=2;
  CT[0]=3;  CT[1]=2;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  //CT[0]=2;  CT[1]=1;  CT[2]=1;
  CT[0]=3;  CT[1]=1;  CT[2]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  //CT[0]=1;  CT[1]=3;
  CT[0]=2;  CT[1]=3;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  //CT[0]=1;  CT[1]=2;  CT[2]=1;
  CT[0]=2;  CT[1]=2;  CT[2]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  //CT[0]=1;  CT[1]=1;  CT[2]=2;
  CT[0]=2;  CT[1]=1;  CT[2]=2;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  //CT[0]=1;  CT[1]=1;  CT[2]=1;  CT[3]=1;
  CT[0]=2;  CT[1]=1;  CT[2]=1;  CT[3]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=1;  CT[1]=4;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=1;  CT[1]=3;  CT[2]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=1;  CT[1]=2;  CT[2]=2;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=1;  CT[1]=2;  CT[2]=1;  CT[3]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=1;  CT[1]=1;  CT[2]=3;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=1;  CT[1]=1;  CT[2]=2;  CT[3]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=1;  CT[1]=1;  CT[2]=1;  CT[3]=2;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=1;  CT[1]=1;  CT[2]=1;  CT[3]=1;  CT[4]=1;
  LOOP;
  TCT=0;
  if(NTMap[TCT]==-1) { NTMap[TCT]=CTID; CTID++; }

  int En;
  List<Vector<unsigned long long> > Hist;
  Vector<unsigned int> sz;
  allocate(sz,20);
  fill(sz,NC+1U);
  allocate(Hist,sz);
  for(int i=0;i<20;++i)
  for(int j=0;j<=NC;++j)
    allocate(Hist[i][j],CTID);
  fill(Hist,0ULL);

  double cX,cY;
  int minY;

  allocate(dirc,L-1);
  allocate(X,L);
  allocate(Y,L);
  X[0]=Y[0]=0;
  fill(dirc,-1);

  int rX,rY,rHead;
  bool incflag;
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
        for(int i=0;i<NC;++i) {
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
        minY=-minY;
        while(cY+minY<20) {
          for(int i=0;i<D;++i)  CT[i]=0;
          for(int i=0;i<NT;++i) if(Y[i]+minY<D) CT[Y[i]+minY]++;
          TCT=CT[0];  for(int i=1;i<D;++i)  TCT=TCT*(NT+1)+CT[i];
          //cout<<cY+minY<<endl;
          //cout<<En<<endl;
          //cout<<TCT<<endl;
          //cout<<NTMap[TCT]<<endl; cout<<"======="<<endl; getchar();
          Hist[static_cast<int>(cY+minY)][En][NTMap[TCT]]++;
          minY++;
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
  for(unsigned int i=0;i<20;++i)
  for(int j=0;j<=NC;++j)
  for(int k=0;k<CTID;++k) {
    if(Hist[i][j][k]>0)
      cout<<i<<"\t"<<j<<"\t"<<k<<"\t"<<Hist[i][j][k]<<endl;
  }

  return 0;
}
