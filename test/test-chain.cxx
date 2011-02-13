
#include "data/basic/chain.h"
#include "data/basic/console-output.h"
using namespace std;

int main() {
  COut<<"Test -- initialize"<<Endl;
  Chain<int> C;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(C);
  COut<<C.root->child->parent<<Endl;
  COut<<Endl;

  COut<<"Test -- add items (node and constant)"<<Endl;
  ChainNode<int> nd;
  allocate(nd);
  nd()=18;
  append(C,nd);
  append(C,58);
  append(C,79,Allocated);
  COut<<*(C.root->child->content)<<Endl;
  COut<<*(C.root->child->child->content)<<Endl;
  COut<<*(C.root->child->child->child->content)<<Endl;
  COut<<Endl;

  COut<<"Test -- copy from another Chain"<<Endl;
  Chain<int> C2;
  copy(C2,C);
  COut<<*(C2.root->child->content)<<Endl;
  COut<<*(C2.root->child->child->content)<<Endl;
  COut<<*(C2.root->child->child->child->content)<<Endl;
  COut<<Endl;

  COut<<"Test -- check whether inside Chain"<<Endl;
  COut<<In(C2,nd)<<Endl;
  COut<<In(C,nd)<<Endl;
  COut<<Endl;

  COut<<"Test -- remove a node"<<Endl;
  remove(C2,C2.root->child->child);
  COut<<*(C2.root->child->content)<<Endl;
  COut<<*(C2.root->child->child->content)<<Endl;
  COut<<Endl;

  COut<<"Test -- release"<<Endl;
  release(C2);
  COut<<C2.root<<"\t"<<C2.head<<Endl;
  COut<<Endl;

  COut<<"Test -- refer operation"<<Endl;
  refer(C2,C);
  COut<<*(C2.root->child->content)<<Endl;
  COut<<*(C2.root->child->child->content)<<Endl;
  COut<<*(C2.root->child->child->child->content)<<Endl;
  COut<<Endl;

  return 1;
}

