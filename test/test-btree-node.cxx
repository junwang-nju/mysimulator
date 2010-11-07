
#include "data/basic/btree-node.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- create a node of binary tree"<<endl;
  BTreeNode<int,double> bn;
  cout<<endl;

  cout<<"Test -- assign the pointers of key and value"<<endl;
  int key=2;
  double value=2.5;
  bn.key=&key;
  bn.value=&value;
  bn.keystate=Reference;
  bn.valuestate=Reference;
  cout<<endl;

  cout<<"Test -- read key and value"<<endl;
  cout<<*(bn.key)<<"\t\t"<<*(bn.value)<<endl;
  cout<<endl;

  cout<<"Test -- assign the parent, left, and right children"<<endl;
  int keyp=5;
  double valuep=1.5;
  bn.branch=Unassigned;
  bn.right=new BTreeNode<int,double>;
  bn.right->key=&keyp;      bn.right->keystate=Reference;
  bn.right->value=&valuep;  bn.right->valuestate=Reference;
  bn.right->branch=RightBranch;
  bn.right->parent=&bn;
  cout<<endl;

  cout<<"Test -- read parent and child information"<<endl;
  cout<<*(bn.right->parent->key)<<"\t\t"<<*(bn.right->parent->value)<<endl;
  cout<<*(bn.right->key)<<"\t\t"<<*(bn.right->value)<<endl;
  cout<<endl;

  cout<<"Test -- assign from another node"<<endl;
  BTreeNode<int,double> bnn;
  bnn=bn;
  cout<<*(bnn.key)<<"\t\t"<<*(bnn.value)<<endl;
  cout<<endl;

  cout<<"Test -- clear node"<<endl;
  release(bnn);
  release(*(bn.right));
  bn.right->parent=&bn;
  bn.right->branch=RightBranch;
  cout<<endl;

  return 1;
}

