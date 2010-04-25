
#include "chain.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  Chain<int> C;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(C);
  cout<<C.root->child->parent<<endl;
  cout<<endl;

  cout<<"Test -- add items (node and constant)"<<endl;
  ChainNode<int> nd;
  allocate(nd);
  nd()=18;
  append(C,nd);
  append(C,58);
  append(C,79,Allocated);
  cout<<*(C.root->child->content)<<endl;
  cout<<*(C.root->child->child->content)<<endl;
  cout<<*(C.root->child->child->child->content)<<endl;
  cout<<endl;

  cout<<"Test -- copy from another Chain"<<endl;
  Chain<int> C2;
  assign(C2,C);
  cout<<*(C2.root->child->content)<<endl;
  cout<<*(C2.root->child->child->content)<<endl;
  cout<<*(C2.root->child->child->child->content)<<endl;
  cout<<endl;

  cout<<"Test -- check whether inside Chain"<<endl;
  cout<<In(C2,nd)<<endl;
  cout<<In(C,nd)<<endl;
  cout<<endl;

  cout<<"Test -- remove a node"<<endl;
  remove(C2,C2.root->child->child);
  cout<<*(C2.root->child->content)<<endl;
  cout<<*(C2.root->child->child->content)<<endl;
  cout<<endl;

  cout<<"Test -- release"<<endl;
  release(C2);
  cout<<C2.root<<"\t"<<C2.head<<endl;
  cout<<endl;

  cout<<"Test -- refer operation"<<endl;
  refer(C2,C);
  cout<<*(C2.root->child->content)<<endl;
  cout<<*(C2.root->child->child->content)<<endl;
  cout<<*(C2.root->child->child->child->content)<<endl;
  cout<<endl;

  return 1;
}

