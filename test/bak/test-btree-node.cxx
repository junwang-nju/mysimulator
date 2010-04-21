
#include "btree-node.h"
#include <iostream>
using namespace std;

int main() {
  BTreeNode<int,double> bn;

  cout<<"Test -- assign the pointers of key and value"<<endl;
  int key=2;
  double value=2.5;
  bn.ptr2key()=&key;
  bn.ptr2value()=&value;
  cout<<endl;

  cout<<"Test -- read key and value"<<endl;
  cout<<*(bn.ptr2key())<<"\t\t";
  cout<<*(bn.ptr2value())<<endl;
  cout<<endl;

  cout<<"Test -- assign the parent, left and right children"<<endl;
  BTreeNode<int,double> bnp,bnl,bnr;
  int keyp=5,keyl=1,keyr=3;
  double valuep=1.5,valuel=5.5,valuer=-2.4;
  bnp.ptr2key()=&keyp;
  bnp.ptr2value()=&valuep;
  bnl.ptr2key()=&keyl;
  bnl.ptr2value()=&valuel;
  bnr.ptr2key()=&keyr;
  bnr.ptr2value()=&valuer;
  bn.SetParent(&bnp,-1);    bnp.SetLeft(&bn);
  bn.SetLeft(&bnl);         bnl.SetParent(&bn,-1);
  bn.SetRight(&bnr);        bnr.SetParent(&bn,1);
  cout<<endl;

  cout<<"Test -- read parent and child information"<<endl;
  cout<<*(bn.parent()->ptr2key())<<"\t\t";
  cout<<*(bn.parent()->ptr2value())<<endl;
  cout<<*(bn.left()->ptr2key())<<"\t\t";
  cout<<*(bn.left()->ptr2value())<<endl;
  cout<<*(bn.right()->ptr2key())<<"\t\t";
  cout<<*(bn.right()->ptr2value())<<endl;
  cout<<endl;

  cout<<"Test -- assign from another node"<<endl;
  BTreeNode<int,double> bnn;
  bnn=bn;
  cout<<*(bnn.ptr2key())<<"\t\t";
  cout<<*(bnn.ptr2value())<<endl;
  cout<<endl;

  cout<<"Test -- assign and get alloc flag"<<endl;
  bn.SetTreeAllocFlag(true);
  cout<<bn.IsAllocByTree()<<endl;
  cout<<endl;

  cout<<"Test -- clear node"<<endl;
  bn.clear();
  cout<<bn.parent()<<"\t\t"<<bn.left()<<"\t\t"<<bn.right()<<endl;
  cout<<endl;

  return 1;
}

