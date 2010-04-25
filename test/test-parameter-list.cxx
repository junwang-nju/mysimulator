
#include "parameter-list.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initiate"<<endl;
  ParameterList PL;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(PL,3,2,7);
  unsigned int *ksize, *vsize;
  ksize=new unsigned int[9];
  vsize=new unsigned int[8];
  assign(ksize,3,9);
  assign(vsize,2,8);
  allocate(PL,ksize,vsize,8);
  allocate(PL,ksize,5,6);
  allocate(PL,4,vsize,5);
  release(ksize);
  release(vsize);
  cout<<endl;

  cout<<"Test -- input data by direct access"<<endl;
  for(unsigned int i=0;i<5;++i) {
    PL.key[i].index[0]=0;
    PL.key[i].index[1]=i;
    PL.key[i].index[2]=i+1;
    PL.key[i].index[3]=i+1;
    buildhash(PL.key[i]);
    PL.value[i][0].d=123.45*i+34.789;
    PL.value[i][1].u=12345+i*87;
  }
  updatetree(PL);
  cout<<endl;

  cout<<"Test -- access tree through []"<<endl;
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(PL[i])) cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- get value"<<endl;
  unsigned int *idx;
  idx=new unsigned int[4];
  idx[0]=0;
  idx[1]=1;
  idx[2]=2;
  idx[3]=2;
  const Vector<UniqueParameter> *pVU=get(PL,idx,4);
  cout<<(*pVU)[0].d<<endl;
  cout<<(*pVU)[1].u<<endl;
  release(idx);
  cout<<endl;

  cout<<"Test -- input from istream"<<endl;
  cin>>PL;
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(PL[i])) cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- assign from another parameter list"<<endl;
  ParameterList PL2;
  allocate(PL2,5,3,4);
  PL2=PL;
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(PL2[i])) cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(PL2,PL);
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(PL2[i])) cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(PL2);
  cout<<endl;

  cout<<"Test -- availability check"<<endl;
  cout<<IsAvailable(PL)<<endl;
  release(PL);
  cout<<IsAvailable(PL)<<endl;
  cout<<endl;

  return 1;
}

