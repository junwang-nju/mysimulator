
#include "data/basic/chain-node.h"
#include "data/basic/console-output.h"
using namespace std;

int main() {
  COut<<"Test -- initialize"<<Endl;
  ChainNode<int> CN;
  COut<<Endl;

  COut<<"Test -- allocate"<<Endl;
  allocate(CN);
  CN()=5;
  COut<<Endl;

  COut<<"Test -- assign external parent and child"<<Endl;
  ChainNode<int> CNp,CNc;
  allocate(CNp);
  allocate(CNc);
  CNp()=4;
  CNc()=6;
  CN.parent=&CNp;
  CN.child=&CNc;
  CN.parentstate=Reference;
  CN.childstate=Reference;
  CNp.child=&CN;
  CNp.childstate=Reference;
  CNc.parent=&CN;
  CNc.parentstate=Reference;
  COut<<*(CN.parent->child->child->content)<<Endl;
  COut<<Endl;

  COut<<"Test -- content access"<<Endl;
  COut<<CNp()<<Endl;
  COut<<Endl;

  COut<<"Test -- insert a parent node"<<Endl;
  ChainNode<int> CNa;
  allocate(CNa);
  CNa()=34;
  add_parent(CNc,CNa);
  COut<<*(CN.child->content)<<"\t"<<*(CN.child->parent->content)<<Endl;
  COut<<*(CNc.parent->content)<<"\t"<<*(CNc.parent->child->content)<<Endl;
  COut<<Endl;

  COut<<"Test -- insert a content"<<Endl;
  add_parent(CNc,45);
  COut<<*(CN.child->child->content)<<"\t"<<*(CN.child->child->parent->content)<<Endl;
  COut<<*(CNc.parent->content)<<"\t"<<*(CNc.parent->child->content)<<Endl;
  add_parent(*(CNc.parent),85,Allocated);
  COut<<*(CN.child->child->content)<<"\t"<<*(CN.child->child->parent->content)<<Endl;
  COut<<*(CNc.parent->parent->content)<<"\t"<<*(CNc.parent->parent->child->content)<<Endl;
  COut<<Endl;

  COut<<"Test -- release node"<<Endl;
  release(*(CNc.parent));
  COut<<*(CN.child->child->content)<<"\t"<<*(CN.child->child->parent->content)<<Endl;
  COut<<*(CNc.parent->content)<<"\t"<<*(CNc.parent->child->content)<<Endl;
  COut<<*(CNc.parent->parent->content)<<"\t"<<*(CNc.parent->parent->child->content)<<Endl;
  COut<<Endl;

  COut<<"Test -- availability"<<Endl;
  COut<<IsAvailable(CN)<<Endl;
  release(CNp);
  COut<<IsAvailable(CNp)<<Endl;
  COut<<Endl;

  return 1;
}

