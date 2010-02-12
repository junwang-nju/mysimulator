
#include "btree.h"
#include "util.h"
#include <iostream>
using namespace std;

int main() {
  BTree<int,double> BT;

  cout<<"Test -- insert with key and value"<<endl;
  BT.insert(5,6.5);
  BT.insert(3,3.5);
  BT.insert(1,1.5);
  BT.insert(2,2.5);
  BT.insert(9,9.5);
  cout<<endl;

  cout<<"Test -- insert with node"<<endl;
  BTreeNode<int,double> BTn;
  int key=7;
  double value=7.5;
  BTn.ptr2key()=&key;
  BTn.ptr2value()=&value;
  BT.insert(BTn);
  cout<<endl;

  cout<<"Test -- assign with another btree"<<endl;
  BTree<int,double> BT1;
  BT1=BT;
  cout<<endl;

  cout<<"Test -- access through ptr of root"<<endl;
  cout<<*(BT.ptrRoot()->ptr2key())<<"\t\t";
  cout<<*(BT.ptrRoot()->ptr2value())<<endl;
  cout<<*(BT.ptrRoot()->right()->ptr2key())<<"\t\t";
  cout<<*(BT.ptrRoot()->right()->ptr2value())<<endl;
  cout<<*(BT.ptrRoot()->left()->ptr2key())<<"\t\t";
  cout<<*(BT.ptrRoot()->left()->ptr2value())<<endl;
  cout<<endl;

  cout<<"Test -- get value from key"<<endl;
  cout<<*(BT.get(1))<<endl;
  cout<<endl;

  cout<<"Test -- get node from key"<<endl;
  BTreeNode<int,double>* bnd;
  bnd=const_cast<BTreeNode<int,double>*>(BT.getNode(3));
  cout<<endl;

  cout<<"Test -- remove node"<<endl;
  BT.remove(bnd);
  cout<<*(BT.ptrRoot()->left()->ptr2key())<<"\t\t";
  cout<<*(BT.ptrRoot()->left()->ptr2value())<<endl;
  bnd=const_cast<BTreeNode<int,double>*>(BT.getNode(7));
  BT.remove(bnd);
  cout<<endl;

  cout<<"Test -- clear tree"<<endl;
  BT.clear();
  cout<<BT.ptrRoot()<<endl;
  cout<<endl;

  return 1;
}

