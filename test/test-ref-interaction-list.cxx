
#include "ref-interaction-list.h"
#include "var-interaction-list.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- init"<<endl;
  refInteractionList rIL;
  cout<<endl;
  
  cout<<"Test -- refer operation"<<endl;
  varInteractionList vIL;
  varVector<unsigned int> Sz(5);
  for(unsigned int i=0;i<5;++i) Sz[i]=i+3;
  vIL.allocate(Sz);
  rIL.refer(vIL);
  cout<<endl;

  cout<<"Test -- size information"<<endl;
  cout<<rIL.size()<<endl;
  cout<<rIL.numberUnits()<<endl;
  cout<<rIL.dataSize()<<endl;
  cout<<endl;

  cout<<"Test -- access element with [] operator"<<endl;
  for(unsigned int i=0;i<5;++i)
  for(unsigned int k=0;k<rIL[i].size();++k)
    rIL[i][k]=i+k;
  cout<<rIL[1]<<endl;
  cout<<endl;

  cout<<"Test -- assign from another var-interaction-list"<<endl;
  rIL[2]=3;
  varInteractionList vIL2(Sz);
  refInteractionList rIL2;
  rIL2.refer(vIL2);
  rIL2=rIL;
  cout<<vIL2[2]<<endl;
  cout<<endl;

  cout<<"Test -- access through structure"<<endl;
  cout<<rIL<<endl;
  cout<<rIL.Structure()<<endl;
  cout<<endl;

  return 1;
}

