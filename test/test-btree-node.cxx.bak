
#include "data/basic/btree-node.h"
#include "data/basic/console-output.h"
using namespace std;

int main() {
  COut<<"Test -- create a node of binary tree"<<Endl;
  BTreeNode<int,double> bn;
  COut<<Endl;

  COut<<"Test -- assign the pointers of key and value"<<Endl;
  int key=2;
  double value=2.5;
  bn.key=&key;
  bn.value=&value;
  bn.keystate=Reference;
  bn.valuestate=Reference;
  COut<<Endl;

  COut<<"Test -- read key and value"<<Endl;
  COut<<*(bn.key)<<"\t\t"<<*(bn.value)<<Endl;
  COut<<Endl;

  COut<<"Test -- assign the parent, left, and right children"<<Endl;
  int keyp=5;
  double valuep=1.5;
  bn.branch=Unassigned;
  bn.right=new BTreeNode<int,double>;
  bn.right->key=&keyp;      bn.right->keystate=Reference;
  bn.right->value=&valuep;  bn.right->valuestate=Reference;
  bn.right->branch=RightBranch;
  bn.right->parent=&bn;
  COut<<Endl;

  COut<<"Test -- read parent and child information"<<Endl;
  COut<<*(bn.right->parent->key)<<"\t\t"<<*(bn.right->parent->value)<<Endl;
  COut<<*(bn.right->key)<<"\t\t"<<*(bn.right->value)<<Endl;
  COut<<Endl;

  COut<<"Test -- assign from another node"<<Endl;
  BTreeNode<int,double> bnn;
  bnn=bn;
  COut<<*(bnn.key)<<"\t\t"<<*(bnn.value)<<Endl;
  COut<<Endl;

  COut<<"Test -- clear node"<<Endl;
  release(bnn);
  release(*(bn.right));
  bn.right->parent=&bn;
  bn.right->branch=RightBranch;
  COut<<Endl;

  return 1;
}

