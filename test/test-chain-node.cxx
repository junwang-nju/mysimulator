
#include "chain-node.h"
#include <iostream>
using namespace std;

int main() {
  cout<<"Test -- initialize"<<endl;
  ChainNode<int> CN;
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  allocate(CN);
  CN()=5;
  cout<<endl;

  cout<<"Test -- assign external parent and child"<<endl;
  ChainNode<int> CNp,CNc;
  allocate(CNp);
  allocate(CNc);
  CNp()=4;
  CNc()=6;
  CN.parent=&CNp;
  CN.child=&CNc;
  CN.parentstate=Reference;
  CN.childstate=Reference;
  CNp.child=&CN;
  CNp.childstate=Reference;
  CNc.parent=&CN;
  CNc.parentstate=Reference;
  cout<<*(CN.parent->child->child->content)<<endl;
  cout<<endl;

  cout<<"Test -- content access"<<endl;
  cout<<CNp()<<endl;
  cout<<endl;

  cout<<"Test -- insert a parent node"<<endl;
  ChainNode<int> CNa;
  allocate(CNa);
  CNa()=34;
  add_parent(CNc,CNa);
  cout<<*(CN.child->content)<<"\t"<<*(CN.child->parent->content)<<endl;
  cout<<*(CNc.parent->content)<<"\t"<<*(CNc.parent->child->content)<<endl;
  cout<<endl;

  cout<<"Test -- insert a content"<<endl;
  add_parent(CNc,45);
  cout<<*(CN.child->child->content)<<"\t"<<*(CN.child->child->parent->content)<<endl;
  cout<<*(CNc.parent->content)<<"\t"<<*(CNc.parent->child->content)<<endl;
  add_parent(*(CNc.parent),85,Allocated);
  cout<<*(CN.child->child->content)<<"\t"<<*(CN.child->child->parent->content)<<endl;
  cout<<*(CNc.parent->parent->content)<<"\t"<<*(CNc.parent->parent->child->content)<<endl;
  cout<<endl;

  cout<<"Test -- release node"<<endl;
  release(*(CNc.parent));
  cout<<*(CN.child->child->content)<<"\t"<<*(CN.child->child->parent->content)<<endl;
  cout<<*(CNc.parent->content)<<"\t"<<*(CNc.parent->child->content)<<endl;
  cout<<*(CNc.parent->parent->content)<<"\t"<<*(CNc.parent->parent->child->content)<<endl;
  cout<<endl;

  cout<<"Test -- availability"<<endl;
  cout<<IsAvailable(CN)<<endl;
  release(CNp);
  cout<<IsAvailable(CNp)<<endl;
  cout<<endl;

  return 1;
}

