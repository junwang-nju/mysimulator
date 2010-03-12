
#include "var-property-list.h"
#include <iostream>
using namespace std;

int main() {

  cout<<"Test -- init with null and size vec"<<endl;
  varPropertyList<double> vPL;
  varVector<unsigned int> Sz(5);
  for(unsigned int i=0;i<5;++i) Sz[i]=i+3;
  varPropertyList<double> vPL2(Sz);
  cout<<endl;

  cout<<"Test -- allocate"<<endl;
  vPL.allocate(Sz);
  cout<<endl;

  cout<<"Test -- size information"<<endl;
  cout<<vPL.size()<<endl;
  cout<<vPL.numberUnits()<<endl;
  cout<<vPL.dataSize()<<endl;
  cout<<endl;

  cout<<"Test -- access element with [] operator"<<endl;
  for(unsigned int i=0;i<5;++i)
  for(unsigned int k=0;k<vPL[i].size();++k)
    vPL[i][k]=i+k;
  cout<<vPL[1]<<endl;
  cout<<endl;

  cout<<"Test -- assign from another var-property-list"<<endl;
  vPL[2]=3;
  vPL2=vPL;
  cout<<vPL2[2]<<endl;
  cout<<endl;

  cout<<"Test -- vector-like operation"<<endl;
  vPL[1].scale(1.5);
  cout<<vPL<<endl;
  cout<<endl;

  cout<<"Test -- access through structure"<<endl;
  cout<<vPL.Structure()<<endl;
  cout<<endl;

  return 1;
}

