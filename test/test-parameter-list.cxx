
#include "parameter-list.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initiate"<<endl;
  ParameterList PL;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(PL,3,2,7);
  Vector<unsigned int> ksize, vsize;
  allocate(ksize,9);
  allocate(vsize,8);
  copy(ksize,3);
  copy(vsize,2);
  allocate(PL,ksize.data,vsize.data,8);
  allocate(PL,ksize.data,5,6);
  allocate(PL,4,vsize.data,5);
  release(ksize);
  release(vsize);
  cout<<endl;

  cout<<"Test -- input data by direct access"<<endl;
  for(unsigned int i=0;i<5;++i) {
    PL.key[i][0]=0;
    PL.key[i][1]=i;
    PL.key[i][2]=i+1;
    PL.key[i][3]=i+1;
    PL.key[i].update();
    PL.value[i][0].d=123.45*i+34.789;
    PL.value[i][1].u=12345+i*87;
  }
  PL.update();
  cout<<endl;

  cout<<"Test -- access tree through []"<<endl;
  for(unsigned int i=0;i<0xFFFFU;++i) if(IsAvailable(PL[i])) cout<<i<<endl;
  cout<<endl;

  cout<<"Test -- get value"<<endl;
  Vector<unsigned int> idx;
  allocate(idx,4);
  idx[0]=0;
  idx[1]=1;
  idx[2]=2;
  idx[3]=2;
  const Vector<UniqueParameter> *pVU=get(PL,idx.data,4);
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
  copy(PL2,PL);
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

