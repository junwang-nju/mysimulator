
#include "btree.h"
#include "util.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- create a binary tree"<<endl;
  BTree<int,double> bt;
  cout<<endl;

  cout<<"Test -- insert with key and value"<<endl;
  insert(bt,5,6.5);
  insert(bt,3,3.5);
  insert(bt,1,1.5);
  insert(bt,4,4.5);
  insert(bt,9,9.5);
  cout<<*(bt.root->key)<<"\t"<<*(bt.root->value)<<endl;
  cout<<*(bt.root->left->key)<<"\t"<<*(bt.root->left->value)<<endl;
  cout<<*(bt.root->right->key)<<"\t"<<*(bt.root->right->value)<<endl;
  cout<<*(bt.root->left->left->key)<<"\t"<<*(bt.root->left->left->value)<<endl;
  cout<<*(bt.root->left->right->key)<<"\t"<<*(bt.root->left->right->value)<<endl;
  insert(bt,4,4.2);
  cout<<*(bt.root->left->right->key)<<"\t"<<*(bt.root->left->right->value)<<endl;
  cout<<endl;

  cout<<"Test -- get value"<<endl;
  cout<<*(get(bt,3))<<endl;
  cout<<get(bt,8)<<endl;
  cout<<endl;

  cout<<"Test -- get node"<<endl;
  cout<<*(getNode(bt,3)->left->key)<<"\t";
  cout<<*(getNode(bt,3)->left->value)<<endl;
  cout<<endl;

  cout<<"Test -- assign a tree"<<endl;
  BTree<int,double> bt2;
  assign(bt2,bt);
  cout<<*(bt2.root->key)<<"\t"<<*(bt2.root->value)<<endl;
  cout<<*(bt2.root->left->key)<<"\t"<<*(bt2.root->left->value)<<endl;
  cout<<*(bt2.root->right->key)<<"\t"<<*(bt2.root->right->value)<<endl;
  cout<<*(bt2.root->left->left->key)<<"\t"<<*(bt2.root->left->left->value)<<endl;
  cout<<*(bt2.root->left->right->key)<<"\t"<<*(bt2.root->left->right->value)<<endl;
  cout<<endl;

  cout<<"Test -- remove node"<<endl;
  removeNode(bt,4);
  cout<<bt.root->left->right<<endl;
  removeNode(bt,bt.root);
  cout<<*(bt.root->key)<<"\t"<<*(bt.root->value)<<endl;
  cout<<endl;

  cout<<"Test -- release a tree"<<endl;
  release(bt2);
  cout<<bt2.root<<endl;
  cout<<endl;

  return 1;
}

