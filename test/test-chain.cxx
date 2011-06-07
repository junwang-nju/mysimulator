
#include "chain/node/copy.h"
#include "chain/node/refer.h"
#include "chain/allocate.h"
#include "chain/copy.h"
using namespace mysimulator;

#include <iostream>
using namespace std;

int main() {

  ChainNode<int>  Nd,Nd2;

  cout<<endl;
  allocate(Nd);
  Nd.content()=5;
  cout<<"Content of Chain Node is: "<<Nd.content()<<endl;
  imprint(Nd2,Nd);
  Nd2.content()=8;
  cout<<"Content of Chain Node is: "<<Nd2.content()<<endl;
  cout<<"Access Chain Node through () operator: "<<Nd()<<endl;

  cout<<endl;
  ChainNode<int> Nd3;
  cout<<"Validity of Allocated Chain Node: "<<IsValid(Nd)<<endl;
  cout<<"Validity of un-Allocated Chain Node: "<<IsValid(Nd3)<<endl;
  release(Nd2);
  cout<<"Validity after release: "<<IsValid(Nd2)<<endl;

  cout<<endl;
  allocate(Nd2);
  Nd2()=9;
  copy(Nd,Nd2);
  cout<<"The content of copied Node is: "<<Nd()<<endl;

  cout<<endl;
  refer(Nd3,Nd);
  cout<<"content of referred Chain Node: "<<Nd3()<<endl;

  cout<<endl;
  cout<<"Extract Node and Check whether it is allocated by Chain: "<<extract(Nd)<<endl;

  cout<<endl;
  Chain<int> C,C2;
  cout<<"Before Allocation of Chain: root is "<<IsValid(C.root)<<endl;
  allocate(C);
  cout<<"After Allocation of Chain: root is "<<IsValid(C.root)<<endl;
  imprint(C2,C);
  cout<<"Aftter Imprint of Chain: root is "<<IsValid(C2.root)<<endl;
  release(C2);
  cout<<"After release of Chain: head is "<<IsValid(C2.head)<<endl;

  cout<<endl;
  C.append(Nd);
  cout<<"The append content is: "<<C.head.parent().content()<<endl;
  cout<<"Check If A Node is Contained: "<<C.IsContained(Nd)<<endl;
  cout<<"Check If A Node is Contained: "<<C.IsContained(Nd2)<<endl;
  cout<<"Check If A Value is Contained: "<<C.IsContained(9)<<endl;
  C.append(8);
  cout<<"The append content is: "<<C.head.parent().content()<<endl;
  C.append(9);
  cout<<"Check If A Value is Contained: "<<C.IsContained(9)<<endl;
  int iValue=6;
  C.append(iValue,Referred);
  cout<<"append with Referred value:"<<endl;
  cout<<"\t"<<C.head.parent().content();
  cout<<"\t"<<C.head.parent().content.flag<<endl;
  cout<<"the content of present Chain are:"<<endl;
  cout<<"\t"<<C.head.parent().content()<<endl;
  cout<<"\t"<<C.head.parent().parent().content()<<endl;
  cout<<"\t"<<C.head.parent().parent().parent().content()<<endl;
  cout<<"\t"<<C.head.parent().parent().parent().parent().content()<<endl;
  C.remove(9);
  cout<<"the content of present Chain After Remove are:"<<endl;
  cout<<"\t"<<C.head.parent().content()<<endl;
  cout<<"\t"<<C.head.parent().parent().content()<<endl;
  cout<<"\t"<<C.head.parent().parent().parent().content()<<endl;

  cout<<endl;
  copy(C2,C);
  cout<<"the content of copied Chain are:"<<endl;
  cout<<"\t"<<C2.head.parent().content()<<endl;
  cout<<"\t"<<C2.head.parent().parent().content()<<endl;
  cout<<"\t"<<C2.head.parent().parent().parent().content()<<endl;
  return 0;
}

