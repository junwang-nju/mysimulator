
#include "data/basic/btree.h"
#include "operation/basic/util.h"
#include "data/basic/console-output.h"
using namespace std;

int main() {
  COut<<"Test -- create a binary tree"<<Endl;
  BTree<int,double> bt;
  COut<<Endl;

  COut<<"Test -- insert with key and value"<<Endl;
  insert(bt,5,6.5);
  insert(bt,3,3.5);
  insert(bt,1,1.5);
  insert(bt,4,4.5);
  insert(bt,9,9.5);
  COut<<*(bt.root->key)<<"\t"<<*(bt.root->value)<<Endl;
  COut<<*(bt.root->left->key)<<"\t"<<*(bt.root->left->value)<<Endl;
  COut<<*(bt.root->right->key)<<"\t"<<*(bt.root->right->value)<<Endl;
  COut<<*(bt.root->left->left->key)<<"\t"<<*(bt.root->left->left->value)<<Endl;
  COut<<*(bt.root->left->right->key)<<"\t"<<*(bt.root->left->right->value)<<Endl;
  insert(bt,4,4.2);
  COut<<*(bt.root->left->right->key)<<"\t"<<*(bt.root->left->right->value)<<Endl;
  COut<<Endl;

  COut<<"Test -- get value"<<Endl;
  COut<<*(get(bt,3))<<Endl;
  COut<<get(bt,8)<<Endl;
  COut<<Endl;

  COut<<"Test -- get node"<<Endl;
  COut<<*(getNode(bt,3)->left->key)<<"\t";
  COut<<*(getNode(bt,3)->left->value)<<Endl;
  COut<<Endl;

  COut<<"Test -- assign a tree"<<Endl;
  BTree<int,double> bt2;
  assign(bt2,bt);
  COut<<*(bt2.root->key)<<"\t"<<*(bt2.root->value)<<Endl;
  COut<<*(bt2.root->left->key)<<"\t"<<*(bt2.root->left->value)<<Endl;
  COut<<*(bt2.root->right->key)<<"\t"<<*(bt2.root->right->value)<<Endl;
  COut<<*(bt2.root->left->left->key)<<"\t"<<*(bt2.root->left->left->value)<<Endl;
  COut<<*(bt2.root->left->right->key)<<"\t"<<*(bt2.root->left->right->value)<<Endl;
  COut<<Endl;

  COut<<"Test -- remove node"<<Endl;
  removeNode(bt,4);
  COut<<bt.root->left->right<<Endl;
  removeNode(bt,bt.root);
  COut<<*(bt.root->key)<<"\t"<<*(bt.root->value)<<Endl;
  COut<<Endl;

  COut<<"Test -- release a tree"<<Endl;
  release(bt2);
  COut<<bt2.root<<Endl;
  COut<<Endl;

  return 1;
}

