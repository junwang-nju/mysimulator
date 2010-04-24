
#include "parameter-key.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- create a key"<<endl;
  ParameterKey K;
  cout<<endl;

  cout<<"Test -- allocate a key"<<endl;
  allocate(K,3);
  cout<<endl;

  cout<<"Test -- build hash"<<endl;
  K.index[0]=1;
  K.index[1]=100;
  K.index[2]=0;
  buildhash(K);
  cout<<K.hash[0]<<"\t"<<K.hash[1]<<"\t"<<K.hash[2]<<endl;
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  ParameterKey K2;
  allocate(K2,4);
  assign(K2,K);
  for(unsigned int i=0;i<K2.size;++i) cout<<K2.index[i]<<"  "; cout<<endl;
  cout<<K2.hash[0]<<"\t"<<K2.hash[1]<<"\t"<<K2.hash[2]<<endl;
  cout<<endl;

  cout<<"Test -- input from stream"<<endl;
  cin>>K;
  for(unsigned int i=0;i<K.size;++i) cout<<K.index[i]<<"  "; cout<<endl;
  cout<<K.hash[0]<<"\t"<<K.hash[1]<<"\t"<<K.hash[2]<<endl;
  cout<<endl;

  cout<<"Test -- compare"<<endl;
  cout<<compare(K,K2)<<endl;
  cout<<compare(K2,K)<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(K2);
  cout<<endl;

  return 1;
}

