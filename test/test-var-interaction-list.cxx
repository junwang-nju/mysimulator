
#include "var-interaction-list.h"
#include <iostream>
using namespace std;

int main() {
  varInteractionList vIL;

  varVector<unsigned int> Sz(5);
  for(unsigned int i=0;i<5;++i) Sz[i]=i+3;
  vIL.allocate(Sz);

  cout<<"Test -- size information"<<endl;
  cout<<vIL.size()<<endl;
  cout<<vIL.numberUnits()<<endl;
  cout<<vIL.dataSize()<<endl;
  cout<<endl;

  cout<<"Test -- access element with [] operator"<<endl;
  for(unsigned int i=0;i<5;++i)
  for(unsigned int k=0;k<vIL[i].size();++k)
    vIL[i][k]=i+k;
  cout<<vIL[1]<<endl;
  cout<<endl;

  cout<<"Test -- assign from another var-property-list"<<endl;
  vIL[2]=3;
  varPropertyList<double> vIL2(Sz);
  vIL2=vIL;
  cout<<vIL2[2]<<endl;
  cout<<endl;

  cout<<"Test -- access through structure"<<endl;
  cout<<vIL<<endl;
  cout<<vIL.Structure()<<endl;
  cout<<endl;

  return 1;
}

