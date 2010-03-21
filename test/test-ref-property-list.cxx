
#include "ref-property-list.h"
#include "var-property-list.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- init"<<endl;
  refPropertyList<double>::Type rPL;
  cout<<endl;
  
  cout<<"Test -- refer operation"<<endl;
  varPropertyList<double>::Type vPL;
  varVector<unsigned int> Sz(5);
  for(unsigned int i=0;i<5;++i) Sz[i]=i+3;
  vPL.allocate(Sz);
  rPL.refer(vPL);
  cout<<endl;

  cout<<"Test -- size information"<<endl;
  cout<<rPL.size()<<endl;
  cout<<rPL.numberUnits()<<endl;
  cout<<rPL.dataSize()<<endl;
  cout<<endl;

  cout<<"Test -- access element with [] operator"<<endl;
  for(unsigned int i=0;i<5;++i)
  for(unsigned int k=0;k<rPL[i].size();++k)
    rPL[i][k]=i+k;
  cout<<rPL[1]<<endl;
  cout<<endl;

  cout<<"Test -- assign from another var-property-list"<<endl;
  rPL[2]=3;
  varPropertyList<double>::Type vPL2(Sz);
  refPropertyList<double>::Type rPL2;
  rPL2.refer(vPL2);
  rPL2=rPL;
  cout<<vPL2[2]<<endl;
  cout<<endl;

  cout<<"Test -- vector-like operation"<<endl;
  rPL[1].scale(1.5);
  cout<<rPL<<endl;
  cout<<endl;

  cout<<"Test -- access through structure"<<endl;
  cout<<rPL.Structure()<<endl;
  cout<<endl;

  return 1;
}

