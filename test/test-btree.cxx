
#include "btree/node/allocate.h"
#include "btree/node/copy.h"
#include "btree/allocate.h"
#include "btree/copy.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {

  cout<<endl;
  BTreeNode<int,double> BN,BN2;
  cout<<"Before Allocation: states of key and value are";
  cout<<"\t"<<BN.key.flag<<"\t"<<BN.value.flag<<endl;
  allocate(BN);
  cout<<"After Allocation: states of key and value are";
  cout<<"\t"<<BN.key.flag<<"\t"<<BN.value.flag<<endl;
  imprint(BN2,BN);
  cout<<"After Imprint: states of key and value are";
  cout<<"\t"<<BN2.key.flag<<"\t"<<BN2.value.flag<<endl;

  cout<<endl;
  BN.key()=5;
  BN.value()=5.5;
  cout<<"Key and Value of Node Before Copy are:";
  cout<<"\t"<<BN2.key()<<"\t"<<BN2.value()<<endl;
  copy(BN2,BN);
  cout<<"Key and Value of Node After Copy are:";
  cout<<"\t"<<BN2.key()<<"\t"<<BN2.value()<<endl;

  cout<<endl;
  BTree<int,double> B,B2;
  cout<<"State of root of BTree Before Allocation:";
  cout<<"\t"<<B.root.flag<<endl;
  allocate(B);
  cout<<"State of root of BTree After Allocation:";
  cout<<"\t"<<B.root.flag<<endl;
  imprint(B2,B);
  cout<<"State of root of BTree After Imprint:";
  cout<<"\t"<<B2.root.flag<<endl;
  cout<<"Validity of BTree After Allocation is: "<<IsValid(B)<<endl;

  cout<<endl;
  B.insert(1,1.5);
  cout<<"Inserted Root is:"<<endl;
  cout<<"\t"<<B.root().key()<<"\t"<<B.root().value()<<endl;
  cout<<"\t"<<B.root().key.flag<<"\t"<<B.root().value.flag<<endl;
  int iValue;
  double dValue;
  iValue=2;
  B.insert(iValue,2.5,Referred);
  cout<<"Inserted Right is:\t"<<B.root().right().workBranch<<endl;
  cout<<"\t"<<B.root().right().key()<<"\t"<<B.root().right().value()<<endl;
  cout<<"\t"<<B.root().right().key.flag<<"\t"<<B.root().right().value.flag<<endl;
  dValue=-3.5;
  B.insert(-3,dValue,Allocated,Referred);
  cout<<"Inserted Left is:\t"<<B.root().left().workBranch<<endl;
  cout<<"\t"<<B.root().left().key()<<"\t"<<B.root().left().value()<<endl;
  cout<<"\t"<<B.root().left().key.flag<<"\t"<<B.root().left().value.flag<<endl;
  dValue=-3.5;
  double* pV;
  pV=const_cast<double*>(B.getValue(9));
  cout<<"Query with Not Valid Key produce pointer:\t"<<pV<<endl;
  pV=const_cast<double*>(B.getValue(-3));
  cout<<"Query with Valid Key produce pointer:\t"<<pV<<"\tand Value:\t"<<(*pV)<<endl;
  B.insert(9,9.5);
  B.insert(4,4.5);
  B.insert(-2,-2.5);
  B.insert(-5,-5.5);
  B.remove(-3);
  cout<<"Remove a middle node in left btree, the resultant tree is:"<<endl;
  cout<<"\t"<<B.root().left().key()<<"\t"<<B.root().left().value()<<endl;
  cout<<"\t"<<B.root().left().left().key()<<"\t"<<B.root().left().left().value()<<endl;
  B.remove(2);
  cout<<"Remove a middle node in right btree, the resultant tree is:"<<endl;
  cout<<"\t"<<B.root().right().key()<<"\t"<<B.root().right().value()<<endl;
  cout<<"\t"<<B.root().right().left().key()<<"\t"<<B.root().right().left().value()<<endl;

  cout<<endl;
  copy(B2,B);
  cout<<"Tree created by copy operation:"<<endl;
  cout<<"\t"<<B2.root().left().key()<<"\t"<<B2.root().left().value()<<endl;
  cout<<"\t"<<B2.root().left().left().key()<<"\t"<<B2.root().left().left().value()<<endl;
  cout<<"\t"<<B2.root().right().key()<<"\t"<<B2.root().right().value()<<endl;
  cout<<"\t"<<B2.root().right().left().key()<<"\t"<<B2.root().right().left().value()<<endl;

  return 0;
}

