
#include "chain/node/allocate.h"
#include "chain/node/copy.h"
#include "chain/node/refer.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {

  ChainNode<int>  Nd,Nd2;

  cout<<endl;
  allocate(Nd);
  Nd.content()=5;
  cout<<"Content of Chain Node is: "<<Nd.content()<<endl;
  imprint(Nd2,Nd);
  Nd2.content()=8;
  cout<<"Content of Chain Node is: "<<Nd2.content()<<endl;
  cout<<"Access Chain Node through () operator: "<<Nd()<<endl;

  cout<<endl;
  ChainNode<int> Nd3;
  cout<<"Validity of Allocated Chain Node: "<<IsValid(Nd)<<endl;
  cout<<"Validity of un-Allocated Chain Node: "<<IsValid(Nd3)<<endl;
  release(Nd2);
  cout<<"Validity after release: "<<IsValid(Nd2)<<endl;

  cout<<endl;
  allocate(Nd2);
  Nd2()=9;
  copy(Nd,Nd2);
  cout<<"The content of copied Node is: "<<Nd()<<endl;

  cout<<endl;
  refer(Nd3,Nd);
  cout<<"content of referred Chain Node: "<<Nd3()<<endl;

  cout<<Nd.parent.flag<<endl;

  return 0;
}

