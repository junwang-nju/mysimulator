
#include "list/allocate.h"
#include "list/fill.h"
#include "list/io.h"
using namespace mysimulator;

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define LOOP  for(int k=0;k<D;++k) {\
                TCT=CT[0];  for(int i=1;i<D;++i)  TCT=TCT*(NT+1)+CT[i];\
                if(NTMap[TCT]==-1) {\
                  NTMap[TCT]=CTID;\
                  for(int i=0;i<D;++i)  Shp[CTID][i]=CT[i];\
                  CTID++;\
                }\
                for(int i=D-1;i>0;--i) CT[i]=CT[i-1]; CT[0]=0;\
              }

int main() {
  const int NMotif=80;
  const int D=6;
  const int NT=5;
  int CT[D],TCT,CTID;
  int NTType;
  NTType=1;
  for(int i=0;i<D;++i)  NTType*=(NT+1);
  Vector<int> NTMap;
  allocate(NTMap,NTType);
  fill(NTMap,-1);

  List<int> Shp;
  Vector<unsigned int> sz;
  allocate(sz,NMotif);
  fill(sz,D+0U);
  allocate(Shp,sz);

  CTID=0;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=5;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=4;  CT[1]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=3;  CT[1]=2;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=3;  CT[1]=1;  CT[2]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=2;  CT[1]=3;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=2;  CT[1]=2;  CT[2]=1;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
  CT[0]=2;  CT[1]=1;  CT[2]=2;
  LOOP;
  for(int i=0;i<D;++i) CT[i]=0;
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

  ifstream ifs("case-25");
  int Y,En,Mode;
  double E;
  unsigned long long Nm;
  double F[17];
  for(int i=0;i<17;++i) F[i]=0;
  for(int i=0;i<10375;++i) {
    ifs>>Y>>En>>Mode>>Nm; 
    //cout<<Y<<"\t"<<En<<"\t"<<Mode<<"\t"<<Nm<<endl; getchar();
    if(Y==6) {
      E=En;
      for(int k=0;k<D;++k)  E+=Shp[Mode][k]*(D-k)*5.8;
      if((En==15)||(En==16)) {
      cout<<Y<<"\t"<<En<<"\t"<<E<<endl;getchar(); }
      F[En]+=Nm*exp(E/0.68);
    }
  }
  for(int i=0;i<=16;++i)
    cout<<i<<"\t"<<-log(F[i])<<endl;
  return 0;
}

