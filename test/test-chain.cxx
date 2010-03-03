
#include "chain.h"
#include <iostream>
using namespace std;

int main() {
  Chain<int> C;

  cout<<"Test -- append with content"<<endl;
  C.append(2);
  C.append(5);
  cout<<endl;

  cout<<"Test -- access chain through root and head"<<endl;
  ChainNode<int>* nd=const_cast<ChainNode<int>*>(&(C.root()));
  while((nd=nd->child())!=&(C.head())) { cout<<nd->content()<<endl; }
  cout<<endl;

  cout<<"Test -- append with node"<<endl;
  ChainNode<int> nda;
  nda.content()=103;
  C.append(nda);
  nd=const_cast<ChainNode<int>*>(&(C.root()));
  while((nd=nd->child())!=&(C.head())) { cout<<nd->content()<<endl; }
  cout<<endl;

  cout<<"Test -- copy another chain"<<endl;
  Chain<int> C1;
  C1=C;
  nd=const_cast<ChainNode<int>*>(&(C1.root()));
  while((nd=nd->child())!=&(C1.head())) { cout<<nd->content()<<endl; }
  cout<<endl;

  cout<<"Test -- remove a node"<<endl;
  nd=const_cast<ChainNode<int>*>(C.root().child());
  C.remove(nd);
  nd=const_cast<ChainNode<int>*>(&(C.root()));
  while((nd=nd->child())!=&(C.head())) { cout<<nd->content()<<endl; }
  cout<<endl;

  cout<<"Test -- clear a chain"<<endl;
  C.clear();
  nd=const_cast<ChainNode<int>*>(&(C.root()));
  while((nd=nd->child())!=&(C.head())) { cout<<nd->content()<<endl; }
  cout<<"============"<<endl;
  nd=const_cast<ChainNode<int>*>(&(C1.root()));
  while((nd=nd->child())!=&(C1.head())) { cout<<nd->content()<<endl; }
  cout<<endl;

  return 1;
}
