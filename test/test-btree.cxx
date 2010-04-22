
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
  insert(bt,2,2.5);
  insert(bt,9,9.5);
  cout<<endl;

  return 1;
}

