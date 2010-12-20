
#include "data/derived/parameter-key.h"
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
  K[0]=1;
  K[1]=100;
  K[2]=0;
  K.update();
  cout<<K.hash[0]<<"\t"<<K.hash[1]<<"\t"<<K.hash[2]<<endl;
  cout<<endl;

  cout<<"Test -- assign"<<endl;
  ParameterKey K2;
  allocate(K2,4);
  copy(K2,K);
  cout<<K2<<endl;
  //for(unsigned int i=0;i<K2.size;++i) cout<<K2[i]<<"  "; cout<<endl;
  cout<<K2.hash[0]<<"\t"<<K2.hash[1]<<"\t"<<K2.hash[2]<<endl;
  cout<<endl;

  cout<<"Test -- input from stream"<<endl;
  cout<<K.hsize<<endl;
  cin>>K;
  cout<<K<<endl;
  //for(unsigned int i=0;i<K.size;++i) cout<<K.index[i]<<"  "; cout<<endl;
  cout<<K.hash[0]<<"\t"<<K.hash[1]<<"\t"<<K.hash[2]<<endl;
  cout<<endl;

  cout<<"Test -- compare"<<endl;
  cout<<compare(K,K2)<<endl;
  cout<<compare(K2,K)<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(K2);
  cout<<endl;

  cout<<"Test - availability check"<<endl;
  cout<<IsAvailable(K)<<endl;
  release(K);
  cout<<IsAvailable(K)<<endl;
  cout<<endl;

  return 1;
}

