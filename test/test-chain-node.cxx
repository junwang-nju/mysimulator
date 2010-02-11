
#include "chain-node.h"
#include <iostream>
using namespace std;

int main() {
  ChainNode<int> nd,ndp,ndc;

  cout<<"Test -- assign of content"<<endl;
  nd.content()=1;
  ndp.content()=0;
  ndc.content()=2;
  cout<<endl;

  cout<<"Test -- assign of parent and child pointer"<<endl;
  nd.parent()=&ndp; ndp.child()=&nd;
  nd.child()=&ndc;  ndc.parent()=&nd;
  cout<<endl;

  cout<<"Test -- output of content"<<endl;
  cout<<nd.content()<<endl;
  cout<<endl;

  cout<<"Test -- output of parent/child content"<<endl;
  cout<<nd.parent()->content()<<endl;
  cout<<nd.child()->content()<<endl;
  cout<<endl;

  cout<<"Test -- assign alloc flag"<<endl;
  nd.SetChainAllocFlag(true);
  cout<<nd.IsAllocByChain()<<endl;
  cout<<endl;

  cout<<"Test -- add node before existed node"<<endl;
  ChainNode<int> ndn;
  ndn.content()=4;
  nd.add_before(ndn);
  cout<<nd.parent()->content()<<endl;
  cout<<ndn.child()->content()<<endl;
  cout<<endl;

  cout<<"Test -- remove node"<<endl;
  ndn.remove_self();
  cout<<nd.parent()->content()<<endl;
  cout<<endl;

  cout<<"Test -- clear node"<<endl;
  nd.clear();
  cout<<nd.parent()<<endl;
  cout<<endl;

  cout<<"Test -- assign node"<<endl;
  nd=ndn;
  cout<<nd.content()<<endl;
  cout<<endl;
  return 1;
}

